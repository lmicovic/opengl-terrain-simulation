#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

// Represent Texture
class ModelTexture {

public:

    unsigned int textureID;

    bool hasTransparency;    // Default false - ako Texture ima providne delove koristi se u Shaderu kako bi izbebli probleme u Prikazu
    bool useFakeLighting;    // Default false - Fake Light Koristimo kod Objekata kao sto je trava kako bi njegove normale pokazivale na Gore kako bi dobili relnije osvetljenje.

    // Data for Specular Light
    float shineDamper;      // Default 1.0f
    float reflectivity;     // Default 0.0f

    ModelTexture();
    ModelTexture(unsigned int id);
    unsigned int getTextureID();

};



#endif // MODELTEXTURE_H
