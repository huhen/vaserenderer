#ifndef VASER_GRADIENT_H
#define VASER_GRADIENT_H

#include "vaser.h"

namespace VASEr
{
	namespace VASErin
	{	//VASEr internal namespace

		double grad_getstep(double A, double B, double t, double T);

		void gradient_apply(const gradient* gradp, Color* C, double* W, const double* L, int length, double path_length);

	} //sub namespace VASErin

}

#endif
