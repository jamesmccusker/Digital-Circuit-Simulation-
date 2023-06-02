#ifndef OUTPUT_H
#define OUTPUT_H
#include "Component.h"
#include <iostream>
#include <vector>
#include <string>

class Output : public Component
{
private:
    bool state;
public:
    Component* input_1;

    Output(Component* input, std::string name);

    bool get_output() override;
};
#endif
