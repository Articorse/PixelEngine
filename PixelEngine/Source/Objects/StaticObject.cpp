#include "StaticObject.h"

StaticObject::StaticObject()
{
	pos = Vector2();
	spriteId = 0;
	spriteOffset = new Vector2();
	spriteCount = 0;
	paletteId = 0;
	passable = true;
	foreground = true;
}

StaticObject::StaticObject(Vector2 _pos, char* _spriteId, Vector2* _spriteOffset, unsigned char _spriteCount, char _paletteId, bool _passable, bool _foreground, bool _mirrorX, bool _mirrorY)
{
	if (_pos.x < 0 || _pos.y < 0)
	{
		_pos = Vector2();
	}
	pos = _pos;
	spriteId = _spriteId;
	spriteOffset = _spriteOffset;
	spriteCount = _spriteCount;
	paletteId = _paletteId;
	passable = _passable;
	foreground = _foreground;
	mirrorX = _mirrorX;
	mirrorY = _mirrorY;
}
void StaticObject::SetSprite(char* _spriteId, Vector2* _spriteOffset, char _spriteCount)
{
	spriteId = _spriteId;
	spriteOffset = _spriteOffset;
	spriteCount = _spriteCount;
}

void StaticObject::SetPassable(bool _passable)
{
	passable = _passable;
}

void StaticObject::SetForeground(bool _foreground)
{
	foreground = _foreground;
}

char* StaticObject::GetSprite()
{
	return spriteId;
}

Vector2* StaticObject::GetSpriteOffset()
{
	return spriteOffset;
}

unsigned char StaticObject::GetSpriteCount()
{
	return spriteCount;
}

bool StaticObject::GetPassable()
{
	return passable;
}

bool StaticObject::GetForeground()
{
	return foreground;
};