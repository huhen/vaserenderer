#include "PolyLine.h"
#include <math.h>
#include <cstdio>
#include <vector>


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

void PolyLine::Draw(const float *pointer, int count, float width, unsigned int color, unsigned int colorC)
{
	box4* pBoxs = new box4[count - 1];

	float lastX = pointer[0];
	float lastY = pointer[1];

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
	}

	size_t curI = 0;
	point intersect;
	std::vector<unsigned int> indices;
	indices.reserve(count * 9);
	std::vector<unsigned int> indicesL;
	indicesL.reserve(count * 2);
	std::vector<unsigned int> indicesLz;
	indicesLz.reserve(count * 2);
	indicesL.push_back(3);
	indicesL.push_back(0);
	indicesLz.push_back(3);
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

			indicesL.push_back(curI + 1);
			indicesLz.push_back(curI + 2);
			indicesLz.push_back(curI + 7);
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

				indicesLz.push_back(curI + 2);
			}
			else
			{
				indicesLz.push_back(curI + 2);
				indicesLz.push_back(curI + 7);
			}

			indicesL.push_back(curI + 1);
			indicesL.push_back(curI + 4);
		}
		indices.push_back(curI);
		indices.push_back(curI + 1);
		indices.push_back(curI + 2);
		indices.push_back(curI + 2);
		indices.push_back(curI + 3);
		indices.push_back(curI);

		curI += 4;
	}
	indicesL.push_back(curI + 1);
	indicesL.push_back(curI + 2);
	indicesLz.push_back(curI + 2);

	indices.push_back(curI);
	indices.push_back(curI + 1);
	indices.push_back(curI + 2);
	indices.push_back(curI + 2);
	indices.push_back(curI + 3);
	indices.push_back(curI);

	/*printf("indicesLz.size=%d", indicesLz.size());
	if (indicesLz.size() > 0)
		for (size_t i = (indicesLz.size() - 1); i >= 0; i--)
		{
			indicesL.push_back(indicesLz[i]);
		}
	printf("end");*/

	glLineWidth(1);
	glColor4ubv((GLubyte*)&color);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, pBoxs);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		&indices[0]           // element array buffer offset
		);

	glColor4ubv((GLubyte*)&colorC);
	glDrawElements(
		GL_LINE_STRIP,      // mode
		indicesL.size(),    // count
		GL_UNSIGNED_INT,   // type
		&indicesL[0]           // element array buffer offset
		);

	glDrawElements(
		GL_LINE_STRIP,      // mode
		indicesLz.size(),    // count
		GL_UNSIGNED_INT,   // type
		&indicesLz[0]           // element array buffer offset
		);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void PolyLine::Draw(const float *pointer, int count, float width, unsigned int color)
{
	box4* pBoxs = new box4[count - 1];

	float lastX = pointer[0];
	float lastY = pointer[1];

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

	glLineWidth(1);
	glColor4ubv((GLubyte*)&color);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, pBoxs);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		&indices[0]           // element array buffer offset
		);

	glDisableClientState(GL_VERTEX_ARRAY);
}

