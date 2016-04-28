#include "GLContext.h"

GLContext::GLContext()
{
	reset();
}


GLContext::~GLContext()
{
	purge();
}

void GLContext::MakeCurrent()
{
	wglMakeCurrent(mhDC, mhRC);
}

bool GLContext::IsCurrent()
{
	HGLRC curent = wglGetCurrentContext();
	return (curent && curent == mhRC);
}

void GLContext::init(HWND hWnd)
{
	// remember the window handle (HWND)
	mhWnd = hWnd;

	// get the device context (DC)
	mhDC = GetDC(mhWnd);

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
		1,                     // version number  
		PFD_DRAW_TO_WINDOW |   // support window  
		PFD_SUPPORT_OPENGL |   // support OpenGL  
		PFD_DOUBLEBUFFER,      // double buffered  
		PFD_TYPE_RGBA,         // RGBA type  
		24,                    // 24-bit color depth  
		0, 0, 0, 0, 0, 0,      // color bits ignored  
		8,                     // 8-bit alpha buffer  
		0,                     // shift bit ignored  
		0,                     // no accumulation buffer  
		0, 0, 0, 0,            // accum bits ignored  
		16,                    // 16-bit z-buffer  
		0,                     // no stencil buffer  
		0,                     // no auxiliary buffer  
		PFD_MAIN_PLANE,        // main layer  
		0,                     // reserved  
		0, 0, 0                // layer masks ignored  
	};

	int format = ChoosePixelFormat(mhDC, &pfd);
	SetPixelFormat(mhDC, format, &pfd);

	// create the render context (RC)
	mhRC = wglCreateContext(mhDC);

	// make it the current render context
	MakeCurrent();
}

void GLContext::purge()
{
	if (mhRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(mhRC);
	}
	if (mhWnd && mhDC)
	{
		ReleaseDC(mhWnd, mhDC);
	}
	reset();
}

void GLContext::reset()
{
	mhWnd = NULL;
	mhDC = NULL;
	mhRC = NULL;
}

