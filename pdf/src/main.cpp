#include "lib/base/base.h"
#include "lib/doc/pdf.h"
#include "lib/doc/ttf.h"
#include "KabaExporter.h"
#include <stdio.h>


extern "C" {


__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	//printf("<glfw export>\n");
	e->declare_class_size("Parser", sizeof(pdf::Parser));
	e->link("Parser.__init__", (void*)&kaba::generic_init<pdf::Parser>);
	e->link("Parser.__delete__", (void*)&kaba::generic_delete<pdf::Parser>);
	e->link("Parser.set_page_size", (void*)&pdf::Parser::set_page_size);
	e->link("Parser.add_page", (void*)&pdf::Parser::add_page);
	e->link("Parser.save", (void*)&pdf::Parser::save);
	
	e->link("add_font_directory", (void*)&ttf::add_font_directory);
}
}


