#ifndef VASER_POLYLINE_H
#define VASER_POLYLINE_H

#include "vertex_array_holder.h"
#include "point.h"
#include "circular_array.h"

namespace VASEr
{
	namespace VASErin
	{	//VASEr internal namespace

	/*visual testes:
	 * A. points (geometry test)
	 *  1. arbitrary polyline of only 2 point
	 *  2. polylines of 3 points, making arbitrary included angle
	 *  3. arbitrary polyline of 4 or more points
	 * B. colors
	 *  1. different colors on each point
	 * C. weight
	 *  1. varying weight
	 * D. other drawing options
	 *  1. feathering
	 *  2. different joint types
	 *  3. different cap types
	 * E. memory test
	 *  1. drawing a polyline of 1000 points
	 */

	 /*known visual bugs: ( ",," simply means "go wild" as it is too hard to describe)
	  * 1.  [solved]when 2 segments are exactly at 90 degrees, the succeeding line segment is reflexed.
	  * 1.1 [solved]when 2 segments are exactly at 180 degrees,,
	  * 2.  [solved]when polyline is dragged, caps seem to have pseudo-podia.
	  * 3.  [solved]when 2 segments are exactly horizontal/ vertical, both segments are reflexed.
	  * 3.1 [solved]when a segment is exactly horizontal/ vertical, the cap disappears
	  * 4.  [solved]when 2 segments make < 5 degrees,,
	  * 4.1 [solved]when 2 segments make exactly 0 degree,,
	  * 5.  when a segment is shorter than its own width,,
	  */

	  /* const double vaser_actual_PPI = 96.0;
		  const double vaser_standard_PPI = 111.94; //the PPI I used for calibration
	   */

	   //critical weight to do approximation rather than real joint processing
		#define cri_segment_approx 1.6f

		//efficiency: can cache one set of w,t,R values
		// i.e. when a polyline is of uniform thickness, the same w is passed in repeatedly
		void determine_t_r(TFLOAT w, TFLOAT& t, TFLOAT& R);

		float get_PLJ_round_dangle(float t, float r);

		void make_T_R_C(Point& P1, Point& P2, Point* T, Point* R, Point* C,
			TFLOAT w, const polyline_opt& opt,
			TFLOAT* rr, TFLOAT* tt, float* dist,
			bool seg_mode = false);

		void same_side_of_line(Point& V, const Point& ref, const Point& a, const Point& b);

		struct st_polyline
			//the struct to hold info for anchor_late() to perform triangluation
		{
			//for all joints
			Point vP; //vector to intersection point
			Point vR; //fading vector at sharp end
				//all vP,vR are outward

			//for djoint==PLJ_bevel
			Point T; //core thickness of a line
			Point R; //fading edge of a line
			Point bR; //out stepping vector, same direction as cap
			Point T1, R1; //alternate vectors, same direction as T21
				//all T,R,T1,R1 are outward

			//for djoint==PLJ_round
			float t, r;

			//for degeneration case
			bool degenT; //core degenerated
			bool degenR; //fade degenerated
			bool pre_full; //draw the preceding segment in full
			Point PT, PR;
			float pt; //parameter at intersection
			bool R_full_degen;

			char djoint; //determined joint
					// e.g. originally a joint is PLJ_miter. but it is smaller than critical angle, should then set djoint to PLJ_bevel
		};

		struct st_anchor
			//the struct to hold memory for the working of anchor()
		{
			Point P[3]; //point
			Color C[3]; //color
			TFLOAT W[3];//weight

			Point cap_start, cap_end;
			st_polyline SL[3];
			vertex_array_holder vah;
		};

		//(apparent center) center of fan
		//draw the inner arc between angle1 and angle2 with dangle at each step.
		// -the arc has thickness, r is the outer radius and r2 is the inner radius,
		//    with color C and C2 respectively.
		//    in case when inner radius r2=0.0f, it gives a pie.
		// -when ignor_ends=false, the two edges of the arc lie exactly on angle1
		//    and angle2. when ignor_ends=true, the two edges of the arc do not touch
		//    angle1 or angle2.
		// -P is the mathematical center of the arc.
		// -when apparent_P points to a valid Point (apparent_P != 0), r2 is ignored,
		//    apparent_P is then the apparent origin of the pie.
		// -the result is pushed to hold, in form of a triangle strip
		// -an inner arc is an arc which is always shorter than or equal to a half circumference
		void inner_arc(vertex_array_holder& hold, const Point& P,
			const Color& C, const Color& C2,
			float dangle, float angle1, float angle2,
			float r, float r2, bool ignor_ends,
			Point* apparent_P);

