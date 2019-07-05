#pragma once

#include "Color.h"

class Palette
{
public:
	Palette(const Color _c1, const Color _c2, const Color _c3);

	Color operator[] (const int index);

private:
	Color colors[4];
};