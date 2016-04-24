#ifndef VASER_RENDERER_H
#define VASER_RENDERER_H

#include "vaser.h"

namespace VASEr
{
	class renderer
	{
	public:
		static void init();
		static void before();
		static void after();
		static Image get_image();
	};
}

#endif
