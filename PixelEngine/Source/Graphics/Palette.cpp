#include "Palette.h"

Palette::Palette(Color _c1, Color _c2, Color _c3)
{
	colors[0] = Color();
	colors[1] = _c1;
	colors[2] = _c2;
	colors[3] = _c3;
}

Color Palette::operator[] (const int index)
{
	if (index >= 0 && index < 4)
	{
		return colors[index];
	}
	else
	{
		throw "Invalid color index requested!";
	}
}