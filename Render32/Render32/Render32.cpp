// Render32.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "Render32.h"
#include "../../Render/includes/vaser.h"
#include "../../Render/includes/renderer.h"

const int buf_size = 20;
VASEr::Vec2 AP[buf_size];
int size_of_AP = 0;
VASEr::Color AC[buf_size];
double AW[buf_size];

RENDER32_API void test_draw(void)
{
	VASEr::polyline_opt opt = { 0 };
	VASEr::tessellator_opt tess = { 0 };
	opt.feather = false;
	opt.feathering = 0.0;
	opt.no_feather_at_cap = false;
	opt.no_feather_at_core = false;
	opt.joint = VASEr::PLJ_bevel;
	opt.cap = VASEr::PLC_none;
	opt.tess = &tess;
	tess.triangulation = false;

	AP[0].x = 280; AP[0].y = 110;
	AP[1].x = 200; AP[1].y = 50;
	AP[2].x = 100; AP[2].y = 50;
	AP[3].x = 200; AP[3].y = 150;
	AP[4].x = 300; AP[4].y = 250;
	AP[5].x = 200; AP[5].y = 250;
	AP[6].x = 120; AP[6].y = 190;
	size_of_AP = 7;

	VASEr::Color grey = { .4f,.4f,.4f, 1.0f };
	/*for (int i = 0; i < size_of_AP; i++)
	{
		AC[i] = grey;
		AW[i] = 8.0;
	}*/
	AC[0] = grey;
	AW[0] = 8.0f;
	TFLOAT w=8.0f;
	VASEr::renderer::before();
	VASEr::polyline(AP, grey, w, size_of_AP, NULL);
	VASEr::renderer::after();
}

