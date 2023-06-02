#ifndef NORGATE_H 
#define NORGATE_H 
#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class NorGate : public Component
{
public:
    Component* input_1;
    Component* input_2;

    NorGate(Component* a, Component* b, std::string name);

    NorGate(std::string name);

    void set_input1(Component* input);

    void set_input2(Component* input);

    bool get_output() override;
};
#endif

