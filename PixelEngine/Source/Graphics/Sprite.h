#pragma once

#include <cstdint>

struct Sprite
{
	union
	{
		struct
		{
			uint32_t
				x0y0 : 2,
				x1y0 : 2,
				x2y0 : 2,
				x3y0 : 2,
				x4y0 : 2,
				x5y0 : 2,
				x6y0 : 2,
				x7y0 : 2,
				x0y1 : 2,
				x1y1 : 2,
				x2y1 : 2,
				x3y1 : 2,
				x4y1 : 2,
				x5y1 : 2,
				x6y1 : 2,
				x7y1 : 2;
			uint32_t
				x0y2 : 2,
				x1y2 : 2,
				x2y2 : 2,
				x3y2 : 2,
				x4y2 : 2,
				x5y2 : 2,
				x6y2 : 2,
				x7y2 : 2,
				x0y3 : 2,
				x1y3 : 2,
				x2y3 : 2,
				x3y3 : 2,
				x4y3 : 2,
				x5y3 : 2,
				x6y3 : 2,
				x7y3 : 2;
			uint32_t
				x0y4 : 2,
				x1y4 : 2,
				x2y4 : 2,
				x3y4 : 2,
				x4y4 : 2,
				x5y4 : 2,
				x6y4 : 2,
				x7y4 : 2,
				x0y5 : 2,
				x1y5 : 2,
				x2y5 : 2,
				x3y5 : 2,
				x4y5 : 2,
				x5y5 : 2,
				x6y5 : 2,
				x7y5 : 2;
			uint32_t
				x0y6 : 2,
				x1y6 : 2,
				x2y6 : 2,
				x3y6 : 2,
				x4y6 : 2,
				x5y6 : 2,
				x6y6 : 2,
				x7y6 : 2,
				x0y7 : 2,
				x1y7 : 2,
				x2y7 : 2,
				x3y7 : 2,
				x4y7 : 2,
				x5y7 : 2,
				x6y7 : 2,
				x7y7 : 2;
		};
		struct {
			uint32_t
				i32_1,
				i32_2,
				i32_3,
				i32_4;
		};
	};
};