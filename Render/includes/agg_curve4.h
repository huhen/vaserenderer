#ifndef VASER_AGG_CURVE4_H
#define VASER_AGG_CURVE4_H
#include "vaser.h"

// this code is isolated from AGG,
// for cubic bezier curve rendering using recursive subdivision

//-----------------------------------------------------------------------
// The Anti-Grain Geometry Project
// A high quality rendering engine for C++
// http://antigrain.com
// 
// Anti-Grain Geometry has dual licensing model. The Modified BSD 
// License was first added in version v2.4 just for convenience.
// It is a simple, permissive non-copyleft free software license, 
// compatible with the GNU GPL. It's well proven and recognizable.
// See http://www.fsf.org/licensing/licenses/index_html#ModifiedBSD
// for details.
// 
// Note that the Modified BSD license DOES NOT restrict your rights 
// if you choose the Anti-Grain Geometry Public License.
// 
// Anti-Grain Geometry Public License
// ====================================================
// 
// Anti-Grain Geometry - Version 2.4 
// Copyright (C) 2002-2005 Maxim Shemanarev (McSeem) 
// 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
// 
// 
// 
// Modified BSD License
// ====================================================
// Anti-Grain Geometry - Version 2.4 
// Copyright (C) 2002-2005 Maxim Shemanarev (McSeem) 
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   1. Redistributions of source code must retain the above copyright 
//      notice, this list of conditions and the following disclaimer. 
// 
//   2. Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in 
//      the documentation and/or other materials provided with the 
//      distribution. 
// 
//   3. The name of the author may not be used to endorse or promote 
//      products derived from this software without specific prior 
//      written permission. 
// 
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR 
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
//
//-----------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//-----------------------------------------------------------------------

double calc_sq_distance(double x1, double y1, double x2, double y2);

void recursive_bezier(double x1, double y1,
	double x2, double y2,
	double x3, double y3,
	double x4, double y4,
	unsigned level,
	double m_angle_tolerance,
	double m_cusp_limit,
	double m_distance_tolerance_square,
	void(*add_point)(void*, float, float),
	void* obj);

void curve4_div(double x1, double y1,
	double x2, double y2,
	double x3, double y3,
	double x4, double y4,
	double m_approximation_scale,
	double m_angle_tolerance,
	double m_cusp_limit,
	void(*add_point)(void*, float, float),
	void* obj);

#endif
