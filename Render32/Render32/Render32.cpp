// Render32.cpp: ���������� ���������������� ������� ��� ���������� DLL.
//

#include "stdafx.h"
#include "Render32.h"


// ������ ���������������� ����������
RENDER32_API int nRender32=0;

// ������ ���������������� �������.
RENDER32_API int fnRender32(void)
{
    return 42;
}

// ����������� ��� ����������������� ������.
// ��. ����������� ������ � Render32.h
CRender32::CRender32()
{
    return;
}
