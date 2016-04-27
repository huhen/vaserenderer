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
