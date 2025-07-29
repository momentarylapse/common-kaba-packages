#include <lib/base/base.h>
#include <lib/kabaexport/KabaExporter.h>
#include <bson/bson.h>
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


