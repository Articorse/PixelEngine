#include "PixelEngine.h"
#include <iostream>

namespace PxEngine
{
	HWND PixelEngine::hwnd = 0;
	int PixelEngine::width = 0;
	int PixelEngine::height = 0;
	unsigned int PixelEngine::pixelDensity = 0;
	unsigned int PixelEngine::wndWidth = 0;
	unsigned int PixelEngine::wndHeight = 0;
	Color PixelEngine::backgroundColor = Color(0, 0, 0);
	Palette* PixelEngine::staticPalettes[] = { 0 };
	Palette* PixelEngine::spritePalettes[] = { 0 };
	Vector2 PixelEngine::perspectivePos = Vector2(0, 0);
	bitset<128> PixelEngine::dynamicSpriteTable[256] = { 0 };
	bitset<128> PixelEngine::staticSpriteTable[256] = { 0 };
	StaticObject* PixelEngine::staticObjects = 0;
	unsigned int PixelEngine::staticObjectsCount = 0;

	using namespace std;

	bool PixelEngine::Initialize(unsigned int _width, unsigned int _height, unsigned int _pixelDensity, const char _windowTitle[])
	{
		width = _width;
		height = _height;
		pixelDensity = _pixelDensity;
		wndWidth = width * pixelDensity;
		wndHeight = height * pixelDensity;

		InitializePalettes();
		SetDynamicSpriteTable();
		SetStaticSpriteTable();

		hwnd = CreatePixelWindow(wndWidth, wndHeight, pixelDensity, _windowTitle);

		if (hwnd)
		{
			return true;
		}
		return false;
	}

	void PixelEngine::SetPalette(PaletteType pt, char index, Color colors[3])
	{
		if (pt == PxEngine::StaticPalette)
		{
			staticPalettes[index] = new Palette(colors[0], colors[1], colors[2]);
		}
		else if (pt == PxEngine::SpritePalette)
		{
			spritePalettes[index] = new Palette(colors[0], colors[1], colors[2]);
		}
	}

	void PixelEngine::SetBgColor(Color c)
	{
		backgroundColor = c;
	}



	Palette* PixelEngine::GetPalette(PaletteType pt, char index)
	{
		if (index >= 0 && index < 4)
		{
			if (pt == PxEngine::StaticPalette)
			{
				return PixelEngine::staticPalettes[index];
			}
			else if (pt == PxEngine::SpritePalette)
			{
				return PixelEngine::spritePalettes[index];
			}
			else
			{
				throw "Invalid Palette Type!";
			}
		}
		else
		{
			throw "Invalid Palette Index!";
		}
	}

