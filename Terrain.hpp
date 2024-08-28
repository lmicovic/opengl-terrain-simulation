#ifndef TERRAIN_H
#define TERRAIN_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <cmath>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "rawModel.h"
#include "modelTexture.h"
#include "loader.h"
#include "TerrainTexture.hpp"
#include "TerrainTexturePack.hpp"
#include "math.hpp"


/*
    Used to Return Array from Function
*/
typedef struct Height {

    float height[256][256];

} HeightPojo;


/*
    Terrain:   hold All Data for Terrain.
*/
class Terrain {

public:
    float x;    // Position of Terrain in World
    float z;    // Position of Terrain in World

    RawModel rawModel;              // Raw Data for Terrain
    ModelTexture modelTexture;      // Main Texture for Terrain(grass)
    TerrainTexture blendMap;        // Terrain Bledn Map
    TerrainTexturePack terrainTexturePack;  // All Terrain Textures for MutliTexturing

    Height heights; // Hold Data for Every Vertex Hight.


    float getHeightOfTerrain(float worldX, float worldZ, Height heights);
    Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack terrainTexturePack, TerrainTexture blendMap);


private:

    float SIZE;          // Default 800.0f
    int VERTEX_COUNT;    // Default 128


    std::vector<std::string> removeDupWord(std::string str);
    RawModel generateTerrain(Loader loader);
    HeightPojo generateHeights();       // Genereate Vertex Terrain Heiht from Heigth Map
    glm::vec3 calucalateNormal(int x, int z, HeightPojo heigts);


};


#endif // TERRAIN_H
