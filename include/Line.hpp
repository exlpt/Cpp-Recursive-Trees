#pragma once

class Line {
public:
    Line();
    Line(float x1, float y1, float x2, float y2);
    Line(float x1, float y1, float x2, float y2, int thickness);
    ~Line();

    float* GetPoint(int pointInd);
    void SetPoint(int pointInd, float* coords);

private:
    float point1[2];
    float point2[2];
    int thickness;
};