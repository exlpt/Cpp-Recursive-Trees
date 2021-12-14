#include <Line.hpp>
#include <math.h>
#include <iostream>

Line::Line() {
    this->point1[0] = 0.0f;
    this->point1[1] = -0.5f;
    this->point2[0] = 0.0f;
    this->point2[1] = 0.5f;
    this->thickness = 2;
}

Line::Line(float x1, float y1, float x2, float y2) {
    this->point1[0] = x1;
    this->point1[1] = y1;
    this->point2[0] = x2;
    this->point2[1] = y2;
    this->thickness = 2;
}

Line::Line(float x1, float y1, float x2, float y2, int thickness) {
    this->point1[0] = x1;
    this->point1[1] = y1;
    this->point2[0] = x2;
    this->point2[1] = y2;
    this->thickness = thickness;
}

Line::~Line() {
}

float* Line::GetPoint(int pointInd) {
    return pointInd == 0 ? this->point1 : (pointInd == 1 ? this->point2 : nullptr);
}

void Line::SetPoint(int pointInd, float* coords) {
    float* point = (pointInd == 0 ? this->point1 : (pointInd == 1) ? this->point2 : nullptr);
    point[0] = coords[0];
    point[1] = coords[1];
}