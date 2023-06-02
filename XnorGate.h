#ifndef XNORGATE_H 
#define XNORGATE_H 
#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class XnorGate : public Component
{
public:
    Component* input_1;
    Component* input_2;

    XnorGate(Component* a, Component* b, std::string name);

    XnorGate(std::string name);

    void set_input1(Component* input);

    void set_input2(Component* input);

    bool get_output() override;
};
#endif
