#include "Output.h"

Output::Output(Component* input, std::string name) : Component(name), input_1(input)
{
    symbols = { "", "", "" };
}
bool Output::get_output()
{
    return input_1->get_output();
}