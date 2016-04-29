#include "GLContext.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

/*PFNGLUSEPROGRAMPROC glUseProgram;
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
PFNGLDELETEBUFFERSPROC glDeleteBuffers;*/
/*
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
*/
/*
bool WGLisExtensionSupported(const char *extension)
{
	const size_t extlen = strlen(extension);
	const char *supported = NULL;

	// ������� ������������ wglGetExtensionStringARB �� ������� ���������, ���� ��������
	PROC wglGetExtString = wglGetProcAddress("wglGetExtensionsStringARB");

	if (wglGetExtString)
		supported = ((char*(__stdcall*)(HDC))wglGetExtString)(wglGetCurrentDC());

	// ����  �������� �� ��������, �� ���������� ������������ ����������� ���������� OpenGL
	if (supported == NULL)
		supported = (char*)glGetString(GL_EXTENSIONS);

	// ���� � ��� �� ��������������, ����� �������� ��� ����������
	if (supported == NULL)
		return false;

	// �������� �������� � ������ ������, ����������� �� 1, ��� false ����������
	for (const char* p = supported; ; p++)
	{
		// ���������� p �� ���������� ���������� ����������
		p = strstr(p, extension);

		if (p == NULL)
			return false; // ���������� ���

						  //��������, ��� ���� ���������� � ������ ������,
						  //��� ������ ������ � ������, ��� ����� ���� ���������
						  //���������� "wglFunkywglExtension" � "wglExtension"

						  // ����� ��������, ��� ������� ������ ������ ��� ������
						  // ��� ��� "wglExtensionTwo" ����� �������� � "wglExtension"
		if ((p == supported || p[-1] == ' ') && (p[extlen] == '\0' || p[extlen] == ' '))
			return true; // ����������
	}
}
*/
/*
bool GLContext::InitMultisample()
{
	// ���������, ���� �� ������ � WGL!
	if (!WGLisExtensionSupported("WGL_ARB_multisample"))
	{
		printf("WGL_ARB_multisample not found\n");
		arbMultisampleSupported = false;
		return false;
	}

	// ������� ��� ������ �������
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB =
		(PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

	if (!wglChoosePixelFormatARB)
	{
		printf("�� �� ����� ��������� ��� ������ ������������� �������, �������� ��� ���� � ������.\n");
		// �� �� ����� ��������� ��� ������ ������������� �������, �������� ��� ���� � ������.
		arbMultisampleSupported = false;
		return false;
	}

	

	// �������� �������� ������ ����������. ��� ��� ���������� ��� ����, ���
	// �������� � OpenGL ����, ����� �������� � ��� ����
	//HDC hDC = GetDC(hWnd);

	int pixelFormat;
	bool valid;
	UINT numFormats;
	float fAttributes[] = { 0,0 };

	// ��� �������� � ����, ������� �� ����� �������������� � ����� ����
	// ��� �������� ����������, ������ ���� �� ��� �� �����
	// ������������� ��������������� - ��� SAMPLE BUFFERS ARB � WGL SAMPLES
	// ��� �������� ������� �������� �� �������: ���� ��� ���
	// � ��� ��������� ������������� �������
	int iAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB,GL_TRUE, // �������, ���� ������ ������� ����� ���� ����������� � ����
		WGL_SUPPORT_OPENGL_ARB,GL_TRUE, // �������, ���� �������������� OpenGL
		WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB, // ������ ���������� ���������
		WGL_COLOR_BITS_ARB,24,          // ���������
		WGL_ALPHA_BITS_ARB,8,           // ����������� �����-������
		WGL_DEPTH_BITS_ARB,16,          // ������� ������ �������
		WGL_STENCIL_BITS_ARB,0,         // ������� ������ �������
		WGL_DOUBLE_BUFFER_ARB,GL_TRUE,  // ������, ���� ������������ ������� �����������
		WGL_SAMPLE_BUFFERS_ARB,GL_TRUE, // ��� �� � �����
		WGL_SAMPLES_ARB, 4 ,            // �������� �� 4x ���
		0,0 };

	// ������� ���������, ������ �� �� �������� ������ ������� ��� 4x ����
	valid = wglChoosePixelFormatARB(mhDC, iAttributes, fAttributes, 1, &pixelFormat, &numFormats);

	// ���� ��������� True, � ��� ������� �������� ������ 1
	if (valid && numFormats >= 1)
	{
		printf("found 4x multisample\n");
		arbMultisampleSupported = true;
		arbMultisampleFormat = pixelFormat;
		return arbMultisampleSupported;
	}

	// ������ ������� � 4x �������� �����������, ��������� �� 2x ���
	iAttributes[19] = 2;
	valid = wglChoosePixelFormatARB(mhDC, iAttributes, fAttributes, 1, &pixelFormat, &numFormats);
	if (valid && numFormats >= 1)
	{
		printf("������ �������� ������ ������� ��� 2x ����\n");
		arbMultisampleSupported = true;
		arbMultisampleFormat = pixelFormat;
		return arbMultisampleSupported;
	}
	printf("������ �� ������ �����\n");
	// ���������� ������ ������
	return  arbMultisampleSupported;
}
*/

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