	bool PixelEngine::Loop()
	{
		MSG msg = { };
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			return true;
		}
		return false;
	}

	void PixelEngine::SetPerspectivePos(Vector2 pPos)
	{
		perspectivePos = pPos;
	}


	// !!! Rework to be able to draw in world space without using the old 'worldPixels' system.
	void PixelEngine::DrawWorldPixel(Vector2 pixPos, Color c)
	{
		//worldPixels[pixPos.x + pixPos.y * width] = c;
	}

	bitset<128>* PixelEngine::GetDynamicSpriteTable()
	{
		return dynamicSpriteTable;
	}

	bitset<128>* PixelEngine::GetStaticSpriteTable()
	{
		return staticSpriteTable;
	}

	void PixelEngine::AddStaticObject(StaticObject* sO)
	{
		for (unsigned int i = 0; i < staticObjectsCount; i++)
		{
			if (&staticObjects[i] == sO)
			{
				cout << "Static Object already in list!" << endl;
				return;
			}
		}

		for (unsigned int i = 0; i < staticObjectsCount; i++)
		{
			if (!&staticObjects[i])
			{
				staticObjects[i] = *sO;
				return;
			}
		}

		StaticObject* newSO = new StaticObject[staticObjectsCount + 1];
		for (unsigned int i = 0; i < staticObjectsCount; i++)
		{
			newSO[i] = staticObjects[i];
		}
		newSO[staticObjectsCount] = *sO;
		staticObjects = newSO;
		staticObjectsCount++;
	}


	 /////////////
	// Private //
   /////////////

	void PixelEngine::InitializePalettes()
	{
		staticPalettes[0] = new Palette(Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255));
		staticPalettes[1] = new Palette(Color(255, 255, 0), Color(0, 255, 255), Color(255, 0, 255));
		staticPalettes[2] = new Palette(Color(255, 150, 150), Color(150, 255, 150), Color(150, 150, 255));
		staticPalettes[3] = new Palette(Color(0, 0, 0), Color(125, 125, 125), Color(255, 255, 255));
		spritePalettes[0] = new Palette(Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255));
		spritePalettes[1] = new Palette(Color(255, 255, 0), Color(0, 255, 255), Color(255, 0, 255));
		spritePalettes[2] = new Palette(Color(255, 150, 150), Color(150, 255, 150), Color(150, 150, 255));
		spritePalettes[3] = new Palette(Color(0, 0, 0), Color(125, 125, 125), Color(255, 255, 255));
		backgroundColor = Color(0, 0, 0);
	}

	void PixelEngine::SetDynamicSpriteTable()
	{
		bool sprMageArray[128] = 
		{
			0,0,	0,0,	0,0,	0,0,	0,0,	0,0,	0,0,	0,0,

			0,0,	0,0,	0,1,	0,1,	0,1,	0,1,	0,1,	0,0,

			0,0,	0,1,	0,1,	0,1,	1,1,	1,1,	1,1,	0,1,

			0,1,	0,1,	0,1,	1,1,	1,0,	1,1,	1,0,	0,0,

			0,1,	0,0,	0,1,	1,1,	1,1,	1,1,	1,1,	0,0,

			0,0,	0,0,	1,0,	0,1,	1,1,	1,1,	0,1,	0,0,

			0,0,	0,1,	0,0,	0,1,	0,1,	0,1,	0,0,	1,0,

			0,0,	0,0,	0,1,	0,1,	0,1,	0,1,	0,1,	0,0
		};

		bitset<128> spriteMage;
		for (u_int i = 0; i < 128; i++)
		{
			spriteMage[i] = sprMageArray[i];
		}
		dynamicSpriteTable[0] = spriteMage;

		bool sprKnightArray[128] =
		{
			1,0,	0,0,	0,0,	1,0,	1,0,	1,0,	1,0,	0,0,

			1,0,	0,0,	0,1,	0,1,	0,1,	0,1,	1,0,	0,0,

			1,0,	0,0,	1,0,	0,1,	1,0,	0,1,	1,0,	0,0,

			1,0,	0,0,	0,1,	0,1,	1,0,	0,1,	1,0,	1,0,

			1,1,	0,1,	1,0,	1,0,	1,0,	1,0,	1,1,	1,1,

			0,0,	0,0,	1,0,	1,1,	1,1,	1,0,	1,1,	1,1,

			0,0,	0,0,	1,0,	1,0,	1,0,	1,0,	1,0,	0,0,

			0,0,	0,0,	0,1,	0,0,	0,0,	0,0,	0,1,	0,0
		};

		bitset<128> spriteKnight;
		for (u_int i = 0; i < 128; i++)
		{
			spriteKnight[i] = sprKnightArray[i];
		}
		dynamicSpriteTable[1] = spriteKnight;


		//spriteKnight.i32_1 = 178783236;
		//spriteKnight.i32_2 = 3668904943;
		//spriteKnight.i32_3 = 2308474207;
		//spriteKnight.i32_4 = 2192082264;

		//dynamicSpriteTable[1] = spriteKnight;

		//spriteDuck.i32_1 = 89392468;
		//spriteDuck.i32_2 = 74712406;
		//spriteDuck.i32_3 = 84;
		//spriteDuck.i32_4 = 0;

		//dynamicSpriteTable[2] = spriteDuck;

		//spriteSnake.i32_1 = 1349129578;
		//spriteSnake.i32_2 = 67125672;
		//spriteSnake.i32_3 = 357831884;
		//spriteSnake.i32_4 = 257694800;

		//dynamicSpriteTable[3] = spriteSnake;
	};

	void PixelEngine::SetStaticSpriteTable()
	{
		bool sprArray[128] =
		{
			0,1,	0,1,	0,1,	1,1,	1,0,	0,1,	0,1,	0,1,

			0,1,	0,1,	0,1,	1,1,	1,0,	0,1,	0,1,	0,1,

			1,0,	1,0,	1,0,	1,1,	1,0,	1,0,	1,0,	1,0,

			1,1,	1,1,	1,1,	1,1,	1,1,	1,1,	1,1,	1,1,

			1,0,	0,1,	0,1,	0,1,	0,1,	0,1,	0,1,	1,1,

			1,0,	0,1,	0,1,	0,1,	0,1,	0,1,	0,1,	1,1,

			1,0,	1,0,	1,0,	1,0,	1,0,	1,0,	1,0,	1,1,

			1,1,	1,1,	1,1,	1,1,	1,1,	1,1,	1,1,	1,1,
		};		

		bitset<128> spriteBricks;

		for (u_int i = 0; i < 128; i++)
		{
			spriteBricks[i] = sprArray[i];
		}

		staticSpriteTable[0] = spriteBricks;

		// TEMP

		bool sprMageArray[128] =
		{
			0,0,	0,0,	0,0,	0,0,	0,0,	0,0,	0,0,	0,0,

			0,0,	0,0,	0,1,	0,1,	0,1,	0,1,	0,1,	0,0,

			0,0,	0,1,	0,1,	0,1,	1,1,	1,1,	1,1,	0,1,

			0,1,	0,1,	0,1,	1,1,	1,0,	1,1,	1,0,	0,0,

			0,1,	0,0,	0,1,	1,1,	1,1,	1,1,	1,1,	0,0,

			0,0,	0,0,	1,0,	0,1,	1,1,	1,1,	0,1,	0,0,

			0,0,	0,1,	0,0,	0,1,	0,1,	0,1,	0,0,	1,0,

			0,0,	0,0,	0,1,	0,1,	0,1,	0,1,	0,1,	0,0
		};

		bitset<128> spriteMage;
		for (u_int i = 0; i < 128; i++)
		{
			spriteMage[i] = sprMageArray[i];
		}
		staticSpriteTable[1] = spriteMage;

		bool sprKnightArray[128] =
		{
			0,0,	1,0,	1,0,	1,0,	1,0,	0,0,	0,0,	1,0,

			0,0,	1,0,	0,1,	0,1,	0,1,	0,1,	0,0,	1,0,

			0,0,	1,0,	0,1,	1,0,	0,1,	1,0,	0,0,	1,0,

			1,1,	1,1,	0,1,	0,1,	0,1,	0,1,	0,0,	1,0,

			1,1,	1,1,	1,0,	1,0,	1,0,	1,0,	0,1,	1,1,

			1,1,	1,1,	1,0,	1,1,	1,1,	1,0,	0,0,	0,0,

			0,0,	1,0,	1,0,	1,0,	1,0,	1,0,	0,0,	0,0,

			0,0,	0,1,	0,0,	0,0,	0,0,	0,1,	0,0,	0,0
		};

		bitset<128> spriteKnight;
		for (u_int i = 0; i < 128; i++)
		{
			spriteKnight[i] = sprKnightArray[i];
		}
		staticSpriteTable[2] = spriteKnight;

		// TEMP
	};

	HWND PixelEngine::CreatePixelWindow(unsigned int _width, unsigned int _height, unsigned int _pixelDensity, const char _windowTitle[])
	{
		// Register the window class.
		const char CLASS_NAME[] = "Pixels Window Class";

		WNDCLASS wc = {};

		wc.lpfnWndProc = WindowProc;
		wc.hInstance = NULL;
		wc.lpszClassName = CLASS_NAME;

		RegisterClass(&wc);

		// Create the window.

		HWND hwnd = CreateWindowEx(
			0,											// Optional window styles.
			CLASS_NAME,									// Window class
			_windowTitle,								// Window text
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,	// Window style

														// Size and position
			0, 0, wndWidth + 16, wndHeight + 38,

			NULL,       // Parent window
			NULL,       // Menu
			NULL,		// Instance handle
			NULL        // Additional application data
		);

		if (hwnd == NULL)
		{
			return 0;
		}

		ShowWindow(hwnd, 5);

		return hwnd;
	}

	LRESULT CALLBACK PixelEngine::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			HDC hdc = GetDC(hwnd);
			HDC drawHdc = CreateCompatibleDC(hdc);

			unsigned char* wndPixels;

			BITMAPINFO bmi = { 0 };
			ZeroMemory(&bmi, sizeof(BITMAPINFO));
			bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
			bmi.bmiHeader.biWidth = wndWidth;
			bmi.bmiHeader.biHeight = wndHeight;
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;

			HBITMAP screenBMP = ::CreateDIBSection(drawHdc, &bmi, DIB_RGB_COLORS, (VOID * *)& wndPixels, NULL, 0);
			if (screenBMP == 0)
				return 0;

			HGDIOBJ oldBMP = ::SelectObject(drawHdc, screenBMP);

			int pitch = 4 * wndWidth; // 4 bytes per pixel but if not 32 bit, round pitch up to multiple of 4


			// Fill the visible screen with the background color
			for (u_int screenY = 0; screenY < height * pixelDensity; screenY++)
			{
				for (u_int screenX = 0; screenX < width * pixelDensity; screenX++)
				{
					u_int index = screenY * pitch;
					index += screenX * 4;

					wndPixels[index + 2] = backgroundColor.r;
					wndPixels[index + 1] = backgroundColor.g;
					wndPixels[index + 0] = backgroundColor.b;
				}
			}

			// Draw all static objects - !!! Split drawing into three phases - background static objects, dynamic objects, foreground static objects
			for (u_int i = 0; i < staticObjectsCount; i++)
			{
				if (&staticObjects[i])
				{
					StaticObject* sO = &staticObjects[i];
					Vector2 objPos = sO->GetPos();
					unsigned char spriteCount = sO->GetSpriteCount();
					Vector2* spritePositions = new Vector2[spriteCount];
					for (unsigned char n = 0; n < spriteCount; n++)
					{
						spritePositions[n] = objPos + sO->GetSpriteOffset()[n];
					}
					for (unsigned char n = 0; n < spriteCount; n++)
					{
						DrawSprite(sO, &spritePositions[n], pitch, wndPixels);
					}
				}
			}

			for (u_int i = 0; i < staticObjectsCount; i++)
			{
				if (&staticObjects[i])
				{
					StaticObject* sO = &staticObjects[i];
					Vector2 objPos = sO->GetPos();
					unsigned char spriteCount = sO->GetSpriteCount();
					Vector2* spritePositions = new Vector2[spriteCount];
					for (unsigned char n = 0; n < spriteCount; n++)
					{
						spritePositions[n] = objPos + sO->GetSpriteOffset()[n];
					}
					for (unsigned char n = 0; n < spriteCount; n++)
					{
						DrawSprite(sO, &spritePositions[n], pitch, wndPixels);
					}
				}
			}



			//Sleep(16);





			BitBlt(hdc, 0, 0, wndWidth, wndHeight, drawHdc, 0, 0, SRCCOPY);

			SelectObject(drawHdc, oldBMP);
			DeleteDC(drawHdc);
			DeleteObject(screenBMP);
			ReleaseDC(hwnd, hdc);

		}
		return 0;

		}


		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	void PixelEngine::DrawSprite(StaticObject* sO, Vector2* sprPos, int pitch, unsigned char* wndPixels)
	{
		bitset<128> * spr = &staticSpriteTable[*sO->GetSprite()];
		Palette* sprPal = spritePalettes[sO->GetPaletteId()];
		bool* mirX = &sO->mirrorX;
		bool* mirY = &sO->mirrorY;

		{
			for (unsigned char sprY = 0; sprY < 8; sprY++)
			{
				for (unsigned char sprX = 0; sprX < 8; sprX++)
				{
					Vector2 relPos = Vector2(sprX + sprPos->x - perspectivePos.x, sprY + sprPos->y - perspectivePos.y);
					if (relPos.x >= 0 && relPos.x < width && relPos.y >= 0 && relPos.y < height)
					{
						u_int indexMin = relPos.y * pitch * pixelDensity;
						indexMin += relPos.x * 4 * pixelDensity;

						u_int indexMax = (relPos.y + 1) * pitch * pixelDensity - pitch;
						indexMax += (relPos.x + 1) * 4 * pixelDensity - 4;

						Palette pal = *sprPal;

						bitset<128> bs = *spr;


						int a;
						int b;

						if (!*mirX && !*mirY)
						{
							a = (sprX + (7 - sprY) * 8) * 2;
							b = (sprX + (7 - sprY) * 8) * 2 + 1;
						}
						else if (*mirX && *mirY)
						{
							a = ((7 - sprX) + sprY * 8) * 2;
							b = ((7 - sprX) + sprY * 8) * 2 + 1;
						}
						else if (*mirX && !*mirY)
						{
							a = ((7 - sprX) + (7 - sprY) * 8) * 2;
							b = ((7 - sprX) + (7 - sprY) * 8) * 2 + 1;
						}
						else
						{
							a = (sprX + sprY * 8) * 2;
							b = (sprX + sprY * 8) * 2 + 1;
						}

						int col = bs[a] + bs[b] * 2;

						if (col > 0)
						{
							for (u_int y = indexMin; y < indexMax + 1; y = y + pitch)
							{
								for (u_int x = y; x < y + pixelDensity * 4; x = x + 4)
								{
									wndPixels[x + 2] = pal[col].r;
									wndPixels[x + 1] = pal[col].g;
									wndPixels[x + 0] = pal[col].b;
								}
							}
						}
					}
				}
			}
		}

	}
}