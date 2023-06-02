#include "NorGate.h"


NorGate::NorGate(Component* a, Component* b, std::string name) : input_1(a), input_2(b), Component(name)
{
    // symbols for visual representation of nor gate
    symbols = { "|-----|","|-NOR-|","|-----|" };
}
NorGate::NorGate(std::string name) : Component(name)
{
    symbols = { "|-----|","|-NOR-|","|-----|" };
}
void NorGate::set_input1(Component* input)
{
    input_1 = input;
}
void NorGate::set_input2(Component* input)
{
    input_2 = input;
}
bool NorGate::get_output()
{
    // logic for nor gate
    if (input_1->get_output() && input_2->get_output()) {
        return true;
    }
    else {
        return false;
    }
}