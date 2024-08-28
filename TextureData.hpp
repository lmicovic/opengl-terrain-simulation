#ifndef TEXTURE_DATA_H
#define TEXTURE_DATA_H

/*
    Class Store Data of Texture
*/
class TextureData {

public:

     unsigned int textureID;    // ID of Texture
     int height;
     int width;
     unsigned char* data;       // pixels of Texture

     TextureData();
     TextureData(unsigned int textureID, int width, int height, unsigned char* data);

};


#endif // TEXTURE_DATA_H
