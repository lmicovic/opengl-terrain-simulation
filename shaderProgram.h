//
//#include <stdio.h>
//#include <stdlib.h>
//
//
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/glm.hpp>
//#include <glad/glad.h>
//
//
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//
//#ifndef SHADERPROGRAM2_H
//#define SHADERPROGRAM2_H
//
//
//// Proveri mozda nije dobro definisana ova klasa: https://www.youtube.com/watch?v=4w7lNF8dnYw&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP&index=5
//
//class ShaderProgram
//{
//public:
//
//    unsigned int ID;
//    unsigned int vertexID, fragmentID;
//    // constructor generates the shader on the fly
//    // ------------------------------------------------------------------------
//    ShaderProgram(const char* vertexPath, const char* fragmentPath, char* geometryPath = NULL);
//
//    void bindAttributes();
//
//    // activate the shader
//    // ------------------------------------------------------------------------
//    void start();
//
//    void stop();
//
//    void cleanUp();
//
//
//
//    void bindAttribute(int attribute, char* variableName);
//    // utility uniform functions
//    // ------------------------------------------------------------------------
//    void setBool(const std::string &name, bool value) const;
//    // ------------------------------------------------------------------------
//    void setInt(const std::string &name, int value) const;
//    // ------------------------------------------------------------------------
//    void setFloat(const std::string &name, float value) const;
//    // ------------------------------------------------------------------------
//    void setVec2(const std::string &name, const glm::vec2 &value) const;
//    void setVec2(const std::string &name, float x, float y) const;
//    // ------------------------------------------------------------------------
//    void setVec3(const std::string &name, const glm::vec3 &value) const;
//    void setVec3(const std::string &name, float x, float y, float z) const;
//    // ------------------------------------------------------------------------
//    void setVec4(const std::string &name, const glm::vec4 &value) const;
//    void setVec4(const std::string &name, float x, float y, float z, float w);
//    // ------------------------------------------------------------------------
//    void setMat2(const std::string &name, const glm::mat2 &mat) const;
//    // ------------------------------------------------------------------------
//    void setMat3(const std::string &name, const glm::mat3 &mat) const;
//    // ------------------------------------------------------------------------
//    void setMat4(const std::string &name, const glm::mat4 &mat) const;
//
//
//private:
//    // utility function for checking shader compilation/linking errors.
//    // ------------------------------------------------------------------------
//    void checkCompileErrors(GLuint shader, std::string type);
//
//};
//
//#endif
