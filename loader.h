


#ifndef LOADER_H
#define LOADER_H

#include <vector>

#include <glad/glad.h>
#include "TextureData.hpp"

#include "intList.hpp"
#include "rawModel.h"
#include "stb_image.h"


#include <string>
#include <iostream>


// Loading 3D Model in GPU Memmory.
class Loader {

public:

    IntList* vbos;
    IntList* vaos;
    IntList* textures;

    Loader();
    RawModel loadToVAO(std::vector<float> positions, std::vector<unsigned int> indices, std::vector<float> textureCoords, std::vector<float> normals);
    unsigned int loadTexture(const char* filePath, bool okreni);
    std::vector<TextureData> decodeTextureFile(std::vector<std::string> filePaths);

private:

    GLuint createVAO();

    void storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float> data);

    void unbindVAO();

    // Load up Indices Buffers and Bind to VAO
    void bindIndicesBuffer( std::vector<unsigned int> indices);

    // Clean All VBOs and VAOs from Lists
    void cleanUp();



};

#endif // LOADER_H
