<Layout>
	version = 420
	pushsize = 128
	topology = points
	bindings = [[sampler,sampler,sampler,sampler,sampler,sampler,sampler,sampler,ubo,ubo,ubo,ubo,ubo]]
</Layout>

<FragmentShader>
#import point-cloud-data

layout(location = 1) in vec3 in_color;
layout(location = 0) out vec4 color;
void main() {
	color = vec4(in_color,1);
	float f = 0.8;
	color = f * color + (1-f) * vec4(1);
}
</FragmentShader>