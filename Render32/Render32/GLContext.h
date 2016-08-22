#pragma once

#include "stdafx.h"

#ifdef RENDER32_EXPORTS
#define RENDER32_1API __declspec(dllexport)
#else
#define RENDER32_1API __declspec(dllimport)
#endif

class RENDER32_1API GLContext
{
public:
	GLContext();

	~GLContext();

	void init(HWND hWnd);

	void purge();

	void MakeCurrent();

	bool IsCurrent();

	void SwapBuffersContext();

	void initShader();
	void freeShader();

	GLuint Program;
	//bool InitMultisample();

private:

	void reset();

	HWND mhWnd;
	HDC mhDC;
	HGLRC mhRC;

	GLuint vShader, fShader;
	bool arbMultisampleSupported = false;
	int  arbMultisampleFormat = 0;
};

