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

// ���� ����� ������������� �� Render32.dll
class RENDER32_API CRender32 {
public:
	CRender32(void);
	// TODO: �������� ����� ���� ������.
};

extern RENDER32_API int nRender32;

RENDER32_API int fnRender32(void);
