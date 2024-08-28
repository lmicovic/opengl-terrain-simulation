
#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <map>


#include "Entity.hpp"
#include "Light.hpp"
#include "camera.hpp"
#include "staticShader.hpp"
#include "EntityRenderer.h"
#include "TerrainShader.hpp"
#include "window.h"
#include "TerrainRenderer.hpp"


/*
    Master Renderer - koristi se za Optimizaciju Renderovanja,
                      vise Entiteta koji imaju zajednicke Modele.
*/
class MasterRenderer {

public:

    // Camera
    const float FOV = 70.0f;            // Field Of View - koliko siroko vidimo
    const float NEAR_PLANE = 0.1f;
    const float FAR_PLANE = 1000.0f;

    // Sky Color
    const float RED = 0.5f;
    const float GREEN = 0.5f;
    const float BLUE = 0.5f;

    glm::mat4 projectionMatrix;

    // Entity
    StaticShader staticShader = StaticShader();
    EntityRenderer renderer = EntityRenderer();

    // Terrain
    TerrainRenderer terrainRenderer;
    TerrainShader terrainShader;

    std::vector<Entity> entities;          // Svi Entiteti koji trebaju da se Renderuju, Entiteti predstavljaju Sve objekte koji trebaju da se Renderuju
    std::vector<Terrain> terrains;          // Svi Tereni Koji Trebaju da se Renderuju, Koristimo samo jedan ali moze i vise.

    MasterRenderer(StaticShader staticShader, TerrainShader terrainShader, Window window);

    // Functions
    //-----------------------------------------------------------------
    void render(std::vector<Light> lights, Camera camera);
    void prepare();
    void processEntity(Entity entity);
    void processTerrain(Terrain terrain);               // Add Terrain in List of Terrains
    glm::mat4 createProjectionMatrix(Window window);
    void enableCulling();
    void disableCulling();
    void cleanUp();
    //--------------------------------------------------------------



};


#endif // MASTER_RENDERER_H
