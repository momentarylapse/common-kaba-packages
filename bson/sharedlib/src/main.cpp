#include <lib/base/base.h>
#include <lib/kabaexport/KabaExporter.h>
#include <bson/bson.h>


extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	e->link_func("_bson_new_from_json", &bson_new_from_json);
	e->link_func("_bson_as_canonical_extended_json", &bson_as_canonical_extended_json);
	e->link_func("_bson_as_relaxed_extended_json", &bson_as_relaxed_extended_json);
	e->link_func("_bson_free", &bson_free);
	e->link_func("_bson_destroy", &bson_destroy);
	e->link_func("_bson_new_from_data", &bson_new_from_data);
	e->link_func("_bson_iter_init", &bson_iter_init);
	e->link_func("_bson_iter_next", &bson_iter_next);
	e->link_func("_bson_iter_key", &bson_iter_key);
	e->link_func("_bson_iter_int32", &bson_iter_int32);
	e->link_func("_bson_iter_int64", &bson_iter_int64);
	e->link_func("_bson_iter_double", &bson_iter_double);
	e->link_func("_bson_iter_utf8", &bson_iter_utf8);
	e->link_func("_bson_iter_array", &bson_iter_array);
	e->link_func("_bson_iter_oid", &bson_iter_oid);
	e->link_func("_bson_oid_to_string", &bson_oid_to_string);
	e->link_func("_bson_iter_type", &bson_iter_type);
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}


