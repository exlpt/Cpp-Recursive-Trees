class AngleTree {
public:
    AngleTree();
    AngleTree(int depth, float angle, float x, float y, float baseLength, float scaleFactor);
    ~AngleTree();

    Line* GetLine();
    void DumpLines(Line* array);

private:
    AngleTree(int depth, float x, float y, float baseLength, float angle, bool direction);

    AngleTree* child1;
    AngleTree* child2;
    Line* line;
    static float angle;
    static float scaleFactor;
    static int dumpLinesInd;
};