#pragma once

#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject();
	StaticObject(Vector2 _pos, char* _spriteId, Vector2* spriteOffset, unsigned char _spriteCount, char _paletteId, bool _passable = false, bool _foreground = false, bool _mirrorX = false, bool _mirrorY = false);

	//void SetPos(Vector2 _pos);
	//void SetPaletteId(char _paletteId);
	void SetSprite(char* _spriteId, Vector2* _spriteOffset, char spriteCount);
	void SetPassable(bool _passable);
	void SetForeground(bool _foreground);

	//Vector2 GetPos();
	//char GetPaletteId();
	char* GetSprite();
	Vector2* GetSpriteOffset();
	unsigned char GetSpriteCount();
	bool GetPassable();
	bool GetForeground();

	bool mirrorX;
	bool mirrorY;

private:
	//Vector2 pos;
	//char paletteId;
	char* spriteId;
	Vector2* spriteOffset;
	unsigned char spriteCount;
	bool passable;
	bool foreground;
};