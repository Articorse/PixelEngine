#pragma once
#include <Windows.h>
#include "Graphics/Color.h"
#include "Graphics/Palette.h"
#include "Math/Vector2.h"
#include "Graphics/Sprite.h"
#include "Objects/StaticObject.h"

namespace PxEngine
{
	static Color* worldPixels;
	enum PaletteType { StaticPalette, SpritePalette };

	class PixelEngine
	{
	public:
		static bool Initialize(unsigned int _width, unsigned int _height, unsigned int _pixelDensity, const char _windowTitle[]);
		static void SetPalette(PaletteType pt, char index, Color colors[3]);
		static void SetBgColor(Color c);

		static Palette* GetPalette(PaletteType pt, char index);

		static bool Loop();

		static void SetPerspectivePos(Vector2 pPos);
		static void DrawWorldPixel(Vector2 pixPos, Color c);
		static void DrawSprite(Sprite sprite, Vector2 pos, Palette palette, bool mirrorX = false, bool mirrorY = false);

		static Sprite* GetDynamicSpriteTable();
		static Sprite* GetStaticSpriteTable();

		static void AddStaticObject(StaticObject* sO);

	private:

		static HWND hwnd;

		static int width;
		static int height;
		static unsigned int pixelDensity;
		static unsigned int wndWidth;
		static unsigned int wndHeight;
		static Palette* staticPalettes[4];
		static Palette* spritePalettes[4];
		static Color backgroundColor;
		static Sprite dynamicSpriteTable[256];
		static Sprite staticSpriteTable[256];

		static StaticObject* staticObjects;
		static unsigned int staticObjectsCount;

		static Vector2 perspectivePos;

		static void InitializePalettes();
		static void SetDynamicSpriteTable();
		static void SetStaticSpriteTable();


		static HWND CreatePixelWindow(unsigned int _width, unsigned int _height, unsigned int _pixelDensity, const char _windowTitle[]);
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
};