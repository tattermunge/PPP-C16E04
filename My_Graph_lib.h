#ifndef My_Graph_lib_GUARD

#include "Simple_window.h"
#include<cmath>
#define PI 3.14159265

namespace Graph_lib {
#undef major
#undef minor

	//-------------------------------------------------------------------
	struct Double_point {
		double x, y;
		Double_point(double xx, double yy) : x(xx), y(yy) { }
		Double_point(Point p) : x{ double(p.x) }, y{ double(p.y) } { }
		Double_point() :x(0), y(0) { }

		Double_point& operator+=(Double_point d) { x += d.x; y += d.y; return *this; }
	};

	inline bool operator==(Double_point a, Double_point b) { return a.x == b.x && a.y == b.y; }
	inline bool operator!=(Double_point a, Double_point b) { return !(a == b); }
	//-------------------------------------------------------------------
	struct Arrow {
		int number_of_double_points() const { return double_points.size(); }
		Double_point double_point(int i) const { return double_points[i]; }
		int width() const { return w; }
		int length() const { return l; }
		void add(Double_point dp) {
			if (double_points.size() == 4) error("only 4 points in double_points");
			double_points.push_back(dp);
		}
	private:
		vector<Double_point> double_points;
		int w;//arrow width
		int l;//arrow length
	};
	//-------------------------------------------------------------------
	struct Triangle_shape : Shape {
		enum Location { left = 'l', right = 'r', both = 'b' };
	protected:
		void add_arrow(Arrow ah) { if (ah.number_of_double_points() != 4) error("not enough points in arrow"); arrows.push_back(ah); }
		void set_slope(Double_point& pa, Double_point& pb);
		void set_variables(Double_point p); //set quadratic equation variables
		bool vertical(Double_point& pa, Double_point& Pb) const; //vertical or horizontal
		void calculate_simple(Double_point& pa, Double_point& Pb, Location l); //set points for stright lines
		void add_left_complex(); //calculates and adds arrow points for "left" arrow to list
		void add_right_complex();//calculates and adds arrow point for "right" arrow to list
		double solution_positive();//solution one for quadratic equation
		double solution_negative();//solution two for quadratic equation
		void calculate_complex(Double_point& pa, Double_point& Pb, Location l);//calculate arrow points for non-straight lines
		Arrow arrow(int i) const { return arrows[i]; }
		int number_of_arrows() const { return int(arrows.size()); }
	private:
		vector<Arrow> arrows; //store calcuated points
		Double_point start; //arrow top/right point
		Double_point end;//arrow "bottom/left" point
		int r = 10;//arrow length
		double a_line;//slope(hældningskoefficient)
		double b_line;//crossing point for y-axis
		double a_quad;//a-koefficient andengradsligning
		double b_quad;//b-koefficient andengradsligning
		double c_quad;//c-koefficient andengradsligning
		double d; //diskriminant
	};
	//-------------------------------------------------------------------
	struct Arrow_line : Triangle_shape {
		/*Arrow_line(Line& ln);
		Arrow_line(Line& ln, Location lc);*/
		Arrow_line(Point pa, Point pb);
		Arrow_line(Point pa, Point pb, Location lc);
		void draw_lines() const;
	private:
		Double_point p1, p2;
		Location l;
	};
	//-------------------------------------------------------------------
	struct Box : Shape {
		Box(Point p, int ww, int hh, int rr);
		void add(initializer_list<Point>& lst);
		void draw_lines() const;

		int height() const { return h; }
		int width() const { return w; }
		int radius() const { return r; }
	private:
		int w;
		int h;
		int r;

	};
	//-------------------------------------------------------------------
	struct Arc : Shape {
		Arc(Point p, int rr, int d1, int d2)	// center, radius and degrees
			:r{ rr }, ds{ d1 }, de{ d2 } {
			add(Point{ p.x - r, p.y - r });
		}

		void draw_lines() const;
		Point center() const { return { point(0).x + r, point(0).y + r }; }
		void set_radius(int rr) { r = rr; }
		int radius() const { return r; }
	private:
		int r;
		int ds;
		int de;
	};
	//-------------------------------------------------------------------
	struct Equitri : Closed_polyline {
		Equitri(Point p, int l);
		void set_equitri(Point p, int l);
		void set_loc(Point p);
		void set_sl(int sl);
		Point get_loc() const { return loc; }
		int get_sl() const { return sl; }
		int roundint(double d) { return static_cast<int>(nearbyint(d)); }
	private:
		Point loc;
		int sl;
	};
	//-------------------------------------------------------------------
	struct Hexagon : Closed_polyline {
		Hexagon(Point p, int sl);
		void set_hexagon(Point p, int l);
		void set_loc(Point p);
		void set_sl(int sl);
		Point get_loc() const { return loc; }
		int get_sl() const { return sl; }
		int roundint(double d) { return static_cast<int>(nearbyint(d)); }
	private:
		Point loc;
		int sl;
		double deg30 = PI * 30 / 180;
	};
}
#endif
