#include <lib/base/base.h>
#include <lib/kabaexport/KabaExporter.h>
#include <zlib.h>


extern "C" {


__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	e->link_func("_compressBound", &compressBound);
	e->link_func("_deflate", &deflate);
	e->link_func("_compress", &compress);
	e->link_func("_uncompress", &uncompress);
}
}


