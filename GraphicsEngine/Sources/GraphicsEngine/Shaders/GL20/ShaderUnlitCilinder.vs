#version 110

// Vertex structure
// Set order of vertex structure (position, color)
// Search in C++ code funciton GL20Mesh::Render()
// glVertexAttribPointer(0, ...) // this is "position"
// glVertexAttribPointer(1, ...) // this is "color"
attribute vec3 position;
attribute vec4 color;

// Shader parameters
// Search in C++ code functions like "glUniform4"
// i.e. functions: glUniform4fv(), glUniformMatrix4fv().
// These functions pass to shader parameters listed below
uniform vec4 constColor;
uniform vec4 time;
uniform mat4 matrixWorldViewProjT;

void main()
{
	float t = cos(time.r)*2.;
	
	mat3 rot = {{cos(t), 0., -sin(t)},{0.,1.,0.},{sin(t),0,cos(t)}};

	vec3 p1 = position;
	vec3 p2 = p1*rot;

	vec3 p ;
	
	float i = (1.+p1.y)/2.;

	 p = p1*(1.-i)+p2*(i);

	gl_Position = vec4(p, 1.0) * matrixWorldViewProjT;
	gl_FrontColor = constColor * color;
}