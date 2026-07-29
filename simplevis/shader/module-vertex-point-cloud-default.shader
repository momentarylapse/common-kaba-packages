<Layout>
	name = vertex-point-cloud-default
</Layout>

<Module>
#import point-cloud-data

layout(location = 0) in vec3 in_pos;
layout(location = 1) in float in_intensity;
layout(location = 1) out vec3 out_color;


void main() {
	gl_Position = matrix.project * matrix.view * matrix.model * vec4(in_pos, 1);
	if (color_mode == 0) { // auto
		vec3 t = abs((in_pos.xyz - (vmin + vmax) / 2) / (vmax - vmin) * 2);
		out_color = t + vec3(1) * (1 - length(t)) / 2;
	} else if (color_mode == 1) { // fixed
		out_color = color_fixed.rgb;
	} else { // intensity
		out_color = vec3(1,1,1);
		//out_color = heatmap(sqrt(in_intensity / max_intensity));
	}
}
</Module>