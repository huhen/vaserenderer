// Render32.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "Render32.h"


// Пример экспортированной переменной
RENDER32_API int nRender32=0;

// Пример экспортированной функции.
RENDER32_API int fnRender32(void)
{
    return 42;
}

// Конструктор для экспортированного класса.
// см. определение класса в Render32.h
CRender32::CRender32()
{
    return;
}
