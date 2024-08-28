#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <vector>

#include "Terrain.hpp"
#include "TerrainShader.hpp"
#include "Entity.hpp"
#include "TextureModel.h"

class TerrainRenderer {

public:

    TerrainRenderer();
    TerrainRenderer(TerrainShader terrainShader, glm::mat4 projectionMatrix);
    void render(std::vector<Terrain> terrains);

private:

    TerrainShader terrainShader;
    void prepareTerrain(Terrain terrain);
    void bindTextures(Terrain terrain);
    void unbindTexturedModel();
    void loadModelMatrix(Terrain terrain);


};

#endif // TERRAIN_RENDERER_H
