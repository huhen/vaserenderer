#ifndef VASER_GRADIENT_H
#define VASER_GRADIENT_H

#include "vaser.h"

namespace VASEr
{
	namespace VASErin
	{	//VASEr internal namespace

		TFLOAT grad_getstep(TFLOAT A, TFLOAT B, TFLOAT t, TFLOAT T);

		void gradient_apply(const gradient* gradp, Color* C, TFLOAT* W, const TFLOAT* L, int length, TFLOAT path_length);

	} //sub namespace VASErin

}

#endif
