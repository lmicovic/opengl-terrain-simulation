#ifndef TERRAIN_TEXTURE_PACKET_H
#define TERRAIN_TEXTURE_PACKET_H

#include "TerrainTexture.hpp"

/*
    TerrainTexturePack Class:   contains 4 Textures That i want to Render to Terrain. Used for Terrain Multi Texturing.
*/
class TerrainTexturePack {

public:

    TerrainTexture backgroundTexture;
    TerrainTexture rTexture;
    TerrainTexture gTexture;
    TerrainTexture bTexture;

    TerrainTexturePack();
    TerrainTexturePack(TerrainTexture backgroundTexture, TerrainTexture rTexture, TerrainTexture gTexture, TerrainTexture bTexture);

};

#endif // TERRAIN_TEXTURE_PACKET_H