		//triangulate an inner arc between vectors A and B,
		//  A and B are position vectors relative to P
		void vectors_to_arc(vertex_array_holder& hold, const Point& P,
			const Color& C, const Color& C2,
			Point A, Point B, float dangle, float r, float r2, bool ignor_ends,
			Point* apparent_P);

#ifdef _DEBUG
		void annotate(const Point& P, Color cc, int I = -1);

		void annotate(const Point& P);

		void draw_vector(const Point& P, const Point& V, const char* name);

		void printpoint(const Point& P, const char* name);
#endif

		/*
				Point plus_minus(const Point& a, const Point& b, bool plus);

				Point plus_minus(const Point& a, bool plus);

				//points:
				//   1------3
				//  /      /
				// 0------2
				// vector 01 parallel to 23
				bool quad_is_reflexed(const Point& P0, const Point& P1, const Point& P2, const Point& P3);

				//push 2 points to form a quad safely(without reflex)
				void push_quad_safe(vertex_array_holder& core,
					const Point& P2, const Color& cc2, bool transparent2,
					const Point& P3, const Color& cc3, bool transparent3);
		*/

		void push_quad_(short line, vertex_array_holder& core,
			const Point& P0, const Point& P1, const Point& P2, const Point& P3,
			const Color& c0, const Color& c1, const Color& c2, const Color& c3);

		void push_quadf_(short line, vertex_array_holder& core,
			const Point& P0, const Point& P1, const Point& P2, const Point& P3,
			const Color& c0, const Color& c1, const Color& c2, const Color& c3,
			bool trans0, bool trans1, bool trans2, bool trans3);

		struct st_knife_cut
		{
			Point T1[4]; //retained polygon, also serves as input triangle
			Color C1[4]; //

			Point T2[4]; //cut away polygon
			Color C2[4]; //

			int T1c, T2c; //count of T1 & T2
				//must be 0,3 or 4
		};

		//see knife_cut_test for more info
		//return number of points cut away
		int triangle_knife_cut(const Point& kn1, const Point& kn2, const Point& kn_out, //knife
			const Color* kC0, const Color* kC1, //color of knife
			st_knife_cut& ST);//will modify for output

		//perform knife cut on all triangles (GL_TRIANGLES) in core
		void vah_knife_cut(vertex_array_holder& core, //serves as both input and output
			const Point& kn1, const Point& kn2, const Point& kn_out);

		//an iterative implementation
		void vah_N_knife_cut(vertex_array_holder& in, vertex_array_holder& out,
			const Point* kn0, const Point* kn1, const Point* kn2,
			const Color* kC0, const Color* kC1,
			int N);

		const float cri_core_adapt = 0.0001f;

		void anchor_late(const Vec2* P, const Color* C, st_polyline* SL,
			vertex_array_holder& tris,
			Point cap1, Point cap2);

		void anchor_cap(const Vec2* P, const Color* C, st_polyline* SL,
			vertex_array_holder& tris,
			Point cap1, Point cap2);

		void segment_late(const Vec2* P, const Color* C, st_polyline* SL,
			vertex_array_holder& tris,
			Point cap1, Point cap2);

		void segment(st_anchor& SA, const polyline_opt* options, bool cap_first, bool cap_last, char last_cap_type = -1);

		int anchor(st_anchor& SA, const polyline_opt* options, bool cap_first, bool cap_last);

		struct polyline_inopt
		{
			bool const_color;
			bool const_weight;
			bool no_cap_first;
			bool no_cap_last;
			bool join_first;
			bool join_last;
			TFLOAT* segment_length; //array of length of each segment
		};

		void poly_point_inter(const Point* P, const Color* C, const TFLOAT* W, const polyline_inopt* inopt,
			Point& p, Color& c, TFLOAT& w,
			int at, TFLOAT t);

		void polyline_approx(
			const Vec2* points,
			const Color* C,
			const TFLOAT* W,
			int length,
			const polyline_opt* opt,
			const polyline_inopt* inopt);

		void polyline_exact(
			const Vec2* P,
			const Color* C,
			const TFLOAT* W,
			int size_of_P,
			const polyline_opt* opt,
			const polyline_inopt* inopt);

		void polyline_range(
			const Vec2* P,
			const Color* C,
			const TFLOAT* W,
			int length,
			const polyline_opt* opt,
			const polyline_inopt* in_options,
			int from, int to,
			bool approx);

		void polyline(
			const Vec2* PP,  //pointer to array of point of a polyline
			const Color* C,  //array of color
			const TFLOAT* W, //array of weight
			int length, //size of the buffer P
			const polyline_opt* options, //options
			const polyline_inopt* in_options);//internal options

	} //sub namespace VASErin

}

#endif
