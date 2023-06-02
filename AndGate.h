#ifndef ANDGATE_H 
#define ANDGATE_H 
#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class AndGate : public Component
{
public:
    Component* input_1;
    Component* input_2;
    // two constructers: one for user inputted circuits, other for main function circuits
    AndGate(Component* a, Component* b, std::string name);

    AndGate(std::string name);

    void set_input1(Component* input);

    void set_input2(Component* input);

    bool get_output() override;
};
#endif