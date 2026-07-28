<Layout>
	name = vertex-point-cloud-color
</Layout>

<Module>
#import point-cloud-data

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec4 in_color;
layout(location = 1) out vec3 out_color;
void main() {
	gl_Position = matrix.project * matrix.view * matrix.model * vec4(in_pos, 1);
	out_color = in_color.rgb;
}
</Module>