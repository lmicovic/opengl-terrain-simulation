


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "loader.h"
#include "stb_image.h"


/*
    Loading 3D Model in GPU Memmory.
*/


Loader::Loader() {

    this->vbos = NULL;
    this->vaos = NULL;
    this->textures = NULL;

}

/*
   Create VBO, VAO and EBO from Vertices

        positions:      Vertives Data.
        sizeOfData:     size of Vertices Array Bytes. Number of Elements in Vertives Array is -> sizeof(sizeOfData) / sizeof(position[0])
        indices:        Data for EBO Buffer.
        sizeOfIndices:  size of Indices Array in bytes. Number of Elements is ->   sizeof(sizeOfIndices) / sizeof(indices[0]);
        sizeOfTextureCoords:  size of TextureCord Arr in bytes. Number of Elements is ->   sizeof(sizeOfIndices) / sizeof(textureCoords[0]);

*/
RawModel Loader::loadToVAO(std::vector<float> positions, std::vector<unsigned int> indices, std::vector<float> textureCoords, std::vector<float> normals) {

    int vaoID = Loader::createVAO();        // Create VAO and Return its ID
    Loader::bindIndicesBuffer(indices);     // Bind Indices to Buffer and Send to Vertex Shader
    Loader::storeDataInAttributeList(0, 3, positions);  // Send positions data to Vertex Shader
    Loader::storeDataInAttributeList(1, 2, textureCoords);  // Send Texture Coordinates to Vertex Shader
    Loader::storeDataInAttributeList(2, 3, normals);        // Send Normals to Vertex Shader


    unbindVAO();    // Unbind Current VAO



    RawModel model = RawModel(vaoID, indices.size());


    return model;

}

/* Ucitava Texturu iz Zadatok Fajla.

        filePath:   putanja do fajla
        returns:    TextureID
*/
unsigned int Loader::loadTexture(const char* filePath, bool okreni) {

    // Generisanje Texture Objekta na GPU
	unsigned int textureID;
	glGenTextures(1, &textureID);

	// Povezujemo Ucitanu Texturu
	glBindTexture(GL_TEXTURE_2D, textureID);




	// Ucitavanje Image Data
	int width, height, numberChannel;
	unsigned char *data = stbi_load(filePath, &width, &height, &numberChannel, 0);

    if(okreni == false) {
        stbi_set_flip_vertically_on_load(false);
    }



	if(data) {


        // Ako Slika ima RGB kanal
        if(numberChannel == 3) {
            // Generisemo Texturu od ucitanih Image Data
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        // Ako slika ima 4 Kanala RGBA
        else if(numberChannel == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

	} else {

		printf("Error Loading Image\n");
		return 0;
	}

	// Setujemo Parametre Texture za Wrap i Filtering za Trenutno Ucitani Texture Objekat
	// GL Repeat zato sto koristimo Textrure za Mapu koja treba da se ponavlja
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);					// Podesavanje Wrapping za S Osu (x)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);					// Podesavanje Wrapping za T Osu (y)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);				// Podesavanje Filtering ako se ucitana Slika smanjuje
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);				// Podesavanje Filtering ako se Slika povecava


	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

    this->textures = addToList(this->textures, textureID);

    return textureID;

}

/*
    Load Skybox Texture.

        Parameters:     filePaths - Paths of all CubeMap Images
        Returns:        Vector Of Cube Map Texture Data(width, height, data(Pixels))

*/
std::vector<TextureData> Loader::decodeTextureFile(std::vector<std::string> filePaths) {

    unsigned int textureID;
    glGenTextures(1, &textureID);   // Generate Texuter Buffer and set ID in TextrureID

    std::vector<TextureData> texturesData;  // Save Texture data


    // Prolazimo kroz sve slike Cube Mape i dodajemo
    int width, height, componentsNum, i;
    for(i = 0; i < filePaths.size(); i++) {

        unsigned char* data = stbi_load(filePaths[i].c_str(), &width, &height, &componentsNum, 0);  // Load Pixels from FilePath
        if(data) {

            // Bind Image
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);


        } else {
            std::cout << "CubeMap texture Faild to Load: " << filePaths[i] << std::endl;
            stbi_image_free(data);
            exit(1);
        }

        texturesData.push_back(TextureData(textureID, width, height, data));    // Dodajemo iscitane vrednosti iz Teksture u Texture Data
        stbi_image_free(data);


    }

    // Podesavamo Parametre kako ce da se ponasa Textura
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Kada se slika Smanjuje da se koristi Linearna Interpolazija
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Kada se slika Uvecava da se koristi Linearna Interpolacija
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // Clamp To Edge ako koristimo vece Koorinate od 1 onda da se uzme piksel na 1.0
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  // Clamp To Edge ako koristimo vece Koorinate od 1 onda da se uzme piksel na 1.0
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  // Clamp To Edge ako koristimo vece Koorinate od 1 onda da se uzme piksel na 1.0


    return texturesData;    // Vraca niz




}

/*
    Create Vertex Array Buffer (VAO)

        returns: vaoID

*/
GLuint Loader::createVAO() {

    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);

    this->vaos = addToList(this->vaos, vaoID);

    glBindVertexArray(vaoID);

    return vaoID;

}

/*
    Store Data in GPU.

        Parameters:     attributeNumber -   broj lokacije na koju se salju podaci u Vertex Shaderu
                        coordinateSize  -   broj koordinata koje koriste podaci (2,3) - (2D, 3D)
                        data            -   podaci
*/
void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float> data) {

    GLuint vboID;
    glGenBuffers(1, &vboID);

    this->vbos = addToList(this->vbos, vboID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    // storeDataInFloatBuffer();



    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0,  (void*) 0);



    glBindBuffer(GL_ARRAY_BUFFER, 0);

}



/* Store Data in Element Buffer Array

        sizeOfData:   number of Elements in indices[] array


*/
void Loader::bindIndicesBuffer( std::vector<unsigned int> indices) {

    unsigned int vboID;
    glGenBuffers(1, &vboID);
    this->vbos = addToList(this->vbos, vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


}





// Clean All Data from VBOs and VAOs Lists
void Loader::cleanUp() {

    // Delete All VAOs
    int i;
    for(i = 0; i < sizeOfList(this->vaos); i++) {
        unsigned int vao = getNode(this->vaos, i);
        glDeleteVertexArrays(1, &vao);

    }

    // Delete All VBOs
    for(i = 0; i < sizeOfList(this->vbos); i++) {
        unsigned int v = getNode(this->vbos, i);
        glDeleteBuffers(1, &v);

    }

    // Delete All Textures
    for(i = 0; i < sizeOfList(this->textures); i++) {
        unsigned int texture = getNode(this->textures, i);
        glDeleteTextures(1, &texture);

    }

    deleteList(this->vaos);
    deleteList(this->vbos);

}

void Loader::unbindVAO() {

    glBindVertexArray(0);

}
