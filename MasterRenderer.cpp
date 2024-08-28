#include "MaterRenderer.hpp"


MasterRenderer::MasterRenderer(StaticShader staticShader, TerrainShader terrainShader, Window window) {

    // Create Projection Matrix only once in our Application
    this->projectionMatrix = createProjectionMatrix(window);
//    staticShader.start();
//    staticShader.setMat4("projectionMatrix", this->projectionMatrix);   // Load Projection Matrix on uniform in Vertex Shader
//    staticShader.stop();
    //---------------------------------------------------------

    // Render Optimization
    //---------------------------------------------------------
    MasterRenderer::enableCulling();                                // Da se ne Renderuju Strane Entiteta koje se nevide.
    //---------------------------------------------------------


    this->staticShader = staticShader;
    this->renderer = EntityRenderer(window, this->staticShader, projectionMatrix);


    this->terrainShader = terrainShader;
    this->terrainRenderer = TerrainRenderer(this->terrainShader, projectionMatrix);


}


void MasterRenderer::prepare() {

    glEnable(GL_DEPTH_TEST);            // Enable Depth Testing
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

/*
    Render Terrain, Entities to the Screen
*/
void MasterRenderer::render(std::vector<Light> lights, Camera camera) {

    //------------------------------------------------------------------------
    // Render Entity
    //------------------------------------------------------------------------
    MasterRenderer::prepare();
    this->staticShader.start();

    // SkyColor
    this->staticShader.loadSkyColor(this->RED, this->GREEN, this->BLUE);

    this->staticShader.loadLight(lights);
    this->staticShader.loadViewMatrix(camera);
    this->renderer.render(this->entities);


    this->staticShader.stop();
    this->entities.clear();
    //------------------------------------------------------------------------

    //------------------------------------------------------------------------
    // Render Terrain
    //------------------------------------------------------------------------
    this->terrainShader.start();


    this->terrainShader.loadSkyColor(this->RED, this->GREEN, this->BLUE);
    this->terrainShader.loadLight(lights);
    this->terrainShader.loadViewMatrix(camera);
    this->terrainRenderer.render(this->terrains);


    this->terrainShader.stop();
    this->terrains.clear();

    MasterRenderer::cleanUp();
    //------------------------------------------------------------------------
}

/*
    Add Entity to Array of Entities that will be Rendered.
*/
void MasterRenderer::processEntity(Entity entity) {

    this->entities.push_back(entity);

}

/*
    Add Tettain to Array of Terrains that will be Rendered.
*/
void MasterRenderer::processTerrain(Terrain terrain) {

    this->terrains.push_back(terrain);

}

/*
    Create Projection Matrix
*/
glm::mat4 MasterRenderer::createProjectionMatrix(Window window) {


    glm::mat4 projectionMatrix;

    float aspectRatio = (float) window.WIDTH / (float) window.HEIGHT;           // Aspect Ration odnos izmedju - Sirine i Visine


    /*
        Use Perspective Projection.

            Perspective Projection:  use w component to Represetn the Depth of 3D image.
            Ortogonal Projection:    dont use Depth and w Component pa tako slika izgleda kao da je 2D nema dubinu.

    */
    projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, this->NEAR_PLANE, this->FAR_PLANE);

    return projectionMatrix;

}

void MasterRenderer::enableCulling() {
    glEnable(GL_CULL_FACE);                                         // Ne renderuje deo objekast koji nije okrenut Kameri
    glCullFace(GL_BACK);
}


void MasterRenderer::disableCulling() {
    glDisable(GL_CULL_FACE);
}

void MasterRenderer::cleanUp() {
//    this->entities.clear();
//    this->terrains.clear();
}
