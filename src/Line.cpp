#include <Line.hpp>
#include <iostream>

Line::Line() {
    this->point1[0] = 0.0f;
    this->point1[1] = -0.5f;
    this->point2[0] = 0.0f;
    this->point2[1] = 0.5f;
    this->thickness = 2.0f;
    this->CalculatePixelCoords();
}

Line::Line(float x1, float y1, float x2, float y2) {
    this->point1[0] = x1;
    this->point1[1] = y1;
    this->point2[0] = x2;
    this->point2[1] = y2;
    this->thickness = 2.0f;
    this->CalculatePixelCoords();
}

Line::Line(float x1, float y1, float x2, float y2, float thickness) {
    this->point1[0] = x1;
    this->point1[1] = y1;
    this->point2[0] = x2;
    this->point2[1] = y2;
    this->thickness = thickness;
    this->CalculatePixelCoords();
}

Line::~Line() {
}

float* Line::GetPoint(int pointInd) {
    return pointInd == 0 ? this->point1 : (pointInd == 1 ? this->point2 : nullptr);
}

float* Line::GetPixelCoords(int pointInd) {
    return pointInd == 0 ? this->point1Pixel : (pointInd == 1 ? this->point2Pixel : nullptr);
}

void Line::SetPoint(int pointInd, float* coords) {
    float* point = (pointInd == 0 ? this->point1 : (pointInd == 1) ? this->point2 : nullptr);
    point[0] = coords[0];
    point[1] = coords[1];
    this->CalculatePixelCoords();
}

void Line::CalculatePixelCoords() {
    float offset = this->thickness / 50.0f;
    float slope = -(this->point1[0] - this->point2[0]) / (this->point1[1] - this->point2[1]);
    // Left
    this->point1Pixel[0] = this->point1[0] - offset;
    this->point1Pixel[1] = this->point1[1] - offset * slope;
    // Right
    this->point1Pixel[2] = this->point1[0] + offset;
    this->point1Pixel[3] = this->point1[1] + offset * slope;

    // Left
    this->point2Pixel[0] = this->point2[0] - offset;
    this->point2Pixel[1] = this->point2[1] - offset * slope;
    // Right
    this->point2Pixel[2] = this->point2[0] + offset;
    this->point2Pixel[3] = this->point2[1] + offset * slope;
}