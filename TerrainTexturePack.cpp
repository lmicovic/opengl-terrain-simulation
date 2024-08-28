
#include "TerrainTexturePack.hpp"

TerrainTexturePack::TerrainTexturePack() {



}

TerrainTexturePack::TerrainTexturePack(TerrainTexture backgroundTexture, TerrainTexture rTexture, TerrainTexture gTexture, TerrainTexture bTexture) {

    this->backgroundTexture = backgroundTexture;
    this->rTexture = rTexture;
    this->gTexture = gTexture;
    this->bTexture = bTexture;

}
