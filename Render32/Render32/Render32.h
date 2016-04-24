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

// Этот класс экспортирован из Render32.dll
class RENDER32_API CRender32 {
public:
	CRender32(void);
	// TODO: Добавьте здесь свои методы.
};

extern RENDER32_API int nRender32;

RENDER32_API int fnRender32(void);
