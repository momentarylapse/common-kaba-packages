#include <lib/base/base.h>
#include <lib/math/rect.h>
#include <lib/kapi/KabaExporter.h>
#include <lib/kapi/kapi.h>
#include <lib/ygraphics/graphics-impl.h>
#include <lib/yrenderer/_kaba_export.h>
#include <lib/profiler/Profiler.h>


KABA_PACKAGE_EXPORT_BEGIN
KABA_PACKAGE_EXPORT void export_symbols(kaba::IExporter* e) {
	profiler::init_external(e->context()->get_global_symbol("profiler", "state"));
	export_package_yrenderer(e);
}
KABA_PACKAGE_EXPORT_END

namespace yrenderer {
	rect dynamicly_scaled_area(ygfx::FrameBuffer *fb) {
		return rect(0, fb->width, 0, fb->height);
	}

	rect dynamicly_scaled_source() {
		return rect(0, 1, 0, 1);
	}
}

float global_shadow_box_size = 1000;


