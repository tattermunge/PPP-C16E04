

#include "../../lib_files/My_window.h"
using namespace Graph_lib;
int main()
try {

	Point tl(0, 0);
	
	Item_window iw(tl, 1280, 680, "C16E04");
	return gui_main();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}

