#ifndef VASER_POINT_H
#define VASER_POINT_H

#include "vaser.h"

namespace VASEr
{
	class Point : public Vec2
	{
	public:
		Point();
		Point(const Vec2& P);
		Point(const Point& P);
		Point(double X, double Y);

		void clear();
		void set(double X, double Y);

		Vec2 vec() const;

		//attributes
		double length() const;
		double slope() const;
		static double signed_area(const Point& P1, const Point& P2, const Point& P3);

		//vector operators	
		Point operator+(const Point &b) const;
		Point operator-() const;
		Point operator-(const Point &b) const;
		Point operator*(double k) const;

		Point& operator=(const Point& b);
		Point& operator+=(const Point& b);
		Point& operator-=(const Point& b);
		Point& operator*=(const double k);
		Point& operator/=(const double k);

		static void dot(const Point& a, const Point& b, Point& o); //dot product: o = a dot b
		Point dot_prod(const Point& b) const; //return dot product

		//self operations
		void opposite();
		void opposite_of(const Point& a);
		double normalize();
		void perpen(); //perpendicular: anti-clockwise 90 degrees
		void follow_signs(const Point& a);

		//todo:follow_magnitude and follow_direction
		//void follow_magnitude(const Point& a);
		//void follow_direction(const Point& a);

		//judgements
		static bool negligible(double M);
		bool negligible() const;
		bool non_negligible() const;
		bool is_zero() const;
		bool non_zero() const;
		static bool intersecting(const Point& A, const Point& B,
			const Point& C, const Point& D); //return true if AB intersects CD

		//operations require 2 input points
		static double distance_squared(const Point& A, const Point& B);
		static inline double distance(const Point& A, const Point& B);
		static Point midpoint(const Point& A, const Point& B);
		static bool opposite_quadrant(const Point& P1, const Point& P2);

		//operations of 3 points
		static inline bool anchor_outward_D(Point& V, const Point& b, const Point& c);
		static bool anchor_outward(Point& V, const Point& b, const Point& c, bool reverse = false); //put the correct outward vector at V, with V placed on b, comparing distances from c
		static void anchor_inward(Point& V, const Point& b, const Point& c);

		//operations of 4 points
		static char intersect(const Point& P1, const Point& P2,  //line 1
			const Point& P3, const Point& P4, //line 2
			Point& Pout,			  //the output point
			double* ua_out = 0, double* ub_out = 0); //Determine the intersection point of two line segments

	}; //end of class Point

	/* after all,
	 * sizeof(Vec2)=16  sizeof(Point)=16
	 * Point is not heavier, just more powerful :)
	*/
}

#endif
