#include "AndGate.h"


AndGate::AndGate(Component* a, Component* b, std::string name) : input_1(a), input_2(b), Component(name)
{
    // symbols used for visual representation of and gate
    symbols = { "|-----|","|-AND-|","|-----|" }; 
}
AndGate::AndGate(std::string name) : Component(name)
{
    symbols = { "|-----|","|-AND-|","|-----|" };
}
void AndGate::set_input1(Component* input)
{
    input_1 = input;
}
void AndGate::set_input2(Component* input)
{
    input_2 = input;
}
bool AndGate::get_output()
{
    // logic for And gate
    if (input_1->get_output() && input_2->get_output()) {
        return true;
    }
    else {
        return false;
    }
}