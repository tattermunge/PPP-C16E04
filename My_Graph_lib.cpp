#include "My_Graph_lib.h"

namespace Graph_lib {
	//-------------------------------------------------------------------
	Box::Box(Point p, int ww, int hh, int rr) :
		w{ ww }, h{ hh }, r{ rr }
	{
		if (h <= 0 || w <= 0) error("Bad rectangle: non-positive side");
		initializer_list<Point> il = {
			//Line Points
			{ p.x + r, p.y },{ p.x + w - r, p.y }, //horisontal line top
		{ p.x + r, p.y + h },{ p.x + w - r, p.y + h }, //horisontal line bottom
		{ p.x, p.y + r },{ p.x, p.y + h - r }, //vertical line left
		{ p.x + w, p.y + r },{ p.x + w, p.y + h - r },//vertical line right
													  //arc Points
		{ p.x + w - r - r, p.y },{ p.x, p.y },
		{ p.x, p.y + h - r - r },{ p.x + w - r - r, p.y + h - r - r },
		{ p.x, p.y }
		};

		add(il);
	}
	//-------------------------------------------------------------------
	Arrow_line::Arrow_line(Point pa, Point pb) :
		p1{ pa }, p2{ pb }, l{ right }
	{
		Shape::add(pa);	Shape::add(pb);
		if (pa.x == pb.x || pa.y == pb.y) calculate_simple(p1, p2, l);
		else {
			set_slope(p1, p2);
			calculate_complex(p1, p2, l);
		}
	}
	//-------------------------------------------------------------------
	Arrow_line::Arrow_line(Point pa, Point pb, Location lc) :
		p1{ pa }, p2{ pb }, l{ lc }
	{
		Shape::add(pa);	Shape::add(pb);
		if (pa.x == pb.x || pa.y == pb.y) calculate_simple(p1, p2, l);
		else {
			set_slope(p1, p2);

			calculate_complex(p1, p2, l);
		}
	}
	/*Arrow_line::Arrow_line(Lines & l)
	{
	for (int i = 1; i<number_of_points(); i += 2)
	if (point(i - 1).x == point(i).x || point(i - 1).y == point(i).y) calculate_simple(pa, pb, lc);
	else {
	set_slope(p1, p2);
	calculate_complex(p1, p2, l);
	}
	}*/
	/*Arrow_line::Arrow_line(Lines & l, Location lc)
	{
	if (point(0).x == point(1).x || point(0).y == point(1).y) calculate_simple(pa, pb);
	else {
	Double_point dpa{ point(0) };
	Double_point dpb{ point(1) };
	a_line = (dpb.y - dpa.y) / (dpb.x - dpa.x);
	calculate_complex(dpa, dpb);
	}
	}*/
	//-------------------------------------------------------------------
	void Triangle_shape::set_slope(Double_point& p1, Double_point& p2)
	{
		a_line = (p2.y - p1.y) / (p2.x - p1.x);
	}
	//-------------------------------------------------------------------
	void Triangle_shape::set_variables(Double_point p)
	{
		b_line = p.y - a_line * p.x;
		a_quad = pow(a_line, 2) + 1;
		b_quad = ((-2) * p.x) + (2 * a_line * (b_line - p.y));
		c_quad = pow(p.x, 2) + pow(b_line - p.y, 2) - pow(r, 2);
		d = pow(b_quad, 2) - 4 * a_quad * c_quad;
	}
	//-------------------------------------------------------------------
	bool Triangle_shape::vertical(Double_point& p1, Double_point& p2) const
	{
		if (p1.x == p2.x) return true;
		return false;
	}
	//-------------------------------------------------------------------
	void Triangle_shape::calculate_simple(Double_point& p1, Double_point& p2, Location l)
	{
		end = (p1.y < p2.y) ? p2 : p1; //righmost/top point
		start = (p1.y < p2.y) ? p1 : p2;//leftmost point
		Arrow ra;
		Arrow la;

		switch (l) {
		case right://top/right arrow	
			if (vertical(p1, p2)) {//add points for vertical arrow
				ra.add({ end.x - r, end.y - r });	ra.add({ end.x + r, end.y - r });
				ra.add({ end.x, end.y });			ra.add({ end.x - r, end.y - r });
			}
			else {//horizontal 
				ra.add({ end.x - r, end.y + r });	ra.add({ end.x - r, end.y - r });
				ra.add({ end.x, end.y });			ra.add({ end.x - r, end.y + r });
			}
			add_arrow(ra);
			break;
		case left:
			if (vertical(p1, p2)) {//vertical right/top and left/bottom
				la.add({ start.x - r, start.y + r });	la.add({ start.x + r, start.y + r });
				la.add({ start.x, start.y });			la.add({ start.x - r, start.y + r });
			}
			else {//horizontal left/bottom
				la.add({ start.x + r, start.y + r });	la.add({ start.x + r, start.y - r });
				la.add({ start.x, start.y });			la.add({ start.x + r, start.y + r });
			}
			add_arrow(la);
			break;
		default:
			if (vertical(p1, p2)) {//add points for vertical right/top and left/bottom arrow
				ra.add({ end.x - r, end.y - r });		ra.add({ end.x + r, end.y - r });
				ra.add({ end.x, end.y });				ra.add({ end.x - r, end.y - r });
				la.add({ start.x - r, start.y + r });	la.add({ start.x + r, start.y + r });
				la.add({ start.x, start.y });			la.add({ start.x - r, start.y + r });
			}
			else {//horizontal right/top and left/bottom
				ra.add({ end.x - r, end.y + r });		ra.add({ end.x - r, end.y - r });
				ra.add({ end.x, end.y });				ra.add({ end.x - r, end.y + r });
				la.add({ start.x + r, start.y + r });	la.add({ start.x + r, start.y - r });
				la.add({ start.x, start.y });			la.add({ start.x + r, start.y + r });
			}
			add_arrow(ra);
			add_arrow(la);
			break;
		}
	}
	//-------------------------------------------------------------------
	double Triangle_shape::solution_positive() {
		double solution = ((-1) * b_quad + sqrt(d)) / (2 * a_quad);
		return solution;
	}
	//-------------------------------------------------------------------
	double Triangle_shape::solution_negative() {
		double solution = ((-1) * b_quad - sqrt(d)) / (2 * a_quad);
		return solution;
	}
	//-------------------------------------------------------------------
	void Triangle_shape::add_right_complex() {
		Arrow ra;
		//solution to equation must be less than right endpoint 
		double x_value = (solution_negative() < end.x) ?
			solution_negative() : solution_positive();
		//calculate correstartonding y-coordinate
		double y_value = a_line * x_value + b_line;
		//calculate perpendicular line funtion 
		a_line = (-1) / a_line;//new slope
		b_line = y_value - a_line * x_value;
		set_variables({ x_value, y_value });
		//adds solution one for drawing  
		x_value = solution_negative();
		y_value = a_line * x_value + b_line;
		ra.add(end);
		ra.add({ x_value , y_value });
		//adds solution two for drawing  
		x_value = solution_positive();
		y_value = a_line * x_value + b_line;
		ra.add({ x_value, y_value });
		ra.add(end);
		add_arrow(ra);
	}
	//-------------------------------------------------------------------
	void Triangle_shape::add_left_complex() {
		Arrow la;
		//solution to equation must be greater than left endpoint
		double x_value = (solution_negative() > start.x) ?
			solution_negative() : solution_positive();
		double y_value = a_line * x_value + b_line;
		//calculate perpendicular line funtion 
		a_line = (-1) / a_line;//new slope
		b_line = y_value - a_line * x_value;
		set_variables({ x_value, y_value });
		//adds solution one for drawing  
		x_value = solution_negative();
		y_value = a_line * x_value + b_line;
		la.add(start);
		la.add({ x_value, y_value });
		//adds solution two for drawing  
		x_value = solution_positive();
		y_value = a_line * x_value + b_line;
		la.add({ x_value, y_value });
		la.add(start);

		add_arrow(la);
	}
	//-------------------------------------------------------------------	
	void Triangle_shape::calculate_complex(Double_point& p1, Double_point& p2, Location lc)
	{
		end = (p1.x < p2.x) ? p2 : p1; //righmost point
		start = (p1.x < p2.x) ? p1 : p2;//leftmost point
		switch (lc) {
		case left://left/bottom arrow
			set_variables(start);
			add_left_complex();
			break;
		case right://top/right arrow
			set_variables(end);
			add_right_complex();
			break;
		default://arrow on both ends
			set_variables(start);
			add_left_complex();
			set_slope(p1, p2);
			set_variables(end);
			add_right_complex();
			break;
		}
	}	
	//-------------------------------------------------------------------
	void Box::add(initializer_list<Point>& lst)
	{
		for (Point p : lst) Shape::add(p);
	}
	//-------------------------------------------------------------------
	void Box::draw_lines() const
	{

		if (color().visibility()) {
			for (int i = 1; i < 8; i += 2)
				fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);

			fl_arc(point(8).x, point(8).y, r + r, r + r, 0, 90);
			fl_arc(point(9).x, point(9).y, r + r, r + r, 90, 180);
			fl_arc(point(10).x, point(10).y, r + r, r + r, 180, 270);
			fl_arc(point(11).x, point(11).y, r + r, r + r, 270, 360);
		}

		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());

			fl_rectf(point(12).x + r, point(12).y, w - r - r, h);
			fl_rectf(point(12).x, point(12).y + r, w, h - r - r);

			fl_pie(point(8).x, point(8).y, r + r - 1, r + r - 1, 0, 90);
			fl_pie(point(9).x, point(9).y, r + r - 1, r + r - 1, 90, 180);
			fl_pie(point(10).x, point(10).y, r + r - 1, r + r - 1, 180, 270);
			fl_pie(point(11).x, point(11).y, r + r - 1, r + r - 1, 270, 360);

			fl_color(color().as_int());	// reset color
		}
	}
	//-------------------------------------------------------------------
	void Arrow_line::draw_lines() const
	{
		if (color().visibility()) {
			for (int i = 1; i<number_of_points(); i += 2)
				fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);

			for (int n = 0; n < number_of_arrows(); ++n)
				for (int i = 1; i < 4; ++i) fl_line(
					nearbyint(arrow(n).double_point(i - 1).x), nearbyint(arrow(n).double_point(i - 1).y),
					nearbyint(arrow(n).double_point(i).x), nearbyint(arrow(n).double_point(i).y)
				);
		}
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for (int n = 0; n < number_of_arrows(); ++n)
				for (int i = 0; i < 4; ++i) fl_vertex(
					nearbyint(arrow(n).double_point(i).x), nearbyint(arrow(n).double_point(i).y)
				);
			fl_end_complex_polygon();
			fl_color(color().as_int());	// reset color
		}
	}
	//-------------------------------------------------------------------
	void Arc::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, ds, de);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, r + r, r + r, ds, de);
		}
	}
	//-------------------------------------------------------------------
	Equitri::Equitri(Point p, int l):
		loc{p}, sl{l}
	{
		add({ loc.x + roundint(sl / 2.0), loc.y });
		add({ loc.x + sl, loc.y + roundint(sqrt(3) / 2.0 * sl) });
		add({ loc.x, loc.y + roundint(sqrt(3) / 2.0 * sl) });
	}
	//-------------------------------------------------------------------
	void Equitri::set_equitri(Point p, int l)
	{
		set_point(0, { p.x + roundint(l / 2.0), p.y });
		set_point(1, { p.x + l, p.y + roundint(sqrt(3) / 2.0 * l) });
		set_point(2, { p.x, p.y + roundint(sqrt(3) / 2.0 * l) });
	}
	//-------------------------------------------------------------------
	void Equitri::set_loc(Point p)
	{
		set_point(0, { p.x + roundint(sl / 2.0), p.y });
		set_point(1, { p.x + sl, p.y + roundint(sqrt(3) / 2.0 * sl) });
		set_point(2, { p.x, p.y + roundint(sqrt(3) / 2.0 * sl) });
	}
	//-------------------------------------------------------------------
	void Equitri::set_sl(int l)
	{
		set_point(0, { loc.x + roundint(l / 2.0), loc.y });
		set_point(1, { loc.x + l, loc.y + roundint(sqrt(3) / 2.0 * l) });
		set_point(2, { loc.x, loc.y + roundint(sqrt(3) / 2.0 * l) });
	}
	//-------------------------------------------------------------------
	Hexagon::Hexagon(Point p, int l):
		loc{ p }, sl{ l }
	{
		add(Point{ loc.x + roundint(cos(deg30) * sl), loc.y });
		add(Point{ loc.x + roundint(2 * cos(deg30) * sl), loc.y + roundint(sl / 2.0) });
		add(Point{ loc.x + roundint(2 * cos(deg30) * sl), loc.y + sl + roundint(sl / 2.0) });
		add(Point{ loc.x + roundint(cos(deg30) * sl), loc.y + 2 * sl });
		add(Point{ loc.x, loc.y + sl + roundint(sl / 2.0) });
		add(Point{ loc.x, loc.y + roundint(sl / 2.0) });
	}
	//-------------------------------------------------------------------
	void Hexagon::set_hexagon(Point p, int l)
	{
		set_point(0, { p.x + roundint(cos(deg30) * l), p.y });
		set_point(1, { p.x + roundint(2 * cos(deg30) * l), p.y + roundint(l / 2.0) });
		set_point(2, { p.x + roundint(2 * cos(deg30) * l), p.y + l + roundint(l / 2.0) });
		set_point(3, { p.x + roundint(cos(deg30) * l), p.y + 2 * l });
		set_point(4, { p.x, p.y + l + roundint(l / 2.0) });
		set_point(5, { p.x, p.y + roundint(l / 2.0) });
	}
	//-------------------------------------------------------------------
	void Hexagon::set_loc(Point p)
	{
		set_point(0, { p.x + roundint(cos(deg30) * sl), p.y });
		set_point(1, { p.x + roundint(2 * cos(deg30) * sl), p.y + roundint(sl / 2.0) });
		set_point(2, { p.x + roundint(2 * cos(deg30) * sl), p.y + sl + roundint(sl / 2.0) });
		set_point(3, { p.x + roundint(cos(deg30) * sl), p.y + 2 * sl });
		set_point(4, { p.x, p.y + sl + roundint(sl / 2.0) });
		set_point(5, { p.x, p.y + roundint(sl / 2.0) });
	}
	//-------------------------------------------------------------------
	void Hexagon::set_sl(int l)
	{
		set_point(0, { loc.x + roundint(cos(deg30) * l), loc.y });
		set_point(1, { loc.x + roundint(2 * cos(deg30) * l), loc.y + roundint(l / 2.0) });
		set_point(2, { loc.x + roundint(2 * cos(deg30) * l), loc.y + l + roundint(l / 2.0) });
		set_point(3, { loc.x + roundint(cos(deg30) * l), loc.y + 2 * l });
		set_point(4, { loc.x, loc.y + l + roundint(l / 2.0) });
		set_point(5, { loc.x, loc.y + roundint(l / 2.0) });
	}
}