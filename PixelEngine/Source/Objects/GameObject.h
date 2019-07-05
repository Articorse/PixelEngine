#pragma once

#include "../Math/Vector2.h"

class GameObject
{
public:
	void SetPos(Vector2 _pos);
	void SetPaletteId(char _paletteId);

	Vector2 GetPos();
	char GetPaletteId();

protected:
	Vector2 pos;
	char paletteId;
};