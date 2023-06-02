#include "XnorGate.h"


XnorGate::XnorGate(Component* a, Component* b, std::string name) : input_1(a), input_2(b), Component(name)
{
    // symbols for visual representation of xnor gate
    symbols = { "|-----|","|XNOR-|","|-----|" };
}
XnorGate::XnorGate(std::string name) : Component(name)
{
    symbols = { "|-----|","|XNOR-|","|-----|" };
}
void XnorGate::set_input1(Component* input)
{
    input_1 = input;
}
void XnorGate::set_input2(Component* input)
{
    input_2 = input;
}
bool XnorGate::get_output()
{
    // logic for xnor gate
    bool input1 = input_1->get_output();
    bool input2 = input_2->get_output();
    return (input1 && input2) || (!input1 && !input2);
}