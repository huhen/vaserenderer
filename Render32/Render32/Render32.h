#pragma once
// ����������� ���� ���� ifdef - ��� ����������� ����� �������� ��������, ���������� ��������� 
// �������� �� ��������� DLL. ��� ����� ������ DLL �������������� � �������������� ������� RENDER32_EXPORTS,
// � ��������� ������. ���� ������ �� ������ ���� ��������� � �����-���� �������
// ������������ ������ DLL. ��������� ����� ����� ������ ������, ��� �������� ����� �������� ������ ����, ����� 
// ������� RENDER32_API ��� ��������������� �� DLL, ����� ��� ������ DLL ����� �������,
// ������������ ������ ��������, ��� ����������������.
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
