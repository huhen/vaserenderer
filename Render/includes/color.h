#ifndef VASER_COLOR_H
#define VASER_COLOR_H

#include "vaser.h"

namespace VASEr
{
	float& Color_get(Color& C, int index);

	bool Color_valid_range(float t);

	Color Color_between(const Color& A, const Color& B, float t = 0.5f);

	void sRGBtolinear(Color& C, bool exact = false); //de-Gamma 2.2

	void lineartosRGB(Color& C, bool exact = false); //Gamma 2.2

	float color_max(float r, float g, float b);

	float color_min(float r, float g, float b);

	void RGBtoHSV(float r, float g, float b, float *h, float *s, float *v);

	void HSVtoRGB(float *r, float *g, float *b, float h, float s, float v);
}

#endif
