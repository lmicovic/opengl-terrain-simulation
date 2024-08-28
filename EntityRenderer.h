
#ifndef RENDERER_H
#define RENDERER_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <map>
#include <vector>

#include "rawModel.h"
#include <glad/glad.h>
#include "Entity.hpp"
#include "staticShader.hpp"
#include "TextureModel.h"
#include "rawModel.h"
#include "window.h"


// Render Model From VAO
class EntityRenderer {

public:



//    const float FOV = 70.0f;            // Field Of View - koliko siroko vidimo
//    const float NEAR_PLANE = 0.1f;
//    const float FAR_PLANE = 100.0f;
    StaticShader staticShader;

    EntityRenderer();
    EntityRenderer(Window window, StaticShader staticShader, glm::mat4 projectionMatrix);
    //void prepare();
    void render(std::vector<Entity> entities);
    void render(Window window, Entity entity, StaticShader staticShader);

private:

    void prepareTexturedModel(TexturedModel texturedModel);
    void unbindTexturedModel();
    void prepareInstance(Entity Entity);
    //glm::mat4 createProjectionMatrix(Window window);

};




#endif
