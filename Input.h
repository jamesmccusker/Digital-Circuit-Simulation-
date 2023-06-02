#ifndef INPUT_H
#define INPUT_H
#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class Input : public Component
{
private:
    bool state;
public:

    Input(std::string name);
   
    void change_state(bool instate);
   
    bool get_output() override;
};
#endif

