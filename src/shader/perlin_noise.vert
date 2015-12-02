uniform int octaves;

uniform float cutoff;
uniform float time;
uniform float scale;

varying vec3 position;
 
void main() {

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	position = gl_Vertex.xyz;
}
