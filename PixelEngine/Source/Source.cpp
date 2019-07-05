#include <windows.h>
#include "Source.h"
#include "PixelEngine.h"

using namespace PxEngine;

int main()
{
	if (!PixelEngine::Initialize(320, 180, 4, "Pixels"))
		return 0;

	/*Color duckPalette[3] = { Color(255, 255, 0), Color(255, 192, 0), Color(0, 0, 0) };
	Color brickPalette[3] = { Color(255, 127, 39), Color(196, 79, 0), Color(88, 55, 37) };

	PixelEngine::SetBgColor(Color(255, 255, 255));
	PixelEngine::SetPalette(SpritePalette, 3, duckPalette);
	PixelEngine::SetPalette(SpritePalette, 2, brickPalette);

	PixelEngine::DrawSprite(PixelEngine::GetStaticSpriteTable()[0], Vector2(0, 0), *PixelEngine::GetPalette(SpritePalette, 2));
	PixelEngine::DrawSprite(PixelEngine::GetStaticSpriteTable()[0], Vector2(8, 0), *PixelEngine::GetPalette(SpritePalette, 2));
	PixelEngine::DrawSprite(PixelEngine::GetStaticSpriteTable()[0], Vector2(16, 0), *PixelEngine::GetPalette(SpritePalette, 2));
	PixelEngine::DrawSprite(PixelEngine::GetStaticSpriteTable()[0], Vector2(24, 0), *PixelEngine::GetPalette(SpritePalette, 2));
	PixelEngine::DrawSprite(PixelEngine::GetStaticSpriteTable()[0], Vector2(32, 0), *PixelEngine::GetPalette(SpritePalette, 2));

	PixelEngine::DrawSprite(PixelEngine::GetStaticSpriteTable()[0], Vector2(0, 8), *PixelEngine::GetPalette(SpritePalette, 2));
	PixelEngine::DrawSprite(PixelEngine::GetStaticSpriteTable()[0], Vector2(8, 8), *PixelEngine::GetPalette(SpritePalette, 2));
	PixelEngine::DrawSprite(PixelEngine::GetStaticSpriteTable()[0], Vector2(16, 8), *PixelEngine::GetPalette(SpritePalette, 2));
	PixelEngine::DrawSprite(PixelEngine::GetStaticSpriteTable()[0], Vector2(24, 8), *PixelEngine::GetPalette(SpritePalette, 2));
	PixelEngine::DrawSprite(PixelEngine::GetStaticSpriteTable()[0], Vector2(32, 8), *PixelEngine::GetPalette(SpritePalette, 2));

	PixelEngine::DrawSprite(PixelEngine::GetDynamicSpriteTable()[2], Vector2(16, 16), *PixelEngine::GetPalette(SpritePalette, 3), true);
	
	PixelEngine::SetPerspectivePos(Vector2(0, 0));*/


	StaticObject bricks1 = StaticObject(Vector2(0, 0), new char(0), new Vector2(0, 0), 1, 0);
	StaticObject bricks2 = StaticObject(Vector2(8, 0), new char(0), new Vector2(0, 0), 1, 0);
	StaticObject bricks3 = StaticObject(Vector2(300, 160), new char(0), new Vector2(0, 0), 1, 0);

	PixelEngine::AddStaticObject(&bricks1);
	PixelEngine::AddStaticObject(&bricks2);
	PixelEngine::AddStaticObject(&bricks3);

	PixelEngine::SetBgColor(Color(50, 150, 255));

	PixelEngine::SetPerspectivePos(Vector2(0, 0));


	while (PixelEngine::Loop())
	{
		
		

	}

	return 0;
}