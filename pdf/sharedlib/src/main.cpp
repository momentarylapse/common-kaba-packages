#include "lib/doc/_kaba_export.h"


extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	export_package_pdf(e);
}
}


