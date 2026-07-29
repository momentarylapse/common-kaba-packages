<Layout>
	name = point-cloud-data
</Layout>
<Module>

#import basic-interface

#ifdef vulkan
layout(push_constant) uniform User {
	float dx;
	float dy;
	int color_mode;
	float max_intensity;
	vec3 vmin;
	vec3 vmax;
	vec4 color_fixed;
};
#else
uniform float dx = 0.01;
uniform float dy = 0.01;
uniform int color_mode = 1;
uniform vec3 vmin;
uniform vec3 vmax;
uniform float max_intensity = 1.0;
uniform vec4 color_fixed;
#endif
</Module>
