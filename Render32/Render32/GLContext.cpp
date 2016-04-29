#include "GLContext.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;

void *GetAnyGLFuncAddress(const char *name)
{
	void *p = (void *)wglGetProcAddress(name);
	if (p == 0 ||
		(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
		(p == (void*)-1))
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = (void *)GetProcAddress(module, name);
	}

	return p;
}
unsigned long getFileLength(ifstream& file)
{
	if (!file.good()) return 0;

	unsigned long pos = file.tellg();
	file.seekg(0, ios::end);
	unsigned long len = file.tellg();
	file.seekg(ios::beg);

	return len;
}

GLubyte* load(char* filename)
{
	ifstream file;
	file.open(filename, ios::in);
	if (!file) return 0;

	unsigned long len = getFileLength(file);

	GLubyte* ShaderSource = (GLubyte*) new char[len + 1];
	ShaderSource[len] = 0;
	unsigned int i = 0;
	while (file.good())
	{
		ShaderSource[i] = file.get();       // get character from file.
		if (!file.eof())
			i++;
	}

	ShaderSource[i] = 0;  // 0 terminate it.
	file.close();
	return ShaderSource;
}

void LoadPointers()
{
	glUseProgram = (PFNGLUSEPROGRAMPROC)GetAnyGLFuncAddress("glUseProgram");
	glCreateShader = (PFNGLCREATESHADERPROC)GetAnyGLFuncAddress("glCreateShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)GetAnyGLFuncAddress("glCreateProgram");
	glShaderSource = (PFNGLSHADERSOURCEPROC)GetAnyGLFuncAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)GetAnyGLFuncAddress("glCompileShader");
	glAttachShader = (PFNGLATTACHSHADERPROC)GetAnyGLFuncAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)GetAnyGLFuncAddress("glLinkProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)GetAnyGLFuncAddress("glDeleteProgram");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)GetAnyGLFuncAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GetAnyGLFuncAddress("glGetShaderInfoLog");

	glGenBuffers = (PFNGLGENBUFFERSPROC)GetAnyGLFuncAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)GetAnyGLFuncAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)GetAnyGLFuncAddress("glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)GetAnyGLFuncAddress("glDeleteBuffers");
}
void checkShader(GLuint ShaderObj)
{
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, sizeof(InfoLog), NULL, InfoLog);

		printf("Error compiling shader type %d: '%s'\n", 0, InfoLog);
	}else
	{
		printf("Shader ok\n");
	}
}

void GLContext::initShader()
{

	GLubyte* vsSource = load("solid-lines-2D.vert");
	GLubyte* fsSource = load("solid-lines-2D.frag");
	// ! Создаем вершинный шейдер
	vShader = glCreateShader(GL_VERTEX_SHADER);
	// ! Передаем исходный код
	glShaderSource(vShader, 1, (const GLchar **)&vsSource, NULL);
	// ! Компилируем шейдер
	glCompileShader(vShader);

	checkShader(vShader);

	// ! Создаем фрагментный шейдер
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	// ! Передаем исходный код
	glShaderSource(fShader, 1, (const GLchar **)&fsSource, NULL);
	// ! Компилируем шейдер
	glCompileShader(fShader);

	checkShader(fShader);

	// ! Создаем программу и прикрепляем шейдеры к ней
	Program = glCreateProgram();
	glAttachShader(Program, vShader);
	glAttachShader(Program, fShader);

	// ! Линкуем шейдерную программу
	glLinkProgram(Program);
}

void GLContext::freeShader()
{
	// ! Передавая ноль, мы отключаем шейдрную программу
	glUseProgram(0);
	// ! Удаляем шейдерную программу
	glDeleteProgram(Program);
}

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

void GLContext::SwapBuffersContext()
{
	SwapBuffers(mhDC);
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
		32,                    // 24-bit color depth  
		0, 0, 0, 0, 0, 0,      // color bits ignored  
		8,                     // 8-bit alpha buffer  
		0,                     // shift bit ignored  
		0,                     // no accumulation buffer  
		0, 0, 0, 0,            // accum bits ignored  
		16,                    // 16-bit z-buffer  
		8,                     // no stencil buffer  
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

	LoadPointers();
	//initShader();
}

void GLContext::purge()
{
	if (mhRC)
	{
		freeShader();
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

