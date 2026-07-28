<Layout>
	name = geometry-point-cloud
</Layout>

<Module>
#import point-cloud-data

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;
layout(location = 1) in vec3 in_color[];
layout(location = 1) out vec3 out_color;
void main() {
	vec4 p = gl_in[0].gl_Position;
	p /= p.w;
	out_color = in_color[0];
	gl_Position = p + vec4(-dx,-dy,0,0);
	EmitVertex();
	gl_Position = p + vec4( dx,-dy,0,0);
	EmitVertex();
	gl_Position = p + vec4(-dx, dy,0,0);
	EmitVertex();
	gl_Position = p + vec4( dx, dy,0,0);
	EmitVertex();
	EndPrimitive();
}
</Module>