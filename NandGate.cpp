#include "NandGate.h"

NandGate::NandGate(Component* a, Component* b, std::string name) : input_1(a), input_2(b), Component(name)
{
    // symbols for visual representation of nand gate
    symbols = { "|-----|","|NAND-|","|-----|" };
}
NandGate::NandGate(std::string name) : Component(name)
{
    symbols = { "|-----|","|NAND-|","|-----|" };
}
void NandGate::set_input1(Component* input)
{
    input_1 = input;
}
void NandGate::set_input2(Component* input)
{
    input_2 = input;
}
bool NandGate::get_output()
{
    // logic for nand gate
    if (!(input_1->get_output() && input_2->get_output())) {
        return true;
    }
    else {
        return false;
    }
}