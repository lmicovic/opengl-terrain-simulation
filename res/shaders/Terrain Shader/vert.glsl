#version 400 core
layout (location = 0) in vec3 aPos;   // Vertex Pozicija
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormals;

const int NumberOfLights = 20;

out vec2 textureCoords;
out vec3 normals;
out vec3 toLightVector[NumberOfLights];				// Multiple Lights Support - Vector From Sufrace Normal to Light
out vec3 toCameraVector;				// Vector From Vertex to the Camera

// Fog
out float visibility;
const float density = 0.002;			// Gustina Magle
const float gradient = 1.5;				// Gradient Magle koliko brzo prelazi iz viljivog u Maglu
//----------------------------------

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 lightPosition[NumberOfLights];	// Multiple Lights Support

/*
	Fake Light Koristimo kod Objekata kao sto je trava kako bi njegove normale pokazivale na Gore kako bi realnije osvetljenje.
*/
uniform float useFakeLighting;			// Da li treba da koristimo Fake Ligt ili ne 0.0 Ako ne treba da kristimo Fake Lighting, 1.0 ako treba da koristimo Fake Lighg



void main()
{		
	
	vec4 worldPosition = transformationMatrix * vec4(aPos, 1.0);
	
	
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
	textureCoords = aTexCoords;
	normals = (transformationMatrix * vec4(aNormals, 0.0)).xyz;
	
	
	// Fake Lighting	
	//------------------------------------------------------------------------------
 	vec3 actualNormal = normals;		// Actual Normals of Object
	if(useFakeLighting > 0.0) {		// Proveravamo da li treba da koristimo Fake Light
		// Ako koristimo Fake Light
		actualNormal = vec3(0.0, 1.0, 0.0);	// Postavljamo sve normale na Gore - Y axis.
	}
	//------------------------------------------------------------------------------
	
	// Diffuse Light - Need to Calculate Vector That Points to Light for Every Light Source
	for(int i = 0; i < NumberOfLights; i++) {
		toLightVector[i] = lightPosition[i] - worldPosition.xyz;
	}
	
	
	// Specular Light
	toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
		
		
	// Fog
	vec4 positionRelativeToCam = viewMatrix * worldPosition; 	// Ovo nam Daje Poziciju Vertex-a u odnosu na Kameru.
	float distance = length(positionRelativeToCam.xyz);		// Udaljenost izmedju Vertex-a i Kamere
	visibility = exp(-pow((distance * density), gradient));			// e^(distance * fogDensity) ^ gradient   - Exponencialna Formula za racunanje Magle
	visibility = clamp(visibility, 0.0, 1.0);	// Zelimo da Visibility vrednost bude izmedju 0 i 1
	//--------------------------------------------------------------------------------------------------

	


	
}  