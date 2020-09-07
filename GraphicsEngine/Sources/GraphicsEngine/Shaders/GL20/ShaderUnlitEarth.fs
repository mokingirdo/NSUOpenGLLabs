#version 110


varying vec2 uv1;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{
	vec2 uv1Scale = vec2(1, 1);
	vec3 color1 = texture2D( texture1, uv1.xy * uv1Scale ).rgb;
	
	gl_FragColor.rgb = color1;
	gl_FragColor.a = 1.0;
}