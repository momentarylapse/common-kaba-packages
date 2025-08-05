#include "lib/base/base.h"
#include "lib/xhui/_kaba_export.h"
#include "lib/xhui/xhui.h"
#include "lib/xhui/Theme.h"
#include "lib/os/app.h"
#include "lib/os/msg.h"



extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	xhui::init({}, "kaba");
	export_package_xhui(e);
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}


