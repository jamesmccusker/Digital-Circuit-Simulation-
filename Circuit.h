#ifndef CIRCUIT_H
#define CIRCUIT_H
#include "Component.h"
#include "Input.h"
#include "Output.h"
#include <iostream>
#include <vector>
#include <string>
#include "component.h"
#include "input.h"
#include "output.h"
#include "AndGate.h"
#include "NandGate.h"
#include "OrGate.h"
#include "NorGate.h"
#include "XorGate.h"
#include "XnorGate.h"
#include "NotGate.h"

class Circuit
{
private:
    std::vector<Input*> inputs; // Store pointers to circuit_input objects
    std::vector<Output*> outputs; // Store pointers to Circuit_output objects
    std::vector<Component*> gates;
    int cols = 50;
    int rows = 50;
    std::vector<std::vector<Component*>> locations;

public:
    int num_layers;

    Circuit();
    
    void enter_circuit_inputs(std::vector<Input*> input);
   
    void enter_circuit_outputs(std::vector<Output*> output);
  
    void enter_circuit_components(std::vector<Component*> input);

    int find_layers(Component* current_step, int layer);
  
    void set_location(Component* gate, int x, int y);
    
    void align_component(Component* current_gate, int current_layer);
    
    void fill_in_wires(Component* current_component);

    void print_circuit();
    
    void print_truth_table();
};
#endif