#include <lib/base/base.h>
#include <lib/kabaexport/KabaExporter.h>
#include <mongoc/mongoc.h>


extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	e->link_func("_mongoc_init", &mongoc_init);
	e->link_func("_mongoc_cleanup", &mongoc_cleanup);
	e->link_func("_mongoc_client_new", &mongoc_client_new);
	e->link_func("_mongoc_client_destroy", &mongoc_client_destroy);
	e->link_func("_mongoc_client_get_collection", &mongoc_client_get_collection);
	e->link_func("_mongoc_collection_find_with_opts", &mongoc_collection_find_with_opts);
	e->link_func("_mongoc_collection_aggregate", &mongoc_collection_aggregate);
	e->link_func("_mongoc_collection_insert_one", &mongoc_collection_insert_one);
	e->link_func("_mongoc_collection_replace_one", &mongoc_collection_replace_one);
	e->link_func("_mongoc_collection_delete_one", &mongoc_collection_delete_one);
	e->link_func("_mongoc_collection_delete_many", &mongoc_collection_delete_many);
	e->link_func("_mongoc_cursor_next", &mongoc_cursor_next);
	e->link_func("_mongoc_cursor_destroy", &mongoc_cursor_destroy);
	e->link_func("_mongoc_collection_destroy", &mongoc_collection_destroy);
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}


