#ifndef WIRES_H
#define WIRES_H 
#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class Wires : public Component
{
public:
    Wires();

    // setting inputs and outputs for gates
    void set_top_input(std::string input);

    void set_bottom_input(std::string input);

    void set_middle_output(std::string input);

    bool get_output() override;
};
#endif