#include <lib/base/base.h>
#include <lib/kabaexport/KabaExporter.h>
#include <clocale>
#include <ncurses.h>

extern "C" {


__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	e->link_func("_initscr", &initscr);
	e->link_func("curs_set", &curs_set);
	e->link_func("has_colors", &has_colors);
	e->link_func("start_color", &start_color);
	e->link_func("use_default_colors", &use_default_colors);
	e->link_func("init_pair", &init_pair);
	e->link_func("_waddnstr", &waddnstr);
//	e->link_func("_waddnwstr", &waddnwstr);
	e->link_func("_wrefresh", &wrefresh);
	e->link_func("_getmaxx", &getmaxx);
	e->link_func("_getmaxy", &getmaxy);
	e->link_func("_wmove", &wmove);
	e->link_func("_wgetch", &wgetch);
	e->link_func("_wclear", &wclear);
	e->link_func("_newwin", &newwin);
	e->link_func("_wborder", &wborder);
	e->link_func("_wattr_on", &wattr_on);
	e->link_func("_wattr_off", &wattr_off);
	e->link_func("_wbkgd", &wbkgd);
	e->link_func("_waddch", &waddch);
	e->link_func("endwin", &endwin);
	e->link_func("raw", &raw);
	e->link_func("noraw", &noraw);
	e->link_func("echo", &echo);
	e->link_func("noecho", &noecho);
	e->link_func("_keypad", &keypad);
	
	e->link_func("_setlocale", &setlocale);
}
}


