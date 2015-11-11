
/*
varying vec3 lightDir,normal;

void main()
{
	lightDir = normalize(vec3(gl_LightSource[0].position));
	normal = gl_NormalMatrix * gl_Normal;

	gl_Position = ftransform();
} 
*/

uniform float time;
uniform int octaves;
//attribute float apply;
 
void main() {
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
/*
	 if(gl_Vertex.x >= 0 || gl_Vertex.y >= 0) {
		apply = 0.0;
	 } else {
	 	apply = 1.0;
	}
	*/
}
