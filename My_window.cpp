#include "My_window.h"
namespace Graph_lib {

	My_window::My_window(Point xy, int w, int h, const string& title) :
		Window(xy, w, h, title),
		next_button(Point(x_max() - 70, 0), 70, 20, "Next", cb_next),
		quit_button(Point(x_max() - 70, 20), 70, 20, "Quit", cb_quit),
		button_pushed{ false }
	{
		attach(next_button);
		attach(quit_button);
	}
	//-------------------------------------------------------------------
	void My_window::wait_for_button()
	{
		while (!button_pushed) Fl::wait();
		hide();
	}
	//-------------------------------------------------------------------
	Checkerboard::Checkerboard(Point xy, int w, int h, const string& title) :
		My_window{ xy,w,h,title }, top_left{ xy.x + (w / 2) - 100,xy.y + (h / 2) - 100 },
		row1{ Point{xy.x + (w / 2) - 100,xy.y + (h / 2) - 100},50,50,Menu::horizontal,"r1" },
		row2{ Point{xy.x + (w / 2) - 100,xy.y + (h / 2) - 50},50,50,Menu::horizontal,"r2" },
		row3{ Point{xy.x + (w / 2) - 100,xy.y + (h / 2)},50,50,Menu::horizontal,"r3" },
		row4{ Point{xy.x + (w / 2) - 100,xy.y + (h / 2) + 50},50,50,Menu::horizontal,"r4" }

