#include <lib/base/base.h>
#include <lib/kapi/KabaExporter.h>
#include <lib/profiler/_kaba_export.h>
#include <lib/profiler/Profiler.h>


KABA_PACKAGE_EXPORT_BEGIN
KABA_PACKAGE_EXPORT void export_symbols(kaba::IExporter* e) {
	profiler::init();
	export_package_profiler(e);
}

KABA_PACKAGE_EXPORT void* export_globals(const string& name) {
	if (name == "state")
		return profiler::state;
	return nullptr;
}
KABA_PACKAGE_EXPORT_END

