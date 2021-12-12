#include <iostream>
#include <glad.h>
#include <Line.hpp>
#include <Util.hpp>

void SetVertexArray(Line* array, int length, GLfloat* vertexArray) {
    for (int i = 0; i < length; i++) {
        // Get line coords
        float* point1Coords = array[i].GetPixelCoords(0);
        float* point2Coords = array[i].GetPixelCoords(1);

        // Put coords into vertex array
        int indexOffset = i * 18;

        // 1st tri
        vertexArray[indexOffset + 0] = point1Coords[0];
        vertexArray[indexOffset + 1] = point1Coords[1];
        vertexArray[indexOffset + 2] = 0.0f;

        vertexArray[indexOffset + 3] = point1Coords[2];
        vertexArray[indexOffset + 4] = point1Coords[3];
        vertexArray[indexOffset + 5] = 0.0f;

        vertexArray[indexOffset + 6] = point2Coords[0];
        vertexArray[indexOffset + 7] = point2Coords[1];
        vertexArray[indexOffset + 8] = 0.0f;

        // 2nd tri
        vertexArray[indexOffset + 9] = point2Coords[2];
        vertexArray[indexOffset + 10] = point2Coords[3];
        vertexArray[indexOffset + 11] = 0.0f;

        vertexArray[indexOffset + 12] = point1Coords[2];
        vertexArray[indexOffset + 13] = point1Coords[3];
        vertexArray[indexOffset + 14] = 0.0f;

        vertexArray[indexOffset + 15] = point2Coords[0];
        vertexArray[indexOffset + 16] = point2Coords[1];
        vertexArray[indexOffset + 17] = 0.0f;
    }
}