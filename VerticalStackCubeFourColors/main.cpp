#include<iostream>
#include<string>
#include<map>
#include<vector>

enum CubeIndex {
    FRONT = 0,
    BACK = 1,
    LEFT = 2,
    RIGHT = 3,
    TOP = 4,
    BOTTOM = 5
};

std::map<int,std::vector<std::string>> g_cubesStates;
std::vector<std::vector<std::string>> g_solutions;

const int CUBECOUNT = 4;

bool contain4Colors(std::string s)
{
    return (s.find('R') != std::string::npos) && (s.find('G') != std::string::npos) && (s.find('Y') != std::string::npos) && (s.find('B') != std::string::npos);
}


void extractInput(std::string input, std::string* inputValues)
{
    std::string del = ",";

    auto pos = input.find(del);
    int i = 0;

    while (pos != std::string::npos) {
        inputValues[i++] = input.substr(0, pos);

        input.erase(0, pos + del.length());

        pos = input.find(del);
    }
    
    inputValues[i] = input;
}

void rotateLeftRightCube(std::string* cube)
{
    // front back left right top bottom  front -> right   => front -> right
    // right back left front top bottom  right -> back    => front -> back
    // back right left front top bottom  back -> left     => front -> left
    // left right back front top bottom  
    //

    if (cube->length() < 5)
        return;

    // front -> right
    std::swap((*cube)[FRONT], (*cube)[RIGHT]);
    // right -> back
    std::swap((*cube)[FRONT], (*cube)[BACK]);
    // back -> left
    std::swap((*cube)[FRONT], (*cube)[LEFT]);
}

void rotateVerticalFrontBackCube(std::string* cube)
{
    // front back left right top bottom  front -> bottom   => front -> bottom
    // bottom back left right top front  bottom -> back    => front -> back
    // back bottom left right top front  back -> top       => front -> top
    // top bottom left right back front
    //


    if (cube->length() < 5)
        return;

    // top -> front
    std::swap((*cube)[FRONT], (*cube)[BOTTOM]);
    // front -> bottom
    std::swap((*cube)[FRONT], (*cube)[BACK]);
    // bottom -> back
    std::swap((*cube)[FRONT], (*cube)[TOP]);

}

void rotateVerticalLeftRightmCube(std::string* cube)
{
    // front back left right top bottom  left -> bottom   => left -> bottom
    // front back bottom right top left  bottom -> right    => left -> right
    // front back right bottom top left  right-> top       => left -> top
    // front back top bottom right left
    //


    if (cube->length() < 5)
        return;

    // top -> front
    std::swap((*cube)[LEFT], (*cube)[BOTTOM]);
    // front -> bottom
    std::swap((*cube)[LEFT], (*cube)[RIGHT]);
    // bottom -> back
    std::swap((*cube)[LEFT], (*cube)[TOP]);

}

bool checkVerticalStackColorsSide(std::string* verticalStack, CubeIndex side)
{
    std::string stackSide = "";

    for (int i = 0; i < CUBECOUNT; i++) {
        stackSide += verticalStack[i][side];
    }

    return contain4Colors(stackSide);
}

bool checkVerticalStackColors(std::string* verticalStack)
{
    bool result = checkVerticalStackColorsSide(verticalStack, FRONT);
    if (!result)
        return result;
    
    result = checkVerticalStackColorsSide(verticalStack, LEFT);
    if (!result)
        return result;
    
    result = checkVerticalStackColorsSide(verticalStack, RIGHT);
    if (!result)
        return result;
    
    result = checkVerticalStackColorsSide(verticalStack, BACK);
    if (!result)
        return result;

    return result;
}

void checkEveryCombination(int cube1IndexOnStack, int cube2IndexOnStack, int cube3IndexOnStack, int cube4IndexOnStack)
{
    bool isAllColorsOnSide = false;
    std::string verticalStack[4];

    for (int cube1State = 0; cube1State < g_cubesStates[cube1IndexOnStack].size(); cube1State++)
    {
        for (int cube2State = 0; cube2State < g_cubesStates[cube2IndexOnStack].size(); cube2State++)
        {
            for (int cube3State = 0; cube3State < g_cubesStates[cube3IndexOnStack].size(); cube3State++)
            {
                for (int cube4State = 0; cube4State < g_cubesStates[cube4IndexOnStack].size(); cube4State++) 
                {
                    verticalStack[0] = g_cubesStates[cube1IndexOnStack][cube1State];
                    verticalStack[1] = g_cubesStates[cube2IndexOnStack][cube2State];
                    verticalStack[2] = g_cubesStates[cube3IndexOnStack][cube3State];
                    verticalStack[3] = g_cubesStates[cube4IndexOnStack][cube4State];

                    isAllColorsOnSide = checkVerticalStackColors(verticalStack);

                    if (isAllColorsOnSide)
                    {
                        int n = sizeof(verticalStack) / sizeof(std::string);
                        std::vector<std::string> vecVerticalStack(verticalStack, verticalStack + n);
                        g_solutions.push_back(vecVerticalStack);
                    }
                }
            }
        }
    }
}

void generateEveryCombination(std::string* verticalStack)
{
    for (int cubeIndex = 0; cubeIndex < CUBECOUNT; cubeIndex++)
    {
        int i = 0, j = 0, k=0;
        for (i = 0; i < 4; i++)
        {
            if (std::count(g_cubesStates[cubeIndex].begin(), g_cubesStates[cubeIndex].end(), verticalStack[cubeIndex]) <= 0)
            {
                g_cubesStates[cubeIndex].push_back(verticalStack[cubeIndex]);
            }
            rotateLeftRightCube(&verticalStack[cubeIndex]);
        }
        for (j = 0; j < 4; j++) {
            if (std::count(g_cubesStates[cubeIndex].begin(), g_cubesStates[cubeIndex].end(), verticalStack[cubeIndex]) <= 0)
            {
                g_cubesStates[cubeIndex].push_back(verticalStack[cubeIndex]);
            }
            rotateVerticalFrontBackCube(&verticalStack[cubeIndex]);
        }
        for (k = 0; k < 4; k++) {
            if (std::count(g_cubesStates[cubeIndex].begin(), g_cubesStates[cubeIndex].end(), verticalStack[cubeIndex]) <= 0)
            {
                g_cubesStates[cubeIndex].push_back(verticalStack[cubeIndex]);
            }
            rotateVerticalLeftRightmCube(&verticalStack[cubeIndex]);
        }
    }
}

int main(int argc, char* args[])
{
    
    std::string input;
    std::cin >> input;
    std::string intputValues[CUBECOUNT];

    extractInput(input, intputValues);
    

    generateEveryCombination(intputValues);
    checkEveryCombination(0,1,2,3);
    int end = 3;

    return 0;
}
