#include <windows.h>
#include "Source.h"
#include "PixelEngine.h"

#include <iostream>
#include "Graphics/Sprite.h"

using namespace PxEngine;
using namespace std;

int main()
{
	if (!PixelEngine::Initialize(64, 36, 16, "Pixels"))
		return 0;

	Color duckPalette[3] = { Color(255, 255, 0), Color(255, 192, 0), Color(0, 0, 0) };
	Color brickPalette[3] = { Color(255, 127, 39), Color(196, 79, 0), Color(88, 55, 37) };

	PixelEngine::SetPalette(SpritePalette, 3, duckPalette);
	PixelEngine::SetPalette(SpritePalette, 2, brickPalette);

	PixelEngine::SetPalette(StaticPalette, 3, duckPalette);
	PixelEngine::SetPalette(StaticPalette, 2, brickPalette);

	PixelEngine::SetBgColor(Color(50, 150, 255));

	PixelEngine::SetPerspectivePos(Vector2(0, 0));

	StaticObject bricks0_0 = StaticObject(Vector2(0, 0), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks1_0 = StaticObject(Vector2(8, 0), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks2_0 = StaticObject(Vector2(16, 0), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks3_0 = StaticObject(Vector2(24, 0), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks4_0 = StaticObject(Vector2(32, 0), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks5_0 = StaticObject(Vector2(40, 0), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks6_0 = StaticObject(Vector2(48, 0), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks7_0 = StaticObject(Vector2(56, 0), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks0_1 = StaticObject(Vector2(0, 8), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks1_1 = StaticObject(Vector2(8, 8), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks2_1 = StaticObject(Vector2(16, 8), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks3_1 = StaticObject(Vector2(24, 8), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks4_1 = StaticObject(Vector2(32, 8), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks5_1 = StaticObject(Vector2(40, 8), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks6_1 = StaticObject(Vector2(48, 8), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject bricks7_1 = StaticObject(Vector2(56, 8), new char(0), new Vector2(0, 0), 1, 2, false, false, false, false);
	StaticObject mage = StaticObject(Vector2(16, 16), new char(1), new Vector2(0, 0), 1, 3, false, false, false, false);
	StaticObject knight = StaticObject(Vector2(40, 16), new char(2), new Vector2(0, 0), 1, 3, false, false, true, false);

	PixelEngine::AddStaticObject(&bricks0_0);
	PixelEngine::AddStaticObject(&bricks1_0);
	PixelEngine::AddStaticObject(&bricks2_0);
	PixelEngine::AddStaticObject(&bricks3_0);
	PixelEngine::AddStaticObject(&bricks4_0);
	PixelEngine::AddStaticObject(&bricks5_0);
	PixelEngine::AddStaticObject(&bricks6_0);
	PixelEngine::AddStaticObject(&bricks7_0);
	PixelEngine::AddStaticObject(&bricks0_1);
	PixelEngine::AddStaticObject(&bricks1_1);
	PixelEngine::AddStaticObject(&bricks2_1);
	PixelEngine::AddStaticObject(&bricks3_1);
	PixelEngine::AddStaticObject(&bricks4_1);
	PixelEngine::AddStaticObject(&bricks5_1);
	PixelEngine::AddStaticObject(&bricks6_1);
	PixelEngine::AddStaticObject(&bricks7_1);
	PixelEngine::AddStaticObject(&mage);
	PixelEngine::AddStaticObject(&knight);


	while (PixelEngine::Loop())
	{
		
		

	}

	return 0;
}