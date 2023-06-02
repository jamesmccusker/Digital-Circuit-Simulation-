#include "NotGate.h"

NotGate::NotGate(Component* a, std::string name) : input_1(a), Component(name)
{
    // symbols for visual representation of not gate
    symbols = { "|-----|","|-NOT-|","|-----|" };
}

NotGate::NotGate(std::string name) : Component(name)
{
    symbols = { "|-----|","|-NOT-|","|-----|" };
}
void NotGate::set_input1(Component* input)
{
    input_1 = input;
}

bool NotGate::get_output()
{
    // logic for not gate
    return !input_1->get_output();
}

