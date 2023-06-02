#include "Wires.h"

Wires::Wires() : Component("")
{
    symbols = { "","","" };
}
void Wires::set_top_input(std::string input)
{
    symbols[0] = input;
}
void Wires::set_bottom_input(std::string input)
{
    symbols[2] = input;
}
void Wires::set_middle_output(std::string input)
{
    symbols[1] = input;
}
bool Wires::get_output()
{
    return false;
}