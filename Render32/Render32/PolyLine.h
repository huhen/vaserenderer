#pragma once
#include "stdafx.h"

class PolyLine
{
public:
	static void Draw(const float *pointer, int count, float width, unsigned int color);
	static void Draw(const float *pointer, int count, float width, unsigned int color, unsigned int colorC);
};