/*void LoadPointers()
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
}*/

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
	// ! ������� ��������� ������
	vShader = glCreateShader(GL_VERTEX_SHADER);
	// ! �������� �������� ���
	glShaderSource(vShader, 1, (const GLchar **)&vsSource, NULL);
	// ! ����������� ������
	glCompileShader(vShader);

	checkShader(vShader);

	// ! ������� ����������� ������
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	// ! �������� �������� ���
	glShaderSource(fShader, 1, (const GLchar **)&fsSource, NULL);
	// ! ����������� ������
	glCompileShader(fShader);

	checkShader(fShader);

	// ! ������� ��������� � ����������� ������� � ���
	Program = glCreateProgram();
	glAttachShader(Program, vShader);
	glAttachShader(Program, fShader);

	// ! ������� ��������� ���������
	glLinkProgram(Program);
}

void GLContext::freeShader()
{
	// ! ��������� ����, �� ��������� �������� ���������
	glUseProgram(0);
	// ! ������� ��������� ���������
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

	if (WGLEW_ARB_create_context && WGLEW_ARB_pixel_format)
	{
		const int iPixelFormatAttribList[] = {
			WGL_DRAW_TO_WINDOW_ARB,GL_TRUE, // �������, ���� ������ ������� ����� ���� ����������� � ����
			WGL_SUPPORT_OPENGL_ARB,GL_TRUE, // �������, ���� �������������� OpenGL
			WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB, // ������ ���������� ���������
			WGL_COLOR_BITS_ARB,24,          // ���������
			WGL_ALPHA_BITS_ARB,8,           // ����������� �����-������
			WGL_DEPTH_BITS_ARB,16,          // ������� ������ �������
			WGL_STENCIL_BITS_ARB,0,         // ������� ������ �������
			WGL_DOUBLE_BUFFER_ARB,GL_TRUE,  // ������, ���� ������������ ������� �����������
			WGL_SAMPLE_BUFFERS_ARB,GL_TRUE, // ��� �� � �����
			WGL_SAMPLES_ARB, 4 ,            // �������� �� 4x ���
			0,0 };

		int iContextAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
			WGL_CONTEXT_MINOR_VERSION_ARB, 1,
			//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0 // End of attributes list
		};

		int iPixelFormat, iNumFormats;
		wglChoosePixelFormatARB(mhDC, iPixelFormatAttribList, NULL, 1, &iPixelFormat, (UINT*)&iNumFormats);

		//DescribePixelFormat(mhDC, iPixelFormat, sizeof(pfd), &pfd);
		printf("try SetPixelFormat pf=%d\n", iPixelFormat);
		// PFD seems to be only redundant parameter now
		if (!SetPixelFormat(mhDC, iPixelFormat, &pfd))
		{
			printf("fail SetPixelFormat pf=%d\n", iPixelFormat);
			return;
		}
		mhRC = wglCreateContextAttribsARB(mhDC, 0, iContextAttribs);
		// If everything went OK
		if (mhRC) {
			if (wglMakeCurrent(mhDC, mhRC) == FALSE)
			{
				// �� �������
				printf("Fail wglMakeCurrent\n");
				return;
			}
			printf("wglCreateContextAttribsARB OK\n");

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glEnable(GL_ALPHA_TEST);
			//glShadeModel(GL_SMOOTH);

			/*glEnable(GL_LINE_SMOOTH);
			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

			glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
			glEnable(GL_POLYGON_SMOOTH);

			glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
			glEnable(GL_POINT_SMOOTH);*/
			
		}
	}
	/*
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

	// ������� �������� ������������ ����� ������� ����������
	if (wglMakeCurrent(mhDC, mhRC) == FALSE)
	{
		// �� �������
		printf("Fail wglMakeCurrent\n");
		return; 
	}

/*	if (InitMultisample())
	{
		/*PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
			(PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

		if (!wglCreateContextAttribsARB)
		{
			printf("!wglCreateContextAttribsARB.\n");
			// �� �� ����� ��������� ��� ������ ������������� �������, �������� ��� ���� � ������.
			arbMultisampleSupported = false;
			return;
		}
		int attribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 1,
			WGL_CONTEXT_FLAGS_ARB, 0,
			0
		};
		HGLRC m_hrc = wglCreateContextAttribsARB(mhDC, 0, attribs);

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(mhRC);

		wglMakeCurrent(mhDC, m_hrc);
		mhRC = m_hrc;
		
		memset(&pfd, 0, sizeof(pfd));
		/* now this is a kludge; we need to pass something in the
		* PIXELFORMATDESCRIPTOR to SetPixelFormat; it will be ignored,
		* mostly. OTOH we want to send something sane, we're nice
		* people after all - it doesn't hurt if this fails. 
		DescribePixelFormat(mhDC, arbMultisampleFormat, sizeof(pfd), &pfd);
		printf("try SetPixelFormat pf=%d\n", arbMultisampleFormat);
		if (SetPixelFormat(mhDC, arbMultisampleFormat, &pfd) == FALSE)
		{
			// �� �������
			printf("Fail SetPixelFormat  Multisample\n");
			return;
		}
		mhRC = wglCreateContext(mhDC);
		if (mhRC) {
			if (wglMakeCurrent(mhDC, mhRC) == FALSE)
			{
				// �� �������
				printf("Fail wglMakeCurrent 2\n");
				return;
			}
		}
		else
		{
			printf("Fail wglCreateContext 2\n");
		}
		printf("InitMultisample OK\n");
	}*/
	// make it the current render context
	//MakeCurrent();

	//LoadPointers();
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

