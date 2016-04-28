#ifndef VASER_BACKEND_H
#define VASER_BACKEND_H

#include "vaser.h"
#include "vertex_array_holder.h"

namespace VASEr
{
	namespace VASErin
	{
		class backend
		{
		public:
			static void vah_draw(vertex_array_holder& vah);
			static void polyline(const Vec2* P, Color C, float W, int length, const polyline_opt*); //constant color and weight
		};

		void swap_pixel(unsigned char* img, int w, int x1, int y1, int x2, int y2);
	}
}

#endif
