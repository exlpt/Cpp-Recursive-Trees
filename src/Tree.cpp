#include <Line.hpp>
#include <Tree.hpp>
#include <iostream>
#include <math.h>

float AngleTree::angle;
float AngleTree::scaleFactor;
int AngleTree::dumpLinesInd;


AngleTree::AngleTree() {
    AngleTree::dumpLinesInd = 0;
    this->child1 = nullptr;
    this->child2 = nullptr;
}

AngleTree::AngleTree(int depth, float x, float y, float baseLength, float angle, bool direction) {
    float ang = direction ? (AngleTree::angle + angle) : (-AngleTree::angle + angle);
    float endX = x + sin(ang) * baseLength;
    float endY = y + cos(ang) * baseLength;
    this->line = new Line(x, y, endX, endY, 0.05f);

    if (depth > 0) {
        this->child1 = new AngleTree(depth - 1, endX, endY, baseLength / AngleTree::scaleFactor, ang, true);
        this->child2 = new AngleTree(depth - 1, endX, endY, baseLength / AngleTree::scaleFactor, ang, false);
    }
    else {
        this->child1 = nullptr;
        this->child2 = nullptr;
    }
}

AngleTree::AngleTree(int depth, float angle, float x, float y, float baseLength, float scaleFactor) {
    AngleTree::dumpLinesInd = 0;
    AngleTree::angle = angle;
    AngleTree::scaleFactor = scaleFactor;
    this->line = new Line(x, y, x, y + baseLength, 0.05f);

    if (depth > 0) {
        this->child1 = new AngleTree(depth - 1, x, y + baseLength, baseLength / AngleTree::scaleFactor, 0, true);
        this->child2 = new AngleTree(depth - 1, x, y + baseLength, baseLength / AngleTree::scaleFactor, 0, false);
    }
    else {
        this->child1 = nullptr;
        this->child2 = nullptr;
    }
}

AngleTree::~AngleTree() {
}

Line* AngleTree::GetLine() {
    return this->line;
}

void AngleTree::DumpLines(Line* array) {
    array[AngleTree::dumpLinesInd] = *this->line;
    AngleTree::dumpLinesInd++;

    if (this->child1 != nullptr)
        child1->DumpLines(array);
    if (this->child2 != nullptr)
        child2->DumpLines(array);
}