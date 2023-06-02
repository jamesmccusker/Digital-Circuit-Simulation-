#include "OrGate.h"

OrGate::OrGate(Component* a, Component* b, std::string name) : input_1(a), input_2(b), Component(name)
{
    // symbols for visual representation of or gate
    symbols = { "|-----|","|-OR--|","|-----|" };
}
OrGate::OrGate(std::string name) : Component(name)
{
    symbols = { "|-----|","|-OR--|","|-----|" };
}
void OrGate::set_input1(Component* input)
{
    input_1 = input;
}
void OrGate::set_input2(Component* input)
{
    input_2 = input;
}
bool OrGate::get_output()
{
    // logic for or gate
    if (input_1->get_output() || input_2->get_output()) {
        return true;
    }
    else {
        return false;
    }
}