#include <lib/base/base.h>
#include <lib/pdf/_kaba_export.h>


extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::IExporter* e) {
	export_package_pdf(e);
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}


