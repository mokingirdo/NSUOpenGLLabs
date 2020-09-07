#version 110

struct Light
{
	vec4	type;		// тип источника
	vec4	position;	// позиция источника (есть у Point и Spot)
	vec4	direction;	// направление света
	vec4	color;		// (цвет.r, цвет.g, цвет.b, интенсивность)
	vec4	corner;		//угол для spot
};

// Shader parameters
uniform mat4 matWorldNormal;
uniform mat4 matWorldT;
uniform vec4 materialColor;
uniform vec4 lightsCount;
uniform Light lights[3];
uniform vec4 cameraPosition;

varying vec3 localPosition;
varying vec3 localNormal;


float atten(float type, vec3 vertexPos, float epsilon)
{
	float atten = 0.;
	if((type - 1.0) < epsilon)	{
				atten = 1.;
			}
			else{
				atten = (10./pow(length(vertexPos ),3.));
			}
	return atten;
}

float spot (float type, vec4 direction, vec4 corner,float epsilon,vec3 vertexPos, vec4 position)
{
	float spot = 1.;

		if((type - 3.0) < epsilon)	{
				float a = (dot(normalize(direction.xyz), normalize(vertexPos - position.xyz)) - cos(corner.y)) / (cos(corner.x) - cos(corner.y));
				spot = pow(clamp(a, 0.0, 1.0), 1.0);
			}
	return spot;
}

vec3 calcDiffuse(vec4 lightCol, vec3 lightDir, vec3 vertexNormal,float type, float epsilon, vec3 vertexPos, vec4 corner, vec4 direction, vec4 position)
{
//in the middle of 1 and 0
//dot - multiply
//float atten;
	float diffuse = clamp( dot(-lightDir, vertexNormal), 0.0, 1.0 );

	// Цвет = diffuse * (цвет источника) * (интенсивность источника)
	vec3 color = atten(type, vertexPos, epsilon)*diffuse * lightCol.rgb * lightCol.a * spot(type,direction,corner,epsilon,vertexPos, position);
	return color;
}

vec3 calcSpecular(vec4 lightCol, vec3 lightDir, vec3 vertexNormal, float type, float epsilon, vec3 vertexPos, vec4 corner, vec4 direction, vec4 position)
{
	vec3 H = normalize(normalize(cameraPosition.xyz - localPosition) - lightDir);
	//float specular = clamp( pow(dot(H, vertexNormal),10.), 0.0, 1.0 );
	float specular = pow(  clamp( dot(H, vertexNormal), 0.0, 1.0 ), 3000.);

	// Цвет = specular * (цвет источника) * (интенсивность источника)
	vec3 color = atten(type, vertexPos, epsilon)*specular * lightCol.rgb * lightCol.a * spot(type,direction,corner,epsilon,vertexPos, position);

	return color;
}


void main()
{
	vec3 col = vec3(0,0,0);

	// Переводим нормаль из локальной в глобальную систему координат
	vec3 vertexNormal = (vec4(localNormal, 0.0) * matWorldNormal).xyz;
	vertexNormal = normalize(vertexNormal);
	
	// Переводим позицию из локальной в глобальную систему координат
	vec3 vertexPos = (vec4(localPosition, 1.0) * matWorldT).xyz;
	
	for (int i = 0; i < 3; ++i)
	{
		// Выходим, как только закончились источники освещения
                if (float(i) >= lightsCount.x) break;
		
		float type = lights[i].type.x;
		float epsilon = 0.001;
		
		vec4 lightCol = lights[i].color;
		vec3 lightDir = vec3(0,0,0);
	
		// Directional light
                if (abs(type - 1.0) < epsilon)
		{
			lightDir = normalize(lights[i].direction.xyz).xyz;
		}
		// Point light
                else if (abs(type - 2.0) < epsilon)
		{
			lightDir = normalize(vertexPos - lights[i].position.xyz).xyz;
		}
		// Spot light
                else if (abs(type - 3.0) < epsilon)
		{
			//lightDir = normalize(lights[i].direction.xyz).xyz + normalize(vertexPos - lights[i].position.xyz).xyz;
			lightDir = normalize(vertexPos - lights[i].position.xyz).xyz;
		}
		
		col += materialColor.rgb * calcDiffuse(lightCol, lightDir, vertexNormal,type, epsilon,vertexPos - lights[i].position.xyz, lights[i].corner, lights[i].direction, lights[i].position);
		col += materialColor.rgb * calcSpecular(lightCol, lightDir, vertexNormal, type, epsilon,vertexPos - lights[i].position.xyz, lights[i].corner, lights[i].direction, lights[i].position);
	}
	
	gl_FragColor = vec4(col, 1.0);
        gl_FragColor.a = 1.0;
}
