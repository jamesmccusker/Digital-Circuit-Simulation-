#ifndef COMPONENT_H 
#define COMPONENT_H 
#include <string>
#include <vector>

class Component // Base Class
{
protected:
    std::vector<std::string> symbols = {};
private:
    std::string name;
public:
    int x, y;

    Component(std::string name);

    // retreive characters needed for visual ouput
    std::string get_symbol(int layer);  

    // retreives names of each component for creating wires
    std::string get_name();  
  
    // retrive output of any component and circuit
    virtual bool get_output() = 0; 
};
#endif