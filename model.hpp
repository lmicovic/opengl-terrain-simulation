#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.hpp"
#include "staticShader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "TextureModel.h"

/// Assimp
using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);



//=======================================================
/*
    Model - Represent Model Object Loaded from File.
*/
//=======================================================
class Model
{
public:
    /*  Model Data */
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    // Vertex Data - ovde se nalaze Potrebni podaci za nas Model
    vector<float> vertices;             // Positions
    vector<float> textureCoords;        // Texture Coordinates
    vector<float> normals;              // Normals
    vector<unsigned int> indices;

    /*  Functions   */

    Model();

    // constructor, expects a filepath to a 3D model.
    Model(string const &path, bool gamma);

    // draws the model, and thus all its meshes
    void Draw(StaticShader shader);

private:
    /*  Functions   */
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const &path);

    void processModel();
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif
