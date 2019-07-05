#pragma once

class Color
{
public:
	Color();
	Color(unsigned char _r, unsigned char _g, unsigned char _b);

	void SetColor(unsigned char _r, unsigned char _g, unsigned char _b);
	void SetTransparent();
	void SetOpaque();
	void ToggleTransparency();

	unsigned char r;
	unsigned char g;
	unsigned char b;
	bool transparent;
};