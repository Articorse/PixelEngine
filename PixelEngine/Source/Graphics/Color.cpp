#include "Color.h"

Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
	transparent = true;
}

Color::Color(unsigned char _r, unsigned char _g, unsigned char _b)
{
	r = _r;
	g = _g;
	b = _b;
	transparent = false;
}

void Color::SetColor(unsigned char _r, unsigned char _g, unsigned char _b)
{
	r = _r;
	g = _g;
	b = _b;
	transparent = false;
}

void Color::SetTransparent()
{
	transparent = true;
}

void Color::SetOpaque()
{
	transparent = false;
}

void Color::ToggleTransparency()
{
	transparent = !transparent;
}

