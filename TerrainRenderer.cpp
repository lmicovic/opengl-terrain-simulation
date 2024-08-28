
#include "TerrainRenderer.hpp"

TerrainRenderer::TerrainRenderer() {



}

TerrainRenderer::TerrainRenderer(TerrainShader terrainShader, glm::mat4 projectionMatrix) {

    this->terrainShader = terrainShader;

    terrainShader.start();
    terrainShader.setMat4("projectionMatrix", projectionMatrix);
    terrainShader.connectTextureUnits();
    terrainShader.stop();

}

void TerrainRenderer::render(std::vector<Terrain> terrains) {

    int i;
    for(i = 0; i < terrains.size(); i++) {
        TerrainRenderer::prepareTerrain(terrains.at(i));
        TerrainRenderer::loadModelMatrix(terrains.at(i));

        //glDrawArrays(GL_TRIANGLES, 0, terrains.at(i).rawModel.vertexCount);
        glDrawElements(GL_TRIANGLES, terrains.at(i).rawModel.vertexCount, GL_UNSIGNED_INT, 0);

        TerrainRenderer::unbindTexturedModel();
    }

}



// Enable OpenGL Texture Setting for TexturedModel
void TerrainRenderer::prepareTerrain(Terrain terrain) {

    RawModel rawModel = terrain.rawModel;

    glBindVertexArray(rawModel.vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    TerrainRenderer::bindTextures(terrain);

    // Specular Light Setting
    // this->terrainShader.loadShineVariables(terrain.texture.shineDamper, texture.reflectivity);



}

// Bind All Textures to use MultiTexture in Terrain Shader
void TerrainRenderer::bindTextures(Terrain terrain) {

    TerrainTexturePack terrainTexturePack = terrain.terrainTexturePack;

    // Background - Crna Pozadina iz BlendMap
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrainTexturePack.backgroundTexture.textureID);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, terrainTexturePack.rTexture.textureID);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, terrainTexturePack.gTexture.textureID);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, terrainTexturePack.bTexture.textureID);

    // BlendMap - Sema kako da se crta Textura za Terrain
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, terrain.blendMap.textureID);

}


// Unbind OpenGL Setting for Current Active Texture
void TerrainRenderer::unbindTexturedModel() {

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);

}

// Settup Tranformation Matrix
void TerrainRenderer::loadModelMatrix(Terrain terrain) {

    Math math;
    glm::mat4 transformationMatrix = math.createTransformationMatrix(glm::vec3(terrain.x, 0.0f, terrain.z), 0.0f, 0.0f, 0.0f, 1.0f);     // Create TransformationMatrix - Model Matrix
    //staticShader.loadTransformationMatrix(transformationMatrix);    // Load Model Matrix to its Uniform on Vertex Shader
    terrainShader.setMat4("transformationMatrix", transformationMatrix);    // Load Model Matrix to its Uniform on Vertex Shader

}
