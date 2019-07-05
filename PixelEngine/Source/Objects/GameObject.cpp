#include "GameObject.h"

void GameObject::SetPos(Vector2 _pos)
{
	if (_pos.x < 0 || _pos.y < 0)
	{
		_pos = Vector2();
	}
	pos = _pos;
}

void GameObject::SetPaletteId(char _paletteId)
{
	paletteId = _paletteId;
}

Vector2 GameObject::GetPos()
{
	return pos;
}

char GameObject::GetPaletteId()
{
	return paletteId;
}
