// Render32.cpp: ���������� ���������������� ������� ��� ���������� DLL.
//

#include "stdafx.h"
#include "Render32.h"

#include "GLContext.h"

#include "../../Render/includes/vaser.h"
#include "../../Render/includes/renderer.h"

const int buf_size = 20;
VASEr::Vec2 AP[buf_size];
int size_of_AP = 0;
VASEr::Color AC[buf_size];
double AW[buf_size];

GLContext _context;

#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif // !GL_BGRA

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif // !GL_CLAMP_TO_EDGE

float TextureArray[] = { 0, 0, 1, 0, 1, 1, 0, 1 };

void UnmanagedClass::RenderTexture(uint tId, const float *vertextArray)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tId);

	glColor4b(255ui8, 255ui8, 255ui8, 255ui8);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, vertextArray);
	glTexCoordPointer(2, GL_FLOAT, 0, &TextureArray);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void UnmanagedClass::RenderTexture(uint tId, float x, float y, float orientation, float scale, float opacity, const float *vertextArray)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tId);
	glPushMatrix();

	glTranslatef(x, y, 0);
	glRotatef(orientation, 0, 0, 1);
	glScalef(scale, scale, 1);

	glColor4b(255ui8, 255ui8, 255ui8, ubyte(255.0f * opacity));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, vertextArray);
	glTexCoordPointer(2, GL_FLOAT, 0, &TextureArray);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_BLEND);

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void UnmanagedClass::DeleteTexture(uint tId)
{
	glBindTexture(GL_TEXTURE_2D, tId);
	glDeleteTextures(1, &tId);
}

uint UnmanagedClass::TexImage2D(int width, int heigh, const void *pixels)
{
	uint id;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigh, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	return id;
}

void UnmanagedClass::DrawSimplePolyLine(const float *pointer, int count, float width, uint color)
{
	glLineWidth(width);
	glColor4b(color >> 16, color >> 8, color, color >> 24);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, pointer);
	glDrawArrays(GL_LINE_STRIP, 0, count);
	glDisableClientState(GL_VERTEX_ARRAY);
}


void UnmanagedClass::DrawSimplePolygone(const float *pointer, int count, float width, uint color)
{
	glLineWidth(width);
	glColor4b(color >> 16, color >> 8, color, color >> 24);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, pointer);
	glDrawArrays(GL_LINE_LOOP, 0, count);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void UnmanagedClass::DrawSimplePoint(float x, float y, float width, uint color)
{
	float p[2];
	p[0] = x;
	p[1] = y;
	glPointSize(width);
	glColor4b(color >> 16, color >> 8, color, color >> 24);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &p);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableClientState(GL_VERTEX_ARRAY);
}

RENDER32_API void test_draw(void)
{
	VASEr::polyline_opt opt = { 0 };
	VASEr::tessellator_opt tess = { 0 };
	opt.feather = false;
	opt.feathering = 0.0;
	opt.no_feather_at_cap = false;
	opt.no_feather_at_core = false;
	opt.joint = VASEr::PLJ_bevel;
	opt.cap = VASEr::PLC_none;
	opt.tess = &tess;
	tess.triangulation = false;

	AP[0].x = -10000; AP[0].y = 10000;
	AP[1].x = 0; AP[1].y = 0;
	AP[2].x = 10000; AP[2].y = 10000;
	AP[3].x = 10000; AP[3].y = 0;
	AP[4].x = 0; AP[4].y = 10000;
	AP[5].x = 100000; AP[5].y = 100000;
	AP[6].x = 100000; AP[6].y = 0;
	AP[7].x = 0; AP[7].y = 1000000;
	AP[8].x = 1000000; AP[8].y = 0;
	AP[9].x = 1000000; AP[9].y = 1000000;
	AP[10].x = 0; AP[10].y = 0;
	AP[11].x = 10000000; AP[11].y = 10000000;
	AP[12].x = 10000000; AP[12].y = 0;
	AP[13].x = 0; AP[13].y = 10000000;
	size_of_AP = 14;

	VASEr::Color grey = { .4f,.4f,.4f, 1.0f };
	/*for (int i = 0; i < size_of_AP; i++)
	{
		AC[i] = grey;
		AW[i] = 8.0;
	}*/
	AC[0] = grey;
	AW[0] = 8.0f;
	TFLOAT w = 8.0f;
	VASEr::renderer::before();
	VASEr::polyline(AP, grey, w, size_of_AP, &opt);
	VASEr::renderer::after();
}

