#include "GameObject.h"

void GameObject::SetPos(Vector2 _pos)
{
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
