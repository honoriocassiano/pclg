uniform int octaves;

uniform float horizon;
uniform float cutoff;
uniform float time;
uniform float scale;

varying vec4 color;
varying vec3 position;
 
void main() {

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	position = gl_Vertex.xyz;

	float n = 0.0;

	color = vec4(0.4, 0.6, 1.0, 1.0);

	if(position.y < horizon) {
		n = 1.0 - (position.y / horizon);
	}

	color = (vec4(1.0, 1.0, 1.0, 1.0) - color) * n + color;
}
