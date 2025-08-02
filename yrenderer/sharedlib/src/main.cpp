#include "lib/base/base.h"
#include "lib/math/rect.h"
#include "lib/ygraphics/graphics-impl.h"
#include "lib/yrenderer/_kaba_export.h"



extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	export_package_yrenderer(e);
}
}

namespace yrenderer {
	rect dynamicly_scaled_area(ygfx::FrameBuffer *fb) {
		return rect(0, fb->width, 0, fb->height);
	}

	rect dynamicly_scaled_source() {
		return rect(0, 1, 0, 1);
	}
}

float global_shadow_box_size = 1000;


// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}


