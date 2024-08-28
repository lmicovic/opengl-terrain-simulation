
#ifndef RAWMODEL_H
#define RAWMODEL_H

// Represents Model
class RawModel {

public:
    int vaoID;          // ID of RawModel Attributes
    int vertexCount;    // Number of Vertex used in Draw Method

    RawModel();
    RawModel(int vaoID, int vertexCount);




};



#endif // RAWMODEL_H
