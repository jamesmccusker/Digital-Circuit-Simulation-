#ifndef ORGATE_H 
#define ORGATE_H 
#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class OrGate : public Component
{
public:
    Component* input_1;
    Component* input_2;

    OrGate(Component* a, Component* b, std::string name);

    OrGate(std::string name);

    void set_input1(Component* input);

    void set_input2(Component* input);

    bool get_output() override;
};
#endif

