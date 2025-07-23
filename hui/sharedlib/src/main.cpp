#include "lib/base/base.h"
#include "lib/hui/_kaba_export.h"
#include "lib/hui/hui.h"
#include <stdio.h>

namespace hui {
	void init_low_level();
}


extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	printf("init hui...\n");
	hui::Application::allowed = false;
	hui::init_low_level();
	hui::_MakeUsable_();
	printf("export hui...\n");
	export_package_hui(e);
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}

