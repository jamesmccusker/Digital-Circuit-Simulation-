#ifndef XORGATE_H 
#define XORGATE_H 
#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class XorGate : public Component
{
public:
    Component* input_1;
    Component* input_2;

    XorGate(Component* a, Component* b, std::string name);

    XorGate(std::string name);

    void set_input1(Component* input);

    void set_input2(Component* input);

    bool get_output() override;
};
#endif
