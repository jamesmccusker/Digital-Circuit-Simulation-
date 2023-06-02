#include "XorGate.h"


XorGate::XorGate(Component* a, Component* b, std::string name) : input_1(a), input_2(b), Component(name)
{
    // symbols for visual representation of xor gate
    symbols = { "|-----|","|-XOR-|","|-----|" };
}
XorGate::XorGate(std::string name) : Component(name)
{
    symbols = { "|-----|","|-XOR-|","|-----|" };
}
void XorGate::set_input1(Component* input)
{
    input_1 = input;
}
void XorGate::set_input2(Component* input)
{
    input_2 = input;
}
bool XorGate::get_output()
{
    // logic for xor gate
    bool input1 = input_1->get_output();
    bool input2 = input_2->get_output();
    return (input1 || input2) && !(input1 && input2);
}
