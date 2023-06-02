#ifndef NOT_GATE_H
#define NOT_GATE_H

#include <string>
#include "Component.h" 

class NotGate : public Component
{
public:
    Component* input_1;

    NotGate(Component* a, std::string name);
    NotGate(std::string name);
    void set_input1(Component* input);
    bool get_output() override;
};

#endif // NOT_GATE_H

