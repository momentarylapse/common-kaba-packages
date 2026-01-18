#include <lib/base/base.h>
#include <lib/kabaexport/KabaExporter.h>
#include <libssh2.h>


extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	libssh2_init(0);
	e->link_func("_libssh2_trace", &libssh2_trace);
	e->link_func("_libssh2_session_init_ex", &libssh2_session_init_ex);
	e->link_func("_libssh2_session_handshake", &libssh2_session_handshake);
	e->link_func("_libssh2_hostkey_hash", &libssh2_hostkey_hash);
	e->link_func("_libssh2_userauth_list", &libssh2_userauth_list);
	e->link_func("_libssh2_userauth_publickey_fromfile_ex", &libssh2_userauth_publickey_fromfile_ex);
	e->link_func("_libssh2_channel_open_ex", &libssh2_channel_open_ex);
}
}


