#version 330 core

const int NumberOfLights = 20;

in vec2 textureCoords;
in vec3 normals;
in vec3 toLightVector[NumberOfLights];
in vec3 toCameraVector;

// Fog
in float visibility;


out vec4 FragColor;


uniform sampler2D textureSampler;

uniform vec3 lightColor[NumberOfLights];
uniform float shineDamper;		// Koliko odsijava objekat
uniform float reflectivity;

uniform vec3 lightDistance[NumberOfLights];

uniform vec3 skyColor;			// Sky Color 


void main()
{	
	// Ambinet Light
	float ambientFactor = 0.5;

	
	vec3 unitNormal = normalize(normals);
	vec3 unitVectorToCamera = normalize(toCameraVector);	// Jedinicni Vektor koji pokazuje od povrsine do Kamere
	
	
	// Calculate Light Diffuse And Specular for Every Light Source
	vec3 totalDeffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);
	
	for(int i = 0; i < NumberOfLights; i++) {
		
		
		// Attenuation - Point Light
		float distance = length(toLightVector[i]);	// Udaljenost Piksela do odredjenog Izvora svetlosti
		float attenuationFactor = lightDistance[i].x + (lightDistance[i].y * distance) + (lightDistance[i].z * distance * distance);
		//----------------------------------------------------------------
		
		
		vec3 unitLightVector = normalize(toLightVector[i]);
		
		// Diffse Light
		// How Bright Should Pixel be
		float nDotl = dot(unitNormal, unitLightVector);  // Ugao izmedju Normale i Vekora Svetla
		float brightness = max(nDotl, 0.0);				 // Vrednost izmedju nDotl i 0.0
		totalDeffuse = totalDeffuse + (brightness * lightColor[i]) / attenuationFactor;    // Dobijenu Difuznu Boju Delimo sa attenuationFactor kako bi Dobili Slabljenje Svetlosti za Diffuzu boju

		//----------------------------------------------------------------
		
		// Specular Light
		vec3 lightDirection = -unitLightVector;		// LightDirection je inverz jeinicnog Light Vekora
		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
		
		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);	// How Brigt Specular Light for current Pixel
		specularFactor = max(specularFactor, 0.0);									// Da ne bi bio negativan
		
		float dampedFactor = pow(specularFactor, shineDamper);						// Racuna koliko sija objekat
		totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColor[i]) / attenuationFactor;				// Dobijenu Difuznu Boju Delimo sa attenuationFactor kako bi Dobili Slabljenje Svetlosti za Specular boju
	
	}
	
	totalDeffuse = max(totalDeffuse, ambientFactor);
	totalSpecular = max(totalSpecular, ambientFactor);
	
	//----------------------------------------------------------------
		
	// Transaprent - kako ne bi renderovali Transparente Pixel-e:   2:00 min    https://www.youtube.com/watch?v=ZyzXBYVvjsg&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP&index=15
	vec4 textureColor = texture(textureSampler, textureCoords);
	if(textureColor.a < 0.5 ) {
		discard;
	}	
	//----------------------------------------------------------------
	
	FragColor = vec4(totalDeffuse, 1.0) * texture(textureSampler, textureCoords) + vec4(totalSpecular, 1.0);
	
	// Fog	- Fog predstavlja mix boje Objekt a i boje Neba.
	FragColor = mix(vec4(skyColor, 1.0), FragColor, visibility);
	//----------------------------------------------------------------
} 

