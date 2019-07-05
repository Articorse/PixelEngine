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
	Sprite PixelEngine::dynamicSpriteTable[256] = { 0 };
	Sprite PixelEngine::staticSpriteTable[256] = { 0 };
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

		worldPixels = new Color[height * width];

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
		if (pPos.x >= 0 && pPos.y >= 0)
		{
			perspectivePos = pPos;
		}
	}

	void PixelEngine::DrawWorldPixel(Vector2 pixPos, Color c)
	{
		worldPixels[pixPos.x + pixPos.y * width] = c;
	}

	void PixelEngine::DrawSprite(Sprite sprite, Vector2 pos, Palette palette, bool mirrorX, bool mirrorY)
	{
		Vector2 curPixel = Vector2(0, 0);
		char xDirection = 1;
		char yDirection = 1;

		if (mirrorX)
		{
			curPixel += Vector2(7, 0);
			xDirection *= -1;
		}

		if (mirrorY)
		{
			curPixel += Vector2(0, 7);
			yDirection *= -1;
		}

		curPixel += pos;

		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x0y0]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x1y0]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x2y0]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x3y0]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x4y0]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x5y0]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x6y0]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x7y0]);
		curPixel.x -= xDirection * 7;
		curPixel.y += yDirection;

		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x0y1]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x1y1]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x2y1]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x3y1]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x4y1]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x5y1]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x6y1]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x7y1]);
		curPixel.x -= xDirection * 7;
		curPixel.y += yDirection;

		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x0y2]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x1y2]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x2y2]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x3y2]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x4y2]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x5y2]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x6y2]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x7y2]);
		curPixel.x -= xDirection * 7;
		curPixel.y += yDirection;

		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x0y3]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x1y3]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x2y3]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x3y3]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x4y3]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x5y3]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x6y3]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x7y3]);
		curPixel.x -= xDirection * 7;
		curPixel.y += yDirection;

		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x0y4]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x1y4]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x2y4]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x3y4]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x4y4]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x5y4]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x6y4]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x7y4]);
		curPixel.x -= xDirection * 7;
		curPixel.y += yDirection;

		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x0y5]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x1y5]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x2y5]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x3y5]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x4y5]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x5y5]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x6y5]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x7y5]);
		curPixel.x -= xDirection * 7;
		curPixel.y += yDirection;

		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x0y6]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x1y6]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x2y6]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x3y6]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x4y6]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x5y6]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x6y6]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x7y6]);
		curPixel.x -= xDirection * 7;
		curPixel.y += yDirection;

		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x0y7]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x1y7]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x2y7]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x3y7]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x4y7]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x5y7]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x6y7]);
		curPixel.x += xDirection;
		PixelEngine::DrawWorldPixel(curPixel, palette[sprite.x7y7]);
	}

	Sprite* PixelEngine::GetDynamicSpriteTable()
	{
		return dynamicSpriteTable;
	}

	Sprite* PixelEngine::GetStaticSpriteTable()
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
		Sprite spriteMage = { 0 };
		Sprite spriteKnight = { 0 };
		Sprite spriteDuck = { 0 };
		Sprite spriteSnake = { 0 };

		spriteMage.i32_1 = 2235831632;
		spriteMage.i32_2 = 1118304;
		spriteMage.i32_3 = 1079259925;
		spriteMage.i32_4 = 5456;

		dynamicSpriteTable[0] = spriteMage;

		spriteKnight.i32_1 = 178783236;
		spriteKnight.i32_2 = 3668904943;
		spriteKnight.i32_3 = 2308474207;
		spriteKnight.i32_4 = 2192082264;

		dynamicSpriteTable[1] = spriteKnight;

		spriteDuck.i32_1 = 89392468;
		spriteDuck.i32_2 = 74712406;
		spriteDuck.i32_3 = 84;
		spriteDuck.i32_4 = 0;

		dynamicSpriteTable[2] = spriteDuck;

		spriteSnake.i32_1 = 1349129578;
		spriteSnake.i32_2 = 67125672;
		spriteSnake.i32_3 = 357831884;
		spriteSnake.i32_4 = 257694800;

		dynamicSpriteTable[3] = spriteSnake;
	};

	void PixelEngine::SetStaticSpriteTable()
	{
		Sprite spriteBricks = { 0 };

		spriteBricks.i32_1 = 2863398911;
		spriteBricks.i32_2 = 2505545047;
		spriteBricks.i32_3 = 2880110591;
		spriteBricks.i32_4 = 1469405077;

		staticSpriteTable[0] = spriteBricks;
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


			for (int screenY = 0; screenY < height; screenY++)
			{
				for (int screenX = 0; screenX < width; screenX++)
				{
					Vector2 relPixel = Vector2(screenX + perspectivePos.x, screenY + perspectivePos.y);
					if (relPixel.x >= 0 && relPixel.x < width && relPixel.y >= 0 && relPixel.y < height)
					{
						UINT32 index = relPixel.x + relPixel.y * width;
						worldPixels[index] = backgroundColor;
					}
				}
			}

			for (u_int i = 0; i < staticObjectsCount; i++)
			{
				if (&staticObjects[i])
				{
					Vector2 objPos = staticObjects[i].GetPos();
					unsigned char spriteCount = staticObjects[i].GetSpriteCount();
					Vector2* spritePositions = new Vector2[spriteCount];
					for (unsigned char n = 0; n < spriteCount; n++)
					{
						spritePositions[n] = objPos + staticObjects[n].GetSpriteOffset()[n];
					}
					for (unsigned char n = 0; n < spriteCount; n++)
					{
						Sprite* spr = &staticSpriteTable[*staticObjects[n].GetSprite()];
						Vector2* sprPos = &spritePositions[n];
						Palette* sprPal = spritePalettes[staticObjects[n].GetPaletteId()];
						bool* mirX = &staticObjects[n].mirrorX;
						bool* mirY = &staticObjects[n].mirrorY;


						DrawSprite(*spr, *sprPos, *sprPal, mirX, mirY);
					}
				}
			}

			for (int screenY = 0; screenY < height; screenY++)
			{
				for (int screenX = 0; screenX < width; screenX++)
				{
					Vector2 relPixel = Vector2(screenX + perspectivePos.x, screenY + perspectivePos.y);
					if (relPixel.x >= 0 && relPixel.x < width && relPixel.y >= 0 && relPixel.y < height)
					{
						UINT32 index = relPixel.x + relPixel.y * width;

						if (!worldPixels[index].transparent)
						{
							u_int indexMin = screenY * pitch * pixelDensity;
							indexMin += screenX * 4 * pixelDensity;

							u_int indexMax = (screenY + 1) * pitch * pixelDensity - pitch;
							indexMax += (screenX + 1) * 4 * pixelDensity - 4;


							for (u_int y = indexMin; y < indexMax + 1; y = y + pitch)
							{
								for (u_int x = y; x < y + pixelDensity * 4; x = x + 4)
								{
									wndPixels[x + 2] = worldPixels[index].r;
									wndPixels[x + 1] = worldPixels[index].g;
									wndPixels[x + 0] = worldPixels[index].b;
								}
							}
						}
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
}