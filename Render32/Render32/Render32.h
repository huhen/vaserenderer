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

typedef unsigned int uint;
RENDER32_API void test_draw(void);


class RENDER32_API UnmanagedClass {
public:
	static void DeleteTexture(uint tId);
	static void TexImage2D(int width, int heigh, const void *pixels);
	static void DrawSimplePolyLine(const float *pointer, int count, float width, uint color);
	static void DrawSimplePoint(float x, float y, float width, uint color);
	static void DrawSimplePolygone(const float *pointer, int count, float width, uint color);
};
