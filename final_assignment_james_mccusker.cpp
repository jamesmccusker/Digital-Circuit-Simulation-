// James McCusker 
// April-May 2023
// Final coding project - Smulating Dgital Circuits


#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <memory>

// Header files
#include "Component.h"
#include "Wires.h"
#include "AndGate.h"
#include "NandGate.h"
#include "XorGate.h"
#include "XnorGate.h"
#include "OrGate.h"
#include "NorGate.h"
#include "Input.h"
#include "Output.h"
#include "Circuit.h"
#include "NotGate.h"
#include "DigitalOutput.h"

int main()
{
    // Demonstrating truth table for a component
    Circuit circuit;

    Input* input_1_ptr = new Input("in 1");
    Input* input_2_ptr = new Input("in 2");

    AndGate and_gate(input_1_ptr, input_2_ptr, "& 1");
    Component* and_gate_ptr = &and_gate;

    Output* out_ptr = new Output(and_gate_ptr, "out");

    std::vector<Input*> input = { input_1_ptr, input_2_ptr };
    std::vector<Output*> output = { out_ptr }; 

    std::cout << "And Gate Truth Table: \n\n";
    circuit.enter_circuit_inputs(input);
    circuit.enter_circuit_outputs(output);
    circuit.print_truth_table();

    //Building a simple circuit
    Circuit circuit_a;

    Input* input_1a_ptr = new Input("in 1");
    Input* input_2a_ptr = new Input("in 2");
    Input* input_3a_ptr = new Input("in 3");
    Input* input_4a_ptr = new Input("in 4");
    Input* input_5a_ptr = new Input("in 5");
    Input* input_6a_ptr = new Input("in 6");

    // First layer

    OrGate or_gate_1(input_1a_ptr, input_2a_ptr, "or 1");
    Component* or_gate_ptr = &or_gate_1;

    NandGate nand_gate_1(input_3a_ptr, input_4a_ptr, "N& 1");
    Component* nand_gate_ptr = &nand_gate_1;

    AndGate and_gate_1(input_5a_ptr, input_6a_ptr, "& 1");
    Component* and_gate_ptr_1 = &and_gate_1;

    // Second layer

    XorGate xor_gate_1(nand_gate_ptr, or_gate_ptr, "Xor 1");
    Component* xor_gate_ptr_1 = &xor_gate_1;

    NotGate not_gate_5(and_gate_ptr_1, "not 5");
    Component* not_gate_ptr_5 = &not_gate_5;

    // Third layer

    NorGate or_gate_4(xor_gate_ptr_1, not_gate_ptr_5, "Nor 1");
    Component* or_gate_ptr_4 = &or_gate_4;

    // Fourth Layer 

    XnorGate xnor_gate_1(or_gate_ptr_4, input_4a_ptr, "Xnor1");
    Component* xnor_gate_ptr_1 = &xnor_gate_1;

    Output* out_ptr_a = new Output(xnor_gate_ptr_1, "out");

    std::vector<Input*> inputs = { input_1a_ptr, input_2a_ptr, input_3a_ptr, input_4a_ptr, input_5a_ptr, input_6a_ptr };
    std::vector<Output*> outputs = { out_ptr_a }; // Store pointers to Circuit_output objects
    std::vector<Component*> gates = { };

    std::cout << "Simple circuit: Diagram and truth table:\n\n";
    circuit_a.enter_circuit_inputs(inputs);
    circuit_a.enter_circuit_outputs(outputs);
    circuit_a.enter_circuit_components(gates);
    circuit_a.num_layers = circuit.find_layers(out_ptr_a, 0);
    circuit_a.align_component(out_ptr_a, 0);
    circuit_a.fill_in_wires(out_ptr_a);
    circuit_a.print_circuit();
    circuit_a.print_truth_table();

    // User circuit
    Circuit user_circuit;

    std::vector<Component*> user_gates;
    std::vector<Input*> user_inputs;
    std::vector<Output*> user_outputs;

    int num_inputs = 1;
    int num_and_gates = 1;
    int num_nand_gates = 1;
    int num_or_gates = 1;
    int num_nor_gates = 1;
    int num_xor_gates = 1;
    int num_xnor_gates = 1;
    int  num_gates;

    std::cout << "Enter the number of gates in the circuit: ";
    //  while loop to check for positive integer
    while (!(std::cin >> num_gates) || num_gates <= 0 || std::cin.peek() != '\n' || fmod(num_gates, 1) != 0) { 
        std::cout << "Invalid input. Please enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << std::endl;

    for (int i = 0; i < num_gates; i++) {

        int choice;
        std::cout << "Enter the type of gate for Gate " << i + 1 << ": (1) AND, (2) NAND, (3) OR, (4) NOR, (5) XOR, (6) XNOR: ";

        //  while loop to check for positive integer less than or equal to 7

        while (!(std::cin >> choice) || choice <= 0 || choice >= 7 || std::cin.peek() != '\n' || fmod(choice, 1) != 0) { 
            std::cout << "Invalid input. Please enter a positive integer less than 7: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        // choice of gates
        if (choice == 1) {
            std::cout << "You entered AND.\n";
            AndGate* and_gate_ptr = new AndGate("& " + std::to_string(num_and_gates) + " -");
            num_and_gates++;
            user_gates.push_back(and_gate_ptr);
        }
        else if (choice == 2) {
            std::cout << "You entered NAND.\n";
            NandGate* nand_gate_ptr = new NandGate("N& " + std::to_string(num_nand_gates) + "-");
            num_nand_gates++;
            user_gates.push_back(nand_gate_ptr);
        }
        else if (choice == 3) {
            std::cout << "You entered OR.\n";
            OrGate* or_gate_ptr = new OrGate("OR " + std::to_string(num_or_gates) + "-");
            num_or_gates++;
            user_gates.push_back(or_gate_ptr);
        }
        else if (choice == 4) {
            std::cout << "You entered NOR.\n";
            NorGate* nor_gate_ptr = new NorGate("NOR " + std::to_string(num_nor_gates));
            num_nor_gates++;
            user_gates.push_back(nor_gate_ptr);
        }
        else if (choice == 5) {
            std::cout << "You entered XOR.\n";
            XorGate* xor_gate_ptr = new XorGate("XOR " + std::to_string(num_xor_gates));
            num_xor_gates++;
            user_gates.push_back(xor_gate_ptr);
        }
        else if (choice == 6) {
            std::cout << "You entered XNOR.\n";
            XnorGate* xnor_gate_ptr = new XnorGate("XNOR" + std::to_string(num_xnor_gates));
            num_xnor_gates++;
            user_gates.push_back(xnor_gate_ptr);
        }
    }
    std::cout << std::endl;
    
    // finding the output gate of the circuit
    int output_gate_index;
    std::cout << "Which gate is the output of the circuit?" << std::endl;
    std::cout << "(Enter the index of the gate, 1-" << num_gates << "): ";
    while (!(std::cin >> output_gate_index) || output_gate_index < 1 || output_gate_index > num_gates || std::cin.peek() != '\n') {
        std::cout << "Invalid input. Please enter a positive integer between 1 and " << num_gates << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (output_gate_index >= 1 && output_gate_index <= user_gates.size()) {
        Output* out_ptr = new Output(user_gates[output_gate_index - 1], "out");
        user_outputs.push_back(out_ptr);
    }
    std::cout << std::endl;

    // retreiving inputs and wiring outputs for all gates
    std::vector<bool> used_outputs(num_gates, false);

    for (int i = 0; i < user_gates.size(); i++) {
        int input1;
        int input2;
        std::cout << "What is input 1 for gate " << i + 1 << ", if it is a circuit input enter 0: ";
        while (!(std::cin >> input1) || input1 < 0 || input1 > num_gates || input1 == i + 1 || std::cin.peek() != '\n') {
            std::cout << "Invalid input. Please enter a positive integer from 0 to " << num_gates << ", not inlcuding " << i + 1 << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "what is input 2 for gate " << i + 1 << ", if it is a circuit input enter 0: ";
        while (!(std::cin >> input2) || input2 < 0 || input2 > num_gates || input2 == i + 1 || std::cin.peek() != '\n') {
            std::cout << "Invalid input. Please enter a positive integer from 0 to " << num_gates << ", not inlcuding " << i + 1 << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << std::endl;

        //check if the inputs for gates has been used twice
        if (input1 != 0) {
            if (used_outputs[input1 - 1]) {
                std::cout << "The output of gate " << input1 << " can only be used once. Please use a different gate or circuit input." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                i--;
                continue;
            }
            else {
                used_outputs[input1 - 1] = true;
            }
        }
        if (input2 != 0) {
            if (used_outputs[input2 - 1]) {
                std::cout << "The output of gate " << input2 << " can only be used once. Please use a different gate or circuit input." << std::endl;
                i--;
                continue;
            }
            else {
                used_outputs[input2 - 1] = true;
            }
        }
        if (dynamic_cast<AndGate*>(user_gates[i])) {

            AndGate* and_ptr = dynamic_cast<AndGate*>(user_gates[i]);
            //set input 1 
            if (input1 == 0)
            {
                Input* input1_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                user_inputs.push_back(input1_ptr);
                and_ptr->set_input1(input1_ptr);
            }
            else {
                and_ptr->set_input1(user_gates[input1 - 1]);
            }
            //set input 2
            if (input2 == 0) {
                Input* input2_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                num_inputs++;
                user_inputs.push_back(input2_ptr);
                and_ptr->set_input2(input2_ptr);
            }
            else {
                and_ptr->set_input2(user_gates[input2 - 1]);
            }
        }
        if (dynamic_cast<NandGate*>(user_gates[i])) {
            NandGate* nand_ptr = dynamic_cast<NandGate*>(user_gates[i]);
            //set input 1 
            if (input1 == 0) {
                Input* input1n_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                user_inputs.push_back(input1n_ptr);
                nand_ptr->set_input1(input1n_ptr);
            }
            else {
                nand_ptr->set_input1(user_gates[input1 - 1]);
            }
            //set input 2
            if (input2 == 0) {
                Input* input2n_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                num_inputs++;
                user_inputs.push_back(input2n_ptr);
                nand_ptr->set_input2(input2n_ptr);
            }
            else {
                nand_ptr->set_input2(user_gates[input2 - 1]);
            }
        }
        if (dynamic_cast<OrGate*>(user_gates[i])) {
            OrGate* or_ptr = dynamic_cast<OrGate*>(user_gates[i]);
            //set input 1 
            if (input1 == 0) {
                Input* input1_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                user_inputs.push_back(input1_ptr);
                or_ptr->set_input1(input1_ptr);

            }
            else {
                or_ptr->set_input1(user_gates[input1 - 1]);
            }
            //set input 2
            if (input2 == 0) {
                Input* input2_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                num_inputs++;
                user_inputs.push_back(input2_ptr);
                or_ptr->set_input2(input2_ptr);
            }
            else {
                or_ptr->set_input2(user_gates[input2 - 1]);
            }
        }
        if (dynamic_cast<NorGate*>(user_gates[i])) {
            NorGate* nor_ptr = dynamic_cast<NorGate*>(user_gates[i]);
            //set input 1 
            if (input1 == 0) {
                Input* input1_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                user_inputs.push_back(input1_ptr);
                nor_ptr->set_input1(input1_ptr);

            }
            else {
                nor_ptr->set_input1(user_gates[input1 - 1]);
            }
            //set input 2
            if (input2 == 0) {
                Input* input2_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                num_inputs++;
                user_inputs.push_back(input2_ptr);
                nor_ptr->set_input2(input2_ptr);
            }
            else {
                nor_ptr->set_input2(user_gates[input2 - 1]);
            }
        }
        if (dynamic_cast<XorGate*>(user_gates[i])) {
            XorGate* xor_ptr = dynamic_cast<XorGate*>(user_gates[i]);
            //set input 1 
            if (input1 == 0) {
                Input* input1_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                user_inputs.push_back(input1_ptr);
                xor_ptr->set_input1(input1_ptr);
            }
            else {
                xor_ptr->set_input1(user_gates[input1 - 1]);
            }
            //set input 2
            if (input2 == 0) {
                Input* input2_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                num_inputs++;
                user_inputs.push_back(input2_ptr);
                xor_ptr->set_input2(input2_ptr);
            }
            else {
                xor_ptr->set_input2(user_gates[input2 - 1]);
            }
        }
        if (dynamic_cast<XnorGate*>(user_gates[i])) {
            XnorGate* xnor_ptr = dynamic_cast<XnorGate*>(user_gates[i]);
            //set input 1 
            if (input1 == 0) {
                Input* input1_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                user_inputs.push_back(input1_ptr);
                xnor_ptr->set_input1(input1_ptr);

            }
            else {
                xnor_ptr->set_input1(user_gates[input1 - 1]);
            }
            //set input 2
            if (input2 == 0) {
                Input* input2_ptr = new Input("-in" + std::to_string(num_inputs) + "-");
                num_inputs++;
                user_inputs.push_back(input2_ptr);
                xnor_ptr->set_input2(input2_ptr);
            }
            else {
                xnor_ptr->set_input2(user_gates[input2 - 1]);
            }
        }
        else if (dynamic_cast<Output*>(user_gates[i])) {

        }
    }
    std::cout << std::endl;

    user_circuit.enter_circuit_inputs(user_inputs);
    user_circuit.enter_circuit_outputs(user_outputs);
    user_circuit.enter_circuit_components(user_gates);
    user_circuit.num_layers = user_circuit.find_layers(user_outputs[0], 0);
    
    if (user_circuit.num_layers > 5) {
        std::cout << "Circuit is too big to be represented in the console. It must have less than 6 layers \n\n";
    }
    else {
        user_circuit.align_component(user_outputs[0], 0);
        user_circuit.fill_in_wires(user_outputs[0]);
        user_circuit.print_circuit();
    }

    std::string truth_table;

    std::cout << "Do you want to see the truth table (y/n)? ";
    std::cin >> truth_table;
    // check for invalid inputs when asking user if they want to see the truth table.
    while (truth_table != "y" && truth_table != "Y" && truth_table != "n" && truth_table != "N") { 
        std::cout << "Invalid input. Please enter 'y' or 'n': ";
        std::cin >> truth_table;
    }
    if (truth_table == "y" || truth_table == "Y") {
        std::cout << std::endl;
        user_circuit.print_truth_table();
    }

    return 0;
}