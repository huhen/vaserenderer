#pragma once

#include "stdafx.h"


class GLContext
{
public:
	GLContext();

	~GLContext();

	void init(HWND hWnd);

	void purge();

	void MakeCurrent();

	bool IsCurrent();

	void SwapBuffersContext();

private:

	void reset();

	HWND mhWnd;
	HDC mhDC;
	HGLRC mhRC;
};

