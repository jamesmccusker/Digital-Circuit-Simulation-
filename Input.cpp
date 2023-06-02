#include "Input.h"

Input::Input(std::string name) : Component(name)
{
    symbols = { "", "-" + name + "-", "" };
}
void Input::change_state(bool instate)
{
    // change state to iterate over all possible inputs 
    state = instate;
}
bool Input::get_output()
{
    return state;
}