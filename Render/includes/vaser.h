#ifndef VASER_H
#define VASER_H
/* Vase Renderer first draft, version 0.3 */

/* Basic usage
* You should provide these structs before any vase_renderer include, using
struct Vec2 { double x,y;};
struct Color { float r,g,b,a;};
* or
typedef your_vec2 Vec2;
typedef your_color Color;
*/

#ifdef _DEBUG
#define VASER_DEBUG printf
#else
#define VASER_DEBUG ;//
#endif

namespace VASEr
{
#define TFLOAT float
	struct Vec2 { TFLOAT x, y; };
	struct Color { float r, g, b, a; };

	namespace VASErin
	{
		extern const TFLOAT vaser_min_alw; //smallest value not regarded as zero
		extern const Color default_color;
		extern const TFLOAT default_weight;
	}

#define vaser_pi 3.141592653589793f

	struct gradient_stop
	{
		TFLOAT t; //position
		char type; //GS_xx
		union
		{
			Color color;
			TFLOAT weight;
		};
	};

	const char GS_none = 0;
	const char GS_rgba = 1;
	const char GS_rgb = 2; //rgb only
	const char GS_alpha = 3;
	const char GS_weight = 4;

	struct gradient
	{
		gradient_stop* stops; //array must be sorted in ascending order of t
		int length; //number of stops
		char unit; //use_GD_XX
	};

	const char GD_ratio = 0; //default
	const char GD_length = 1;

	struct Image
	{
		unsigned char* buf; //must **free** buffer manually
		short width;
		short height;
	};

	struct tessellator_opt
	{
		//set the whole structure to 0 will give default options
		bool triangulation;
		char parts; //use TS_xx
		bool tessellate_only;
		void* holder; //used as (VASErin::vertex_array_holder*) if tessellate_only is true
	};

	//for tessellator_opt.parts
	const char TS_core_fade = 0; //default
	const char TS_core = 1;
	const char TS_outer_fade = 2;
	const char TS_inner_fade = 3;

	struct polyline_opt
	{
		//set the whole structure to 0 will give default options
		const tessellator_opt* tess;
		char joint; //use PLJ_xx
		char cap;   //use PLC_xx
		bool feather;
		TFLOAT feathering;
		bool no_feather_at_cap;
		bool no_feather_at_core;
	};

	//for polyline_opt.joint
	const char PLJ_miter = 0; //default
	const char PLJ_bevel = 1;
	const char PLJ_round = 2;

	//for polyline_opt.cap
	const char PLC_butt = 0; //default
	const char PLC_round = 1;
	const char PLC_square = 2;
	const char PLC_rect = 3;
	const char PLC_both = 0; //default
	const char PLC_first = 10;
	const char PLC_last = 20;
	const char PLC_none = 30;

	void polyline(const Vec2*, const Color*, const TFLOAT*, int length, const polyline_opt*);
	void polyline(const Vec2*, Color, TFLOAT W, int length, const polyline_opt*); //constant color and weight
	void polyline(const Vec2*, const Color*, TFLOAT W, int length, const polyline_opt*); //constant weight
	void polyline(const Vec2*, Color, const TFLOAT* W, int length, const polyline_opt*); //constant color
	void segment(Vec2, Vec2, Color, Color, TFLOAT W1, TFLOAT W2, const polyline_opt*);
	void segment(Vec2, Vec2, Color, TFLOAT W, const polyline_opt*); //constant color and weight
	void segment(Vec2, Vec2, Color, Color, TFLOAT W, const polyline_opt*); //constant weight
	void segment(Vec2, Vec2, Color, TFLOAT W1, TFLOAT W2, const polyline_opt*); //const color

	struct polybezier_opt
	{
		//set the whole structure to 0 will give default options
		const polyline_opt* poly;
	};

	void polybezier(const Vec2* P, const gradient* grad, int length, const polybezier_opt* options);
	void polybezier(const Vec2* P, Color cc, double ww, int length, const polybezier_opt* options);

} //namespace VASEr

#endif
