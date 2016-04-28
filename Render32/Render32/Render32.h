#pragma once
// Приведенный ниже блок ifdef - это стандартный метод создания макросов, упрощающий процедуру 
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа RENDER32_EXPORTS,
// в командной строке. Этот символ не должен быть определен в каком-либо проекте
// использующем данную DLL. Благодаря этому любой другой проект, чьи исходные файлы включают данный файл, видит 
// функции RENDER32_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef RENDER32_EXPORTS
#define RENDER32_API __declspec(dllexport)
#else
#define RENDER32_API __declspec(dllimport)
#endif

#include "GLContext.h"


typedef unsigned int uint;
typedef signed char ibyte;
typedef unsigned char ubyte;

RENDER32_API void test_draw(void);


class RENDER32_API UnmanagedClass {
public:
	static void DeleteTexture(uint tId);
	static uint TexImage2D(int width, int heigh, const void *pixels);
	static void DrawSimplePolyLine(const float *pointer, int count, float width, uint color);
	static void DrawSimplePoint(float x, float y, float width, uint color);
	static void DrawSimplePolygone(const float *pointer, int count, float width, uint color);
	static void RenderTexture(uint tId, const float *vertextArray);
	static void RenderTexture(uint tId, float x, float y, float orientation, float scale, float opacity, const float *vertextArray);
	static void SetupViewPort(int width, int heigh);
	static void Clear();
	static void DrawFinePolyLine(const float *pointer, int count, float width, uint color);

	void Init(HWND hWnd);
	void DeleteContext();
	void SwapBuffersContext();
private:
	GLContext _context;
};
