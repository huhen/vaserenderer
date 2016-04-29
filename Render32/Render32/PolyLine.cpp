#include "PolyLine.h"
#include <math.h>
#include <cstdio>
#include <vector>


/*namespace VASEr
{
	struct Vec2 { float x, y; };
	struct Color { float r, g, b, a; };
}
#include "../vaser/vaser.cpp"
using namespace VASEr;*/

struct box4 { float x1, y1, x2, y2, x3, y3, x4, y4; };
struct point { float x, y; };
struct line { float x1, y1, x2, y2; };

bool intersection(struct line* line1, struct line* line2, struct point* out_intersection)
{
	point dir1 = { line1->x2 - line1->x1, line1->y2 - line1->y1 };
	point dir2 = { line2->x2 - line2->x1, line2->y2 - line2->y1 };

	//считаем уравнения прямых проходящих через отрезки
	float a1 = -dir1.y;
	float b1 = +dir1.x;
	float d1 = -(a1 * line1->x1 + b1 * line1->y1);

	float a2 = -dir2.y;
	float b2 = +dir2.x;
	float d2 = -(a2 * line2->x1 + b2 * line2->y1);

	//подставляем концы отрезков, для выяснения в каких полуплоскотях они
	float seg1_line2_start = a2 * line1->x1 + b2 * line1->y1 + d2;
	float seg1_line2_end = a2 * line1->x2 + b2 * line1->y2 + d2;

	float seg2_line1_start = a1 * line2->x1 + b1 * line2->y1 + d1;
	float seg2_line1_end = a1 * line2->x2 + b1 * line2->y2 + d1;

	//если концы одного отрезка имеют один знак, значит он в одной полуплоскости и пересечения нет.
	if (((seg1_line2_start * seg1_line2_end) >= 0.0f) || ((seg2_line1_start * seg2_line1_end) >= 0.0f)) return false;

	float u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
	out_intersection->x = line1->x1 + u * dir1.x;
	out_intersection->y = line1->y1 + u * dir1.y;

	if (isnan(out_intersection->x) || isnan(out_intersection->y)) return false;
	return true;
}

void PolyLine::Draw(const float *pointer, int count, float width, unsigned int color)
{
	box4* pBoxs = new box4[count - 1];

	float lastX = pointer[0];
	float lastY = pointer[1];

	//printf("count=%d\n", count);

	size_t ii = 2;
	for (size_t i = 0; i < count - 1; i++)
	{
		float curX = pointer[ii];
		ii++;
		float curY = pointer[ii];
		ii++;

		float vectX = curX - lastX;
		float vectY = curY - lastY;
		float len = (float)sqrt(vectY * vectY + vectX * vectX) / width;

		float t = vectX / len;
		float tt = vectY / len;

		pBoxs[i].x1 = lastX - tt;
		pBoxs[i].y1 = t + lastY;
		pBoxs[i].x2 = curX - tt;
		pBoxs[i].y2 = t + curY;
		pBoxs[i].x3 = tt + curX;
		pBoxs[i].y3 = curY - t;
		pBoxs[i].x4 = tt + lastX;
		pBoxs[i].y4 = lastY - t;

		lastX = curX;
		lastY = curY;
		//printf("i=%d ii=%d %f %f\n", i, ii, lastX, lastY);
	}

	size_t curI = 0;
	point intersect;
	std::vector<unsigned int> indices;
	indices.reserve(count * 9);
	curI = 0;
	for (size_t i = 0; i < count - 2; i++)
	{
		if (intersection((line*)&pBoxs[i], (line*)&pBoxs[i + 1], &intersect))
		{
			pBoxs[i].x2 = intersect.x;
			pBoxs[i].y2 = intersect.y;
			pBoxs[i + 1].x1 = intersect.x;
			pBoxs[i + 1].y1 = intersect.y;

			indices.push_back(curI + 2);
			indices.push_back(curI + 1);
			indices.push_back(curI + 7);
		}
		else
		{
			if (intersection((line*)&pBoxs[i].x3, (line*)&pBoxs[i + 1].x3, &intersect))
			{
				pBoxs[i].x3 = intersect.x;
				pBoxs[i].y3 = intersect.y;
				pBoxs[i + 1].x4 = intersect.x;
				pBoxs[i + 1].y4 = intersect.y;

				indices.push_back(curI + 2);
				indices.push_back(curI + 1);
				indices.push_back(curI + 4);
			}
		}
		indices.push_back(curI);
		indices.push_back(curI + 1);
		indices.push_back(curI + 2);
		indices.push_back(curI + 2);
		indices.push_back(curI + 3);
		indices.push_back(curI);

		curI += 4;
	}
	indices.push_back(curI);
	indices.push_back(curI + 1);
	indices.push_back(curI + 2);
	indices.push_back(curI + 2);
	indices.push_back(curI + 3);
	indices.push_back(curI);

	//printf("indices.size=%d\n", indices.size());


	//glEnable(GL_MULTISAMPLE_ARB);
	//glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	//glEnable(GL_POLYGON_STIPPLE);
	// Сглаживание линий
	//glEnable(GL_POLYGON_SMOOTH);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	//glLineWidth(1);
	glColor4ubv((GLubyte*)&color);
	//glColor4ub(color >> 16, color >> 8, color, color >> 24);
	//glColor4f(1.0f / 255.0f * ((color >> 16) & 0xFF), 1.0f / 255.0f * ((color >> 8) & 0xFF), 1.0f / 255.0f * ((color)& 0xFF), 1.0f/255.0f*((color >> 24) & 0xFF));

	//glLineWidth(1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, pBoxs);

	/*GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);*/

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		&indices[0]           // element array buffer offset
		);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glDeleteBuffers(1, &elementbuffer);
	glDisableClientState(GL_VERTEX_ARRAY);

	/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, pointer);
	glIndexPointer();
	glDrawArrays(GL_TRIANGLES, 0, indices.size());
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);*/

	//glDisable(GL_BLEND);
	//glDisable(GL_POLYGON_SMOOTH);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	/*for (size_t i = 0; i < count - 1; i++)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		// Сглаживание линий
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
	}*/
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

