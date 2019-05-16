#include "GUI.h"
#include "My_Graph_lib.h"

namespace Graph_lib{

	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title);
		void wait_for_button();
	private:
		Button next_button;
		Button quit_button;

		void next() { Fl::redraw(); }
		void quit() { button_pushed = true; }

		bool button_pushed;
		static void cb_next(Address, Address pw) { reference_to<My_window>(pw).next(); }
		static void cb_quit(Address, Address pw) { reference_to<My_window>(pw).quit(); }
	};

	struct Checkerboard : My_window {
		Checkerboard(Point xy, int w, int h, const string& title);	
	private:
		Vector_ref<Rectangle> rects;
		Menu row1;
		Menu row2;
		Menu row3;
		Menu row4;
		void create_rects();
		void attach_rects();
		Point top_left;
		void change_b01();
		void change_b02();
		void change_b03();
		void change_b04();
		void change_b05();
		void change_b06();
		void change_b07();
		void change_b08();
		void change_b09();
		void change_b10();
		void change_b11();
		void change_b12();
		void change_b13();
		void change_b14();
		void change_b15();
		void change_b16();
	};
	struct Img_window : My_window {
		Img_window(Point xy, int w, int h, const string& title);
	private:
		Image img_calvin;
		Button move_button;
		Button test_button;
		Point top_left;
		Out_box move_point;
		int legal_xmove();
		int legal_ymove();
		void move_image();
		static void cb_move(Address, Address pw) { reference_to<Img_window>(pw).move_image(); }
	};
	struct Item_window : Window{
		Item_window(Point xy, int w, int h, const string & title);
	private:
		Button cl_button;
		Button rt_button;
		Button et_button;
		Button hex_button;
		Button pos_button;
		In_box cl_inbox;
		In_box rt_inbox;
		In_box et_inbox;
		In_box hex_inbox;
		Out_box message_box;
		void add_circle();
		void add_rectangle();
		void add_equitri();
		void add_hexagon();
		void set_clb();
		void set_rtb();
		void set_etb();
		void set_hexb();
		int get_xval(istringstream& s);
		int get_yval(istringstream& s);
		int get_len(istringstream& s);
		int get_hei(istringstream& s);
		int do_nothing() { return 1; }
		int cl_r, rt_w, rt_h, et_l, hex_l;
		Point cl_p, rt_p, et_p, hex_p;
		static void cb_cl(Address, Address pw);
		static void cb_rt(Address, Address pw);
		static void cb_et(Address, Address pw);
		static void cb_hex(Address, Address pw);
	};
}