#ifndef STACKFRAME_HPP
#define STACKFRAME_HPP
#include <vector>
#include <string>
#define MEMORY_SIZE 8

using namespace std;

class Field {
    string name;
    int memoryPosition;
    Field(string name);
};

class StackFrame {
    int framePointer;
    int stackPointer;
    vector<Field> memory;
    StackFrame();
};




#endif