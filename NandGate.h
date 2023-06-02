#ifndef NANDGATE_H 
#define NANDGATE_H 
#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class NandGate : public Component
{
public:
    Component* input_1;
    Component* input_2;

    NandGate(Component* a, Component* b, std::string name);

    NandGate(std::string name);

    void set_input1(Component* input);

    void set_input2(Component* input);

    bool get_output() override;
};
#endif