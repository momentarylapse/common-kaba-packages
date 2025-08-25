#include "lib/base/base.h"
#include "lib/net/net.h"
#include "lib/net/_kaba_export.h"


extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	NetInit();
	export_package_net(e);
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}


