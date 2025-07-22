#include <lib/base/base.h>
#include <lib/kabaexport/KabaExporter.h>
#include <sqlite3.h>


extern "C" {

__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	e->link_func("sqlite3_libversion_number", &sqlite3_libversion_number);
	e->link_func("_sqlite3_open_v2", &sqlite3_open_v2);
	e->link_func("_sqlite3_close", &sqlite3_close);
	e->link_func("_sqlite3_finalize", &sqlite3_finalize);
	e->link_func("_sqlite3_prepare", &sqlite3_prepare);
	e->link_func("_sqlite3_column_count", &sqlite3_column_count);
	e->link_func("_sqlite3_column_text", &sqlite3_column_text);
	e->link_func("_sqlite3_column_int", &sqlite3_column_int);
	e->link_func("_sqlite3_column_double", &sqlite3_column_double);
	e->link_func("_sqlite3_step", &sqlite3_step);
	e->link_func("_sqlite3_errmsg", &sqlite3_errmsg);
	e->link_func("_sqlite3_column_name", &sqlite3_column_name);
	e->link_func("_sqlite3_column_type", &sqlite3_column_type);
}
}


