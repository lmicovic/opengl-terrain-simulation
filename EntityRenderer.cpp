
#include "math.hpp"
#include "staticShader.h"
#include "EntityRenderer.h"
#include <iostream>
#include "window.h"
#include <math.h>

// #include "model.hpp"

EntityRenderer::EntityRenderer() {



}

EntityRenderer::EntityRenderer(Window window, StaticShader staticShader, glm::mat4 projectionMatrix){

    this->staticShader = staticShader;

    this->staticShader.start();
    staticShader.setMat4("projectionMatrix", projectionMatrix);   // Load Projection Matrix on uniform in Vertex Shader
    this->staticShader.stop();


//    this->staticShader = staticShader;
//
//
////    // Render Optimization
////    //---------------------------------------------------------
////    glEnable(GL_CULL_FACE);                                         // Ne renderuje deo objekast koji nije okrenut Kameri
////    glCullFace(GL_BACK);
////    //---------------------------------------------------------
//
//    // Create Projection Matrix only once in our Application
//    //glm::mat4 projectionMatrix = createProjectionMatrix(window);
//
//    staticShader.start();
//    staticShader.setMat4("projectionMatrix", projectionMatrix);   // Load Projection Matrix on uniform in Vertex Shader
//    staticShader.stop();

}

//void EntityRenderer::prepare() {
//
//    glEnable(GL_DEPTH_TEST);            // Enable Depth Testing
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}


void EntityRenderer::render(std::vector<Entity> entities) {

//    // Retrive All Keys from HashMap - entities
//    std::vector<TexturedModel> keys;                // All Keys
//    for(std::map<TexturedModel, std::vector<Entity>>::iterator it = entities.begin(); it != entities.end(); ++it) {
//      keys.push_back(it->first);
//    }
//    //-------------------------------------------------------------------

    // Loop All TexturedModels - Keys
    int i;
    for(i = 0; i < entities.size(); i++) {

        TexturedModel texturedModel2 = entities.at(i).texturedModel;
        Entity entity = entities.at(i);

        EntityRenderer::prepareTexturedModel(texturedModel2);

        //--------------------------------------------------------------
        // Get All Entities that use that TexturedModel
//        std::vector<Entity> batch;  // Store All Entities for TexturedModel
//        for(auto itr = entities.find(texturedModel2); itr != entities.end(); itr++) {       // Search Values for Given Key - Key: TexturedModel, Value: vector<Entitiy> entities
//
//            batch.assign(itr->second.begin(), itr->second.end());   // Add All Entities From TexturedModel to Batch
//
//        }
        //-------------------------------------------------------------

        int j;
       // for(j = 0; j < batch.size(); j++) {

            EntityRenderer::prepareInstance(entity);
            glDrawArrays(GL_TRIANGLES, 0, entity.texturedModel.rawModel.vertexCount);
        //}

        EntityRenderer::unbindTexturedModel();


    }


}

// Enable OpenGL Texture Setting for TexturedModel
void EntityRenderer::prepareTexturedModel(TexturedModel texturedModel) {

    RawModel rawModel = texturedModel.rawModel;

    glBindVertexArray(rawModel.vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    // Fake Lighting
    ModelTexture texture = texturedModel.texture;
    if(texture.hasTransparency == true) {
        glDisable(GL_CULL_FACE);
    }
    this->staticShader.loadFakeLightingVariable(texture.useFakeLighting);
    //---------------------------------------------------------------------------------


    // Specular Light Setting
    this->staticShader.loadShineVariables(texture.shineDamper, texture.reflectivity);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel.texture.textureID);
    //---------------------------------------------------------------------------------
}

// Settup Tranformation Matrix
void EntityRenderer::prepareInstance(Entity entity) {

    Math math;
    glm::mat4 transformationMatrix = math.createTransformationMatrix(entity.position, entity.rotX, entity.rotY, entity.rotZ, entity.scale);     // Create TransformationMatrix - Model Matrix
    //staticShader.loadTransformationMatrix(transformationMatrix);    // Load Model Matrix to its Uniform on Vertex Shader
    staticShader.setMat4("transformationMatrix", transformationMatrix);    // Load Model Matrix to its Uniform on Vertex Shader

}

// Unbind OpenGL Setting for Current Active Texture
void EntityRenderer::unbindTexturedModel() {

    glEnable(GL_CULL_FACE);                                         // Ne renderuje deo objekast koji nije okrenut Kameri
    glCullFace(GL_BACK);


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);

}



void EntityRenderer::render(Window window, Entity entity, StaticShader staticShader) {

    TexturedModel model = entity.texturedModel;

    // Specular Light
    ModelTexture texture = entity.texturedModel.texture;
    staticShader.loadShineVariables(texture.shineDamper, texture.reflectivity);     // Load Specular Data of Object to Fragment Shade
    //---------------------------------------------------------------------

    glBindVertexArray(model.rawModel.vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Load Tranfromations to Vertex Shader
    Math math;
    glm::mat4 transformationMatrix = math.createTransformationMatrix(entity.position, entity.rotX, entity.rotY, entity.rotZ, entity.scale);     // Create TransformationMatrix - Model Matrix
    //staticShader.loadTransformationMatrix(transformationMatrix);    // Load Model Matrix to its Uniform on Vertex Shader
    staticShader.setMat4("transformationMatrix", transformationMatrix);    // Load Model Matrix to its Uniform on Vertex Shader


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.texture.textureID);




    // std::cout << entity.texturedModel.rawModel.vertexCount << std::endl;



    glDrawElements(GL_TRIANGLES, entity.texturedModel.rawModel.vertexCount, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, entity.texturedModel.rawModel.vertexCount);


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);


}

//glm::mat4 EntityRenderer::createProjectionMatrix(Window window) {
//
//
//    glm::mat4 projectionMatrix;
//
//    float aspectRatio = (float) window.WIDTH / (float) window.HEIGHT;
//    float scaleY = (1.0f / std::tan(glm::radians(FOV / 2.0f))) * aspectRatio;
//    float scaleX = scaleY / aspectRatio;
//    float frustumLength = this->FAR_PLANE - this->NEAR_PLANE;
//
//    projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, this->NEAR_PLANE, this->FAR_PLANE);
//
//    return projectionMatrix;
//
//}



