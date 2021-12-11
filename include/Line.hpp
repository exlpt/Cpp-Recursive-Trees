class Line {
public:
    Line();
    Line(float x1, float y1, float x2, float y2);
    Line(float x1, float y1, float x2, float y2, float thickness);
    ~Line();

    float* GetPoint(int pointInd);

    float* GetPixelCoords(int pointInd);

    void SetPoint(int pointInd, float* coords);

private:
    float point1[2];
    float point2[2];
    float point1Pixel[4];
    float point2Pixel[4];
    float thickness;

    void CalculatePixelCoords();
};