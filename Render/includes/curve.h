#ifndef VASER_CURVE_H
#define VASER_CURVE_H

#include <vector>
#include "vaser.h"

namespace VASEr
{
	namespace VASErin
	{	//VASEr internal namespace

		class polyline_buffer
		{
		public:
			std::vector<Vec2>   P;
			std::vector<Color>  C;
			std::vector<TFLOAT> W;
			std::vector<TFLOAT> L; //length along polyline
			int N;
			TFLOAT path_length; //total segment length

			polyline_buffer();

			void point(TFLOAT x, TFLOAT y);
			void point(Vec2 V);
			static void point_cb(void* obj, TFLOAT x, TFLOAT y);
			void vertex(Vec2 V, Color cc);
			void vertex(Vec2 V, Color cc, TFLOAT ww);
			void set_color(Color cc);
			void set_weight(TFLOAT ww);
			void gradient(const gradient* grad);
			void draw(const polyline_opt* options);
		private:
			bool addvertex(const Vec2& V, const Color* cc = 0, TFLOAT ww = 0.0f);
		};

		struct polybezier_inopt
		{
			bool evaluate_only;
			polyline_buffer* target;
		};

		void polybezier(const Vec2* P, const gradient* grad, int length, const polybezier_opt* options, const polybezier_inopt* in_options);

	} //sub namespace VASErin

}

#endif
