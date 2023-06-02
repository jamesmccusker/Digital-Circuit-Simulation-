#include "Component.h"

Component::Component(std::string name)
{
    this->name = name;
}
std::string Component::get_symbol(int layer)
{
    return symbols[layer];
}
std::string Component::get_name()
{
    return name;
}