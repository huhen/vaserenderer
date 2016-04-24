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
			std::vector<double> W;
			std::vector<double> L; //length along polyline
			int N;
			double path_length; //total segment length

			polyline_buffer();

			void point(double x, double y);
			void point(Vec2 V);
			static void point_cb(void* obj, double x, double y);
			void vertex(Vec2 V, Color cc);
			void vertex(Vec2 V, Color cc, double ww);
			void set_color(Color cc);
			void set_weight(double ww);
			void gradient(const gradient* grad);
			void draw(const polyline_opt* options);
		private:
			bool addvertex(const Vec2& V, const Color* cc = 0, double ww = 0.0);
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
