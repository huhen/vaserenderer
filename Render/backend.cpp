#include <windows.h>
#include <gl/GL.h>

#include "includes/backend.h"

namespace VASEr
{
	namespace VASErin
	{
		void backend::vah_draw(vertex_array_holder& vah)
		{
			if (vah.count > 0) //save some effort
			{
				glVertexPointer(2, GL_FLOAT, 0, &vah.vert[0]);
				glColorPointer(4, GL_FLOAT, 0, &vah.color[0]);
				glDrawArrays(vah.glmode, 0, vah.count);
			}
		}

		void backend::polyline(const Vec2* P, Color C, float W, int length, const polyline_opt*) //constant color and weight
		{
			int type = 0;
			if (sizeof(Vec2) == 16)
				type = GL_DOUBLE;
			else if (sizeof(Vec2) == 8)
				type = GL_FLOAT;

			glColor4f(C.r, C.g, C.b, C.a);
			glLineWidth(W);
			if (type)
			{
				glEnableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_COLOR_ARRAY);
				glVertexPointer(2, type, 0, P);
				glDrawArrays(GL_LINE_STRIP, 0, length);
				glEnableClientState(GL_COLOR_ARRAY);
			}
			else
			{
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < length; i++)
					glVertex2f(P[i].x, P[i].y);
				glEnd();
			}
			glLineWidth(1);
		}

		void swap_pixel(unsigned char* img, int w, int x1, int y1, int x2, int y2)
		{
			const int b = 4;
			unsigned char R = img[y1*w*b + x1*b];
			unsigned char G = img[y1*w*b + x1*b + 1];
			unsigned char B = img[y1*w*b + x1*b + 2];
			unsigned char A = img[y1*w*b + x1*b + 3];

			img[y1*w*b + x1*b] = img[y2*w*b + x2*b];
			img[y1*w*b + x1*b + 1] = img[y2*w*b + x2*b + 1];
			img[y1*w*b + x1*b + 2] = img[y2*w*b + x2*b + 2];
			img[y1*w*b + x1*b + 3] = img[y2*w*b + x2*b + 3];

			img[y2*w*b + x2*b] = R;
			img[y2*w*b + x2*b + 1] = G;
			img[y2*w*b + x2*b + 2] = B;
			img[y2*w*b + x2*b + 3] = A;
		}
	}
}
