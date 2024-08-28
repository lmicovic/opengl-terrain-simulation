#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "shaderProgram.hpp"
#include "camera.hpp"
#include "math.hpp"
#include "Light.hpp"


/*
    Class that represent Shader for Entity - Entity is All Models on Screen except Terrain and CubeMap.
    Used to Load Uniform Data to Shaders

    StaticShader extends ShaderProgram which is Parent Class for All Different Shaders in Program.

*/
class StaticShader: public ShaderProgram {
  public:

    static int const MAX_LIGHTS = 20; // Maximum Number of Lights

    // Uniform Locations
    int locaion_transformationMatrix;
    int location_projectionMatrix;
    int location_viewMatrix;
    int location_lightPosition[MAX_LIGHTS];
    int location_lightColor[MAX_LIGHTS];
    int location_shineDamter;
    int location_reflectivity;
    int location_useFakeLighting;
    int location_skyColor;

    StaticShader():ShaderProgram("res/shaders/Object Shader/vert.glsl", "res/shaders/Object Shader/frag.glsl") {
        bindAttributes();
        getAllUniformLocations();
    }

    void bindAttributes() {
        ShaderProgram::bindAttribute(0, "aPos");
        ShaderProgram::bindAttribute(1, "aTexCoords");
        ShaderProgram::bindAttribute(2, "aNormals");
    }

    void getAllUniformLocations() {

        //std::cout << glGetUniformLocation(this->ID, "projectionMatrix") << std::endl;

        this->locaion_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");  // Vraca ID
        this->locaion_transformationMatrix = ShaderProgram::getUniformLocation("projectionMatrix");  // Vraca ID



        this->location_viewMatrix = ShaderProgram::getUniformLocation("shineDamper");  // Vraca ID
        this->location_viewMatrix = ShaderProgram::getUniformLocation("reflectivity");  // Vraca ID
        this->location_viewMatrix = ShaderProgram::getUniformLocation("useFakeLighting");  // Vraca ID
        this->location_viewMatrix = ShaderProgram::getUniformLocation("skyColor");  // Vraca ID

        // Get Locations for All Lights
        int i;
        for(i = 0; i < this->MAX_LIGHTS; i++) {

            std::string uniformName = "lightPosition[" + std::to_string(i) + std::string("]");
            this->location_lightPosition[i] = StaticShader::getUniformLocation(uniformName.c_str());

            uniformName = "lightColor[" + std::to_string(i) + std::string("]");
            this->location_lightColor[i] = StaticShader::getUniformLocation(uniformName.c_str());

            uniformName = "lightDistance[" + std::to_string(i) + "]";
            this->location_viewMatrix = ShaderProgram::getUniformLocation(uniformName.c_str());

        }








    }

    void loadSkyColor(float r, float g, float b) {
        ShaderProgram::setVec3("skyColor", glm::vec3(r, g, b));
    }

    void loadFakeLightingVariable(bool useFake) {
        ShaderProgram::setBool("useFakeLighting", useFake);
    }

    // Testirati mozda ne radi sa & ili * // ne radi umesto ovog se koristi u Render.cpp setMat4()
    void loadTransformationMatrix(const glm::mat4 mat) {
        ShaderProgram::loadMatrix(this->locaion_transformationMatrix, mat);
    }


    // ne radi umesto ovog se koristi u Render.cpp setMat4()
    void loadProjectionMatrix(const glm::mat4 &mat) {
        ShaderProgram::setMat4("transformationMatrix", mat);    // Load Model Matrix to its Uniform on Vertex Shader
    }


    /// Should Be in Math.hpp
    void loadViewMatrix(Camera camera) {

        glm::mat4 viewMatrix = glm::mat4(1.0f);
        viewMatrix = glm::lookAt(camera.position, camera.position + camera.cameraFront, camera.cameraUP);

        ShaderProgram::setMat4("viewMatrix", viewMatrix);

    }

    // Load Lights Data to Vertex and Fragment Shader
    void loadLight(std::vector<Light> light ) {

        // Adding Lights to the Shaders
        int i;
        for(i = 0; i < this->MAX_LIGHTS; i++) {

            if(i < light.size()) {

                std::string uniformName = "lightPosition[" + std::to_string(i) + std::string("]");
                ShaderProgram::setVec3(uniformName, light.at(i).position);

                uniformName = "lightColor[" + std::to_string(i) + std::string("]");
                ShaderProgram::setVec3(uniformName, light.at(i).color);

                uniformName = "lightDistance[" + std::to_string(i) + std::string("]");
                ShaderProgram::setVec3(uniformName, light.at(i).lightDistance);

            } else {    // Else If there is no Lights we need to Fill Arrays in Shaders

                // If there is no lights we initialize Values of Array to 0.0

                std::string uniformName = "lightPosition[" + std::to_string(i) + std::string("]");
                ShaderProgram::setVec3(uniformName, glm::vec3(0.0f, 0.0f, 0.0f));

                uniformName = "lightColor[" + std::to_string(i) + std::string("]");
                ShaderProgram::setVec3(uniformName, glm::vec3(0.0f, 0.0f, 0.0f));

                uniformName = "lightDistance[" + std::to_string(i) + std::string("]");
                ShaderProgram::setVec3(uniformName, glm::vec3(1.0f, 0.0f, 0.0f));

            }

        }


    }

    void loadShineVariables(float shineDamper, float reflectivity) {
        ShaderProgram::setFloat("shineDamper", shineDamper);
        ShaderProgram::setFloat("reflectivity", reflectivity);
    }


  private:
    char* VERTEX_FILE = "res/shaders/Object Shader/vert.glsl";
    char* FRAGMENT_FILE = "res/shaders/Object Shader/frag.glsl";

};


#endif // STATICSHADER_H