	{
		create_rects();
		row1.attach(new Button{ Point{ 0,0 }, 0, 0, "1-1", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b01(); } });
		row1.attach(new Button{ Point{ 0,0 }, 0, 0, "1-2", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b02(); } });
		row1.attach(new Button{ Point{ 0,0 }, 0, 0, "1-3", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b03(); } });
		row1.attach(new Button{ Point{ 0,0 }, 0, 0, "1-4", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b04(); } });

		row2.attach(new Button{ Point{ 0,0 }, 0, 0, "2-1", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b05(); } });
		row2.attach(new Button{ Point{ 0,0 }, 0, 0, "2-2", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b06(); } });
		row2.attach(new Button{ Point{ 0,0 }, 0, 0, "2-3", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b07(); } });
		row2.attach(new Button{ Point{ 0,0 }, 0, 0, "2-4", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b08(); } });

		row3.attach(new Button{ Point{ 0,0 }, 0, 0, "3-1", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b09(); } });
		row3.attach(new Button{ Point{ 0,0 }, 0, 0, "3-2", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b10(); } });
		row3.attach(new Button{ Point{ 0,0 }, 0, 0, "3-3", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b11(); } });
		row3.attach(new Button{ Point{ 0,0 }, 0, 0, "3-4", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b12(); } });

		row4.attach(new Button{ Point{ 0,0 }, 0, 0, "4-1", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b13(); } });
		row4.attach(new Button{ Point{ 0,0 }, 0, 0, "4-2", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b14(); } });
		row4.attach(new Button{ Point{ 0,0 }, 0, 0, "4-3", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b15(); } });
		row4.attach(new Button{ Point{ 0,0 }, 0, 0, "4-4", [](Address, Address pw) { reference_to<Checkerboard>(pw).change_b16(); } });

		attach(row1);
		attach(row2);
		attach(row3);
		attach(row4);
		attach_rects();
	}
	//-------------------------------------------------------------------
	void Checkerboard::create_rects()
	{
		for (int h = 0; h < 4; ++h)
			for (int w = 0; w < 4; ++w) {
				rects.push_back(new Rectangle{ Point{top_left.x + (w * 50),top_left.y + (h * 50)},50,50 });
				rects[rects.size() - 1].set_fill_color(Color{ h * 16 + w + 1 });
			}
	}
	//-------------------------------------------------------------------
	void Checkerboard::attach_rects()
	{
		for (int i = 0; i < rects.size(); ++i) attach(rects[i]);
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b01()
	{
		rects[0].set_fill_color(Color{ rects[0].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b02()
	{
		rects[1].set_fill_color(Color{ rects[1].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b03()
	{
		rects[2].set_fill_color(Color{ rects[2].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b04()
	{
		rects[3].set_fill_color(Color{ rects[3].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b05()
	{
		rects[4].set_fill_color(Color{ rects[4].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b06()
	{
		rects[5].set_fill_color(Color{ rects[5].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b07()
	{
		rects[6].set_fill_color(Color{ rects[6].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b08()
	{
		rects[7].set_fill_color(Color{ rects[7].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b09()
	{
		rects[8].set_fill_color(Color{ rects[8].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b10()
	{
		rects[9].set_fill_color(Color{ rects[9].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b11()
	{
		rects[10].set_fill_color(Color{ rects[10].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b12()
	{
		rects[11].set_fill_color(Color{ rects[11].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b13()
	{
		rects[12].set_fill_color(Color{ rects[12].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b14()
	{
		rects[13].set_fill_color(Color{ rects[13].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b15()
	{
		rects[14].set_fill_color(Color{ rects[14].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	void Checkerboard::change_b16()
	{
		rects[15].set_fill_color(Color{ rects[15].fill_color().as_int() + 1 });
		redraw();
	}
	//-------------------------------------------------------------------
	Img_window::Img_window(Point xy, int w, int h, const string & title) :
		My_window{ xy,w,h,title }, top_left{ xy }, img_calvin{ Point{200,200},"C:/Users/Simon/source/repos/lib_files/calvin_img.jpg" },
		move_button{ Point{200,200},100, 112,"",cb_move }, move_point{ Point(x_max() - 70, 40), 70, 20,"current(x,y):" },
		test_button{ Point{x_max() - 70, 60},70, 20,"test",cb_move }

	{
		attach(test_button);
		attach(move_button);
		attach(img_calvin);
		attach(move_point);
	}
	//-------------------------------------------------------------------
	int Img_window::legal_xmove()
	{
		int x_value = 0;
		do x_value = randint(-(Window::x_max() + top_left.x), Window::x_max() + top_left.x - 100);
		while (0 + top_left.x > x_value + move_button.loc.x || x_value + move_button.loc.x > Window::x_max() + top_left.x - 100);

		return x_value;
	}
	//-------------------------------------------------------------------
	int Img_window::legal_ymove()
	{
		int y_value = 0;
		do y_value = randint(-(Window::y_max() + top_left.y), Window::y_max() + top_left.y - 112);
		while (0 + top_left.y > y_value + move_button.loc.y || y_value + move_button.loc.y > Window::y_max() + top_left.y - 112);

		return y_value;
	}
	//-------------------------------------------------------------------
	void Img_window::move_image()
	{
		int x_value = legal_xmove();
		int y_value = legal_ymove();
		move_button.move(x_value, y_value);
		img_calvin.move(x_value, y_value);
		ostringstream ss;
		ss << '(' << move_button.loc.x << ',' << move_button.loc.y << ')';
		move_point.put(ss.str());


		redraw();
	}
	//-------------------------------------------------------------------
	Item_window::Item_window(Point xy, int w, int h, const string& title) :
		Window{ xy, w, h, title }, 
		pos_button{ Point{0, 0}, 20, 20, "+", 
			[](Address, Address pw) { reference_to<Item_window>(pw).do_nothing(); } },
		cl_button{ Point{ x_max() - 70, 40 }, 70, 20, "Create circle",
			[](Address, Address pw) {reference_to<Item_window>(pw).set_clb(); } },
		rt_button{ Point{ x_max() - 70, 80 }, 70, 20, "Create rectangle",
			[](Address, Address pw) {reference_to<Item_window>(pw).set_rtb(); } },
		et_button{ Point{ x_max() - 70, 120 }, 70, 20, "Create equilateral triangle",
			[](Address, Address pw) {reference_to<Item_window>(pw).set_etb(); } },
		hex_button{ Point{ x_max() - 70, 160 }, 70, 20, "Create hexagon",
			[](Address, Address pw) {reference_to<Item_window>(pw).set_hexb(); } },
		cl_inbox{ Point{x_max() - 70, 60}, 70, 20,"(x,y)r" },
		rt_inbox{ Point{x_max() - 70, 100}, 70, 20,"(x,y)w,h" },
		et_inbox{ Point{x_max() - 70, 140}, 70, 20,"(x,y)l" },
		hex_inbox{ Point{x_max() - 70, 180}, 70, 20,"(x,y)l" },
		message_box{ Point{ x_max() - 350, 70 }, 100, 40, "" },
		cl_r{ 0 }, rt_w{ 0 }, rt_h{ 0 }, et_l{ 0 }, hex_l{ 0 }
	{
		attach(pos_button);
		pos_button.hide();
		attach(cl_button);
		attach(rt_button);
		attach(et_button);
		attach(hex_button);
		attach(cl_inbox);
		attach(rt_inbox);
		attach(et_inbox);
		attach(hex_inbox);
	}
	//-------------------------------------------------------------------
	void Item_window::add_circle()
	{
		Circle *new_cl = new Circle{ cl_p, cl_r };
		pos_button.hide();
		attach(*new_cl);
		redraw();
	}
	//-------------------------------------------------------------------
	void Item_window::add_rectangle()
	{
		Rectangle *new_rt = new Rectangle{ rt_p, rt_w, rt_h };
		pos_button.hide();
		attach(*new_rt);
		redraw();
	}
	//-------------------------------------------------------------------
	void Item_window::add_equitri()
	{
		Equitri *new_et = new Equitri{ et_p, et_l };
		pos_button.hide();
		attach(*new_et);
		redraw();
	}
	//-------------------------------------------------------------------
	void Item_window::add_hexagon()
	{
		Hexagon *new_hex = new Hexagon{ hex_p, hex_l };
		pos_button.hide();
		attach(*new_hex);
		redraw();
	}
	//-------------------------------------------------------------------
	void Item_window::cb_cl(Address, Address pw)
	{
		reference_to<Item_window>(pw).add_circle();
	}
	//-------------------------------------------------------------------
	void Item_window::cb_rt(Address, Address pw)
	{
		reference_to<Item_window>(pw).add_rectangle();
	}
	//-------------------------------------------------------------------
	void Item_window::cb_et(Address, Address pw)
	{
		reference_to<Item_window>(pw).add_equitri();
	}
	//-------------------------------------------------------------------
	void Item_window::cb_hex(Address, Address pw)
	{
		reference_to<Item_window>(pw).add_hexagon();
	}
	//-------------------------------------------------------------------
	void Item_window::set_clb()
	{
		istringstream is{ cl_inbox.get_string() };
		ostringstream os;

		int x = get_xval(is);
		int y = get_yval(is);
		int r = get_len(is);
		if (x == -7 || y == -7 || r == -7) {
			os << "Illegal values, try again.";
			message_box.put(os.str());
			redraw();
			return;
		}
		os << "Point: (" << x << ", " << y << ")\n" << "radius: " << r;
		message_box.put(os.str());
		
		pos_button.loc.x = x;
		pos_button.loc.y = y;
		/*pos_button.do_it = cb_cl;*/
		cl_p = { x, y };
		cl_r = r;
		
		pos_button.show();
		redraw();
	}
	//-------------------------------------------------------------------
	void Item_window::set_rtb()
	{
		istringstream is{ rt_inbox.get_string() };
		ostringstream os;

		int x = get_xval(is);
		int y = get_yval(is);
		int w = get_len(is);
		int h = get_hei(is);
		if (x == -7 || y == -7 || w == -7 || h == -7) {
			os << "Illegal values, try again.";
			message_box.put(os.str());
			redraw();
			return;
		}
		os << "Point: (" << x << ", " << y << ")\n" << "width: " << w << "height: " << h;
		message_box.put(os.str());

		pos_button.loc.x = x;
		pos_button.loc.y = y;
		pos_button.do_it = cb_rt;
		rt_p = { x, y };
		rt_w = w;
		rt_h = h;

		pos_button.show();
		redraw();
	}
	//-------------------------------------------------------------------
	void Item_window::set_etb()
	{
		istringstream is{ et_inbox.get_string() };
		ostringstream os;

		int x = get_xval(is);
		int y = get_yval(is);
		int l = get_len(is);
		if (x == -7 || y == -7 || l == -7) {
			os << "Illegal values, try again.";
			message_box.put(os.str());
			redraw();
			return;
		}
		os << "Point: (" << x << ", " << y << ")\n" <<  "Length: " << l;
		message_box.put(os.str());

		pos_button.loc.x = x;
		pos_button.loc.y = y;
		pos_button.do_it = cb_et;
		et_p = { x, y };
		et_l = l;

		pos_button.show();
		redraw();
	}
	//-------------------------------------------------------------------
	void Item_window::set_hexb()
	{
		istringstream is{ hex_inbox.get_string() };
		ostringstream os;

		int x = get_xval(is);
		int y = get_yval(is);
		int l = get_len(is);
		if (x == -7 || y == -7 || l == -7) {
			os << "Illegal values, try again.";
			message_box.put(os.str());
			redraw();
			return;
		}
		os << "Point: (" << x << ", " << y << ")\n" << "Length: " << l;
		message_box.put(os.str());

		pos_button.loc.x = x;
		pos_button.loc.y = y;
		pos_button.do_it = cb_hex;
		hex_p = { x, y };
		hex_l = l;

		pos_button.show();
		redraw();
	}
	//-------------------------------------------------------------------
	int Item_window::get_xval(istringstream& is)
	{
		char ch;
		int i = -7;
		is.get(ch);
		if (ch == '(') {
			i = 0;
			while (is.get(ch) && isdigit(ch)) i = i * 10 + ch - '0';
		}
		is.unget();
		return i;		
	}
	//-------------------------------------------------------------------
	int Item_window::get_yval(istringstream& is)
	{
		char ch;
		int i = -7;
		is.get(ch);
		if (ch == ',') {
			i = 0;
			while (is.get(ch) && isdigit(ch)) i = i * 10 + ch - '0';
		}
		is.unget();
		return i;
	}
	//-------------------------------------------------------------------
	int Item_window::get_len(istringstream& is)
	{
		char ch;
		int i = -7;
		is.get(ch);
		if (ch == ')') {
			i = 0;
			while (is.get(ch) && isdigit(ch)) i = i * 10 + ch - '0';
		}
		is.unget();
		return i;
	}
	int Item_window::get_hei(istringstream& is)
	{
		char ch;
		int i = -7;
		is.get(ch);
		if (ch == ',') {
			i = 0;
			while (is.get(ch) && isdigit(ch)) i = i * 10 + ch - '0';
		}
		is.unget();
		return i;
	}
	
}