#include <lib/base/base.h>
#include <lib/pattern/_kaba_export.h>


extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::IExporter* e) {
	export_package_obs(e);
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}


