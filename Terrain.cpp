
#include <iostream>


#include "Terrain.hpp"

Terrain::Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack terrainTexturePack, TerrainTexture blendMap) {

    // Default Values
    this->SIZE = 800.0f;
    this->VERTEX_COUNT = 128;
    //-----------------------

    this->modelTexture = modelTexture;
    this->x = (float)gridX * this->SIZE;
    this->z = (float)gridZ * this->SIZE;
    this->rawModel = generateTerrain(loader);   // Generate Vertex Data of Terrain

    this->terrainTexturePack = terrainTexturePack;
    this->blendMap = blendMap;

}

// Generate Terrain
RawModel Terrain::generateTerrain(Loader loader) {

    // Generate Height of Map
    Height heights = Terrain::generateHeights();
    this->heights = heights;



    int count = this->VERTEX_COUNT * this->VERTEX_COUNT;

    float vertices[count * 3];
    float normals[count * 3];
    float texCoords[count * 2];
    int indices[6 * (this->VERTEX_COUNT - 1) * (this->VERTEX_COUNT - 1)];




    int vertexPointer = 0, heightPtr = 0;
    int i,j;
    for(i = 0; i < this->VERTEX_COUNT; i++) {

        for(j = 0; j < this->VERTEX_COUNT; j++) {

            float height = heights.height[j][i];

            vertices[vertexPointer*3] = (float)j/((float)this->VERTEX_COUNT - 1) * this->SIZE;
            vertices[vertexPointer*3+1] = height;
            vertices[vertexPointer*3+2] = (float)i/((float)this->VERTEX_COUNT - 1) * this->SIZE;

            glm::vec3 calNormals = Terrain::calucalateNormal(i, j, heights);
            normals[vertexPointer*3] = calNormals.x;
            normals[vertexPointer*3+1] = calNormals.y;
            normals[vertexPointer*3+2] = calNormals.z;
            texCoords[vertexPointer*2] = (float)j/((float)this->VERTEX_COUNT - 1);
            texCoords[vertexPointer*2+1] = (float)i/((float)this->VERTEX_COUNT - 1);
            vertexPointer++;

        }

    }

    // Generate Indices

    int pointer = 0;
    int gz, gx;
    for(gz = 0; gz < this->VERTEX_COUNT - 1; gz++){

        for(gx = 0; gx < VERTEX_COUNT - 1; gx++){
            int topLeft = (gz * this->VERTEX_COUNT ) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * this->VERTEX_COUNT) + gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }

    }

    // Cast Arrays to Vectors
    std::vector<float> vertices1(vertices, vertices + sizeof vertices / sizeof vertices[0]);
    std::vector<float> normals1(normals, normals + sizeof normals / sizeof normals[0]);
    std::vector<float> texCoords1(texCoords, texCoords + sizeof texCoords / sizeof texCoords[0]);
    std::vector<unsigned int> indices1(indices, indices + sizeof indices / sizeof indices[0]);


    RawModel rawModel = loader.loadToVAO(vertices1, indices1, texCoords1, normals1);
    return rawModel;

}

// Vraca visinu Terena za zadatu x,y tacku:       https://www.youtube.com/watch?v=6E2zjfzMs7c&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP&index=22
float Terrain::getHeightOfTerrain(float worldX, float worldZ, Height heights) {

    // Cast World Coordinates to Coordinates Relative to the Terrain
    float terrainX = worldX - this->x;
    float terrainZ = worldZ - this->z;

    // Calculate Size of Each Grid Square on Terrain
    // Velicina Terena / Velicina Vertex-a
    float gridSquareSize = this->SIZE / ((float)128 - 1); /// this->vertex_count mozdda ne radi

    // Find Out Witch Grid Square our X,Y Coordinate is IN
    int gridX = (int) std::floor(terrainX / gridSquareSize);
    int gridZ = (int) std::floor(terrainZ / gridSquareSize);

    // Test if This GridX, GridZ Positions are in the Terrain
    if(gridX >= 256 - 1 || gridX < 0 || gridZ >= 256 - 1 || gridZ < 0) {
        return 0.0f;   // Ako jeste onda vracamo 0.0f kao visinu.
    }

    // We Found Witch GridSquare camera is
    // Now we need to Find Where in that GridSquare camere is
    float xCoord = std::fmod(terrainX, gridSquareSize) / gridSquareSize;    // Delimo sa gridSquareSize kako bi dobili X koordinate izmedju (0,1)
    float zCoord = std::fmod(terrainZ, gridSquareSize) / gridSquareSize;    // Delimo sa gridSquareSize kako bi dobili X koordinate izmedju (0,1)

    // We found where in GridSquare camere is,
    // Now we need to find in witch Triangle out camera is,
    // because in OpenGL Every Square contain of two Triangles:   min 6:00 -https://www.youtube.com/watch?v=6E2zjfzMs7c&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP&index=22
     float res;     // Height of Terrain
     if(xCoord <= (1 - zCoord)) {
        // Upper Trinagle
        res = Math::barryCentricInterpolation(glm::vec3(0, heights.height[gridX][gridZ], 0), glm::vec3(1,
							heights.height[gridX + 1][gridZ], 0), glm::vec3(0,
							heights.height[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
     } else  {
        // Lover Trinangle
        res = Math::barryCentricInterpolation(glm::vec3(1, heights.height[gridX + 1][gridZ], 0), glm::vec3(1,
							heights.height[gridX + 1][gridZ + 1], 1), glm::vec3(0,
							heights.height[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
     }



     return res;

}

/*
    Calulate Normals for Terrain that Has Heihts
*/
glm::vec3 Terrain::calucalateNormal(int x, int z, HeightPojo heights) {

    // HeightMap Image:
    //      Height: 256
    //      Width:  256

    float heightL;
    float heightR;
    float heightD;
    float heightU;

    if(x < 0 || x >= 256 || z < 0 || z >= 256) {

        heightL = 1.0f;
        heightR = 1.0f;
        heightD = 1.0f;
        heightU = 1.0f;

        //return glm::vec3(0.0f, 1.0f, 0.0f);

    } else {

        heightL = heights.height[x-1][z];
        heightR = heights.height[x+1][z];
        heightD = heights.height[x][z-1];
        heightU = heights.height[x][z+1];

    }

    glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
    normal = glm::normalize(normal);

    return normal;


}



/*
    Split String by ",". Used to Parse HeightMap Data in: Terrain generateHeight
*/
std::vector<std::string> Terrain::removeDupWord(std::string str)
{
   std::string word = "";
   int c = 0;

   std::vector<std::string> res;

   for (auto x : str)
   {
       if (x == ',')
       {
           res.push_back(word);
           c++;
           word = "";
       }
       else
       {
           word = word + x;
       }
   }

   return res;
}

// Generate Terrain Height Values From HeightMap.
HeightPojo Terrain::generateHeights() {

    // Read File
    std::ifstream inFile;

    // Check if File is Opened
    inFile.open("heightMap.txt");   // HeightMap Genereted From HeightMap.png
    if(!inFile) {
        std::cout << "Unable to Open File" << std::endl;
        exit(1);
    }

    std::string str;    // Store Read Line from File

    int x, y;
    Height heightes;

    // Parse File and Store data to Heights
    for(x = 0; std::getline(inFile, str); x++) {


            std::vector<std::string> res = Terrain::removeDupWord(str); // Res store Splited str values by ','

            for(y = 0; y < 255; y++) {
                heightes.height[x][y] = std::atof(res.at(y).c_str());   // Cast String to Float and Store
            }
    }

    inFile.close();


    return heightes;    // Returns Array of Heights
}







