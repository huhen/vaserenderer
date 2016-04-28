#include "PolyLine.h"
#include <math.h>

/*namespace VASEr
{
	struct Vec2 { float x, y; };
	struct Color { float r, g, b, a; };
}
#include "../vaser/vaser.cpp"
using namespace VASEr;*/

struct box4 { float x1, y1, x2, y2, x3, y3, x4, y4; };

void PolyLine::Draw(const float *pointer, int count, float width, unsigned int color)
{
	box4* pBoxs = new box4[count - 1];

	float lastX = pointer[0];
	float lastY = pointer[1];

	for (size_t i = 2; i < count * 2; i += 2)
	{
		float curX = pointer[i];
		float curY = pointer[i + 1];

		float vectX = curX - lastX;
		float vectY = curY - lastY;
		float len = (float)sqrt(vectY * vectY + vectX * vectX) / width;

		float t = vectX / len;
		float tt = vectY / len;

		size_t curI = i / 2 - 1;

		pBoxs[curI].x1 = lastX - tt;
		pBoxs[curI].y1 = t + lastY;
		pBoxs[curI].x2 = curX - tt;
		pBoxs[curI].y2 = t + curY;
		pBoxs[curI].x3 = tt + curX;
		pBoxs[curI].y3 = curY - t;
		pBoxs[curI].x4 = tt + lastX;
		pBoxs[curI].y4 = lastY - t;

		lastX = curX;
		lastY = curY;
	}

	for (size_t i = 0; i < count - 1; i++)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		// —глаживание линий
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

		glLineWidth(1);
		//glColor4b(color >> 16, color >> 8, color, color >> 24);
		glColor4f(.0f, .0f, .0f, 1.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, &pBoxs[i]);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);

		glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);
	}
	/*
	VASEr::polyline_opt opt = { 0 };
	VASEr::tessellator_opt tess = { 0 };
	opt.feather = false;
	opt.feathering = 1.0;
	opt.no_feather_at_cap = false;
	opt.no_feather_at_core = false;
	opt.joint = VASEr::PLJ_bevel;
	opt.cap = VASEr::PLC_none;
	opt.tess = &tess;
	tess.triangulation = false;

	VASEr::Color colorf = { 1.0f * ((color >> 16) & 0xFF), 1.0f * ((color >> 8) & 0xFF), 1.0f * ((color)& 0xFF), 1.0f * ((color >> 24) & 0xFF) };
	VASEr::renderer::before();
	VASEr::polyline((VASEr::Vec2*)pointer, colorf, width, count, &opt);
	VASEr::renderer::after();*/
}

