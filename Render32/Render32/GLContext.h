#pragma once

#include "stdafx.h"


class GLContext
{
public:
	GLContext();

	~GLContext();

	void init(HWND hWnd);

	void purge();

private:

	void reset();

	HWND mhWnd;
	HDC mhDC;
	HGLRC mhRC;
};

