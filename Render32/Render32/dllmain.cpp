// dllmain.cpp: определяет точку входа для приложения DLL.
#include "stdafx.h"
#include <cstdio>

void InitOpenGL(HINSTANCE hInstance);

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		InitOpenGL(hModule);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Callback functions to handle all window functions this app cares about.
// Once complete, pass message on to next app in the hook chain.
LRESULT CALLBACK WndProc(HWND hWnd,  // Handle For This Window
	UINT uMsg,  // Message For This Window
	WPARAM wParam,  // Additional Message Information
	LPARAM lParam)  // Additional Message Information
{
	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

static const TCHAR g_szAppName[] = TEXT("Pixel Format Test");
static const TCHAR g_szClassName[] = TEXT("OGL_PIXEL_FORMAT_TEST_CLASS");

//static const int g_nWinWidth = 800;
//static const int g_nWinHeight = 600;

bool createTmpWindow()
{
	HINSTANCE g_hInstance = GetModuleHandle(NULL);
	WNDCLASS     g_windClass;
	// setup window class
	g_windClass.lpszClassName = g_szClassName;                // Set the name of the Class
	g_windClass.lpfnWndProc = (WNDPROC)WndProc;
	g_windClass.hInstance = g_hInstance;                // Use this module for the module handle
	g_windClass.hCursor = LoadCursor(NULL, IDC_ARROW);// Pick the default mouse cursor
	g_windClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);// Pick the default windows icons
	g_windClass.hbrBackground = NULL;                       // No Background
	g_windClass.lpszMenuName = NULL;                       // No menu for this window
	g_windClass.style = CS_HREDRAW | CS_OWNDC |     // set styles for this class, specifically to catch
		CS_VREDRAW;                 // window redraws, unique DC, and resize
	g_windClass.cbClsExtra = 0;                          // Extra class memory
	g_windClass.cbWndExtra = 0;                          // Extra window memory

														 // Register the newly defined class
	if (!RegisterClass(&g_windClass))
		return false;

	DWORD dwExtStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwWindStyle = WS_OVERLAPPEDWINDOW;

	int nWindowX = 0;
	int nWindowY = 0;
	RECT g_windowRect;
	g_windowRect.left = nWindowX;
	g_windowRect.right = nWindowX + 800;
	g_windowRect.top = nWindowY;
	g_windowRect.bottom = nWindowY + 600;

	// Setup window width and height
	AdjustWindowRectEx(&g_windowRect, dwWindStyle, FALSE, dwExtStyle);

	//Adjust for adornments
	int nWindowWidth = g_windowRect.right - g_windowRect.left;
	int nWindowHeight = g_windowRect.bottom - g_windowRect.top;

	// Create window
	HWND g_hWnd = CreateWindowEx(dwExtStyle,     // Extended style
		g_szClassName,    // class name
		g_szAppName,   // window name
		dwWindStyle |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN,// window stlye
		nWindowX,       // window position, x
		nWindowY,       // window position, y
		nWindowWidth,   // height
		nWindowHeight,  // width
		NULL,           // Parent window
		NULL,           // menu
		g_hInstance,    // instance
		NULL);          // pass this to WM_CREATE

						// now that we have a window, setup the pixel format descriptor
	HDC g_hDC = GetDC(g_hWnd);
	// Set a dummy pixel format so that we can get access to wgl functions
	PIXELFORMATDESCRIPTOR pfdDummy;
	memset(&pfdDummy, 0, sizeof(pfdDummy));
	SetPixelFormat(g_hDC, 1, &pfdDummy);
	// Create OGL context and make it current
	HGLRC g_hRC = wglCreateContext(g_hDC);
	wglMakeCurrent(g_hDC, g_hRC);

	if (g_hDC == 0 ||
		g_hDC == 0)
	{
		printf("!!! An error accured creating an OpenGL window.\n");
		return false;
	}
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf("Error: %s\n", glewGetErrorString(err));
		return false;
	}
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(g_hRC);
	ReleaseDC(g_hWnd, g_hDC);
	DestroyWindow(g_hWnd);
}

void InitOpenGL(HINSTANCE hInstance)
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	printf("Debugging Window:\n");

	createTmpWindow();

	
}
