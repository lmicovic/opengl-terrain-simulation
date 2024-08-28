#ifndef MATH_H
#define MATH_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>



class Math {

public:

    Math() {

    }

    glm::mat4 createTransformationMatrix(glm::vec3 translation, float rotateX, float rotateY, float rotateZ, float scale) {

        // Make Indentity Matrix - sve jedinice
        glm::mat4 mat = glm::mat4(1.0f);

        // Translation
        mat = glm::translate(mat, translation);

        // Rotation
        mat = glm::rotate(mat, glm::radians(rotateX), glm::vec3(1.0f, 0.0f, 0.0f));  // Rotate on the X axis
        mat = glm::rotate(mat, glm::radians(rotateY), glm::vec3(0.0f, 1.0f, 0.0f));  // Rotate on the Y axi
        mat = glm::rotate(mat, glm::radians(rotateZ), glm::vec3(0.0f, 0.0f, 1.0f));  // Rotate on the Z

        // Scale - uniform scale, same in X, Y and Z axis
        mat = glm::scale(mat, glm::vec3(scale, scale, scale));


        return mat;

    }


    /*
        Barry Centric Interpolation:

            We use this to find hight of Terrain Position Based on Cameras
            X,Y Position

            Param: p1, p2, p3, pos

                    p1, p2, p3 - represents 3 points in Triangle
                    pos - represent X,Y coordinate of Camera

    */
    static float barryCentricInterpolation(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {

        float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;

		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
    }








};


#endif // MATH_H
