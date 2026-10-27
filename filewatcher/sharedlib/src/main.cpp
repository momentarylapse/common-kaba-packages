#include <lib/base/base.h>
#include <lib/obs/FileWatcher.h>
#include <lib/kapi/KabaExporter.h>


extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::IExporter* e) {
	e->package_info("filewatcher", "0.1");

	obs::FileWatcher w;
	e->declare_class_size("FileWatcher", sizeof(obs::FileWatcher));
	e->declare_class_element("FileWatcher.out_edited", &obs::FileWatcher::out_edited);
	e->declare_class_element("FileWatcher.out_created", &obs::FileWatcher::out_created);
	e->declare_class_element("FileWatcher.out_deleted", &obs::FileWatcher::out_deleted);
	e->declare_class_element("FileWatcher.out_moved", &obs::FileWatcher::out_moved);
	e->link_class_func("FileWatcher.__init__", &kaba::generic_init<obs::FileWatcher>);
	e->link_virtual("FileWatcher.__delete__", &kaba::generic_virtual<obs::FileWatcher>::__delete__, &w);
	e->link_class_func("FileWatcher.add", &obs::FileWatcher::add);
	e->link_class_func("FileWatcher.iterate", &obs::FileWatcher::iterate);
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}


