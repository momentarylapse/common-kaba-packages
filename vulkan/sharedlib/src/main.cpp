#include "lib/base/base.h"
#include "lib/vulkan/_kaba_export.h"

extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	export_package_vulkan(e);
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}


