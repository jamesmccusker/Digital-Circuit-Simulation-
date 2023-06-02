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

static std::string digital_output(bool input)
{
    // find string representation of boolean output
    if (input) {
        return "1";
    }
    else {
        return "0";
    }
}

Circuit::Circuit() : num_layers(0)
{
    // initialize 2D array
    locations.resize(cols, std::vector<Component*>(rows, nullptr));
}

void Circuit::enter_circuit_inputs(std::vector<Input*> input)
{
    inputs = input;
}

void Circuit::enter_circuit_outputs(std::vector<Output*> output)
{
    outputs = output;
}

void Circuit::enter_circuit_components(std::vector<Component*> input)
{
    gates = input;
}

void Circuit::set_location(Component* gate, int x, int y)
{
    locations[x][y] = gate;
    gate->x = x;
    gate->y = y;
}

int Circuit::find_layers(Component* current_step, int layer)
{
    if (dynamic_cast<Input*>(current_step)) {
        // base case of recursion
        return layer;
    }
    // if current component is an output, recurse on its input
    else if (dynamic_cast<Output*>(current_step)) {
        Output* out = dynamic_cast<Output*>(current_step);
        return find_layers(out->input_1, layer);
    }
    // if current component is a gate recurse both inputs and return max layer of the two
    else if (dynamic_cast<AndGate*>(current_step)) {
        AndGate* andgate = dynamic_cast<AndGate*>(current_step);
        return std::max(find_layers(andgate->input_1, layer + 1), find_layers(andgate->input_2, layer + 1));
    }
    else if (dynamic_cast<NandGate*>(current_step)) {
        NandGate* nandgate = dynamic_cast<NandGate*>(current_step);
        return std::max(find_layers(nandgate->input_1, layer + 1), find_layers(nandgate->input_2, layer + 1));
    }
    else if (dynamic_cast<OrGate*>(current_step)) {
        OrGate* orgate = dynamic_cast<OrGate*>(current_step);
        return std::max(find_layers(orgate->input_1, layer + 1), find_layers(orgate->input_2, layer + 1));
    }
    else if (dynamic_cast<NorGate*>(current_step)) {
        NorGate* norgate = dynamic_cast<NorGate*>(current_step);
        return std::max(find_layers(norgate->input_1, layer + 1), find_layers(norgate->input_2, layer + 1));
    }
    else if (dynamic_cast<XorGate*>(current_step)) {
        XorGate* xorgate = dynamic_cast<XorGate*>(current_step);
        return std::max(find_layers(xorgate->input_1, layer + 1), find_layers(xorgate->input_2, layer + 1));
    }
    else if (dynamic_cast<XnorGate*>(current_step)) {
        XnorGate* xnorgate = dynamic_cast<XnorGate*>(current_step);
        return std::max(find_layers(xnorgate->input_1, layer + 1), find_layers(xnorgate->input_2, layer + 1));
    }
    // for not gate, only recurse one input
    else if (dynamic_cast<NotGate*>(current_step)) {
        NotGate* notgate = dynamic_cast<NotGate*>(current_step);
        return (find_layers(notgate->input_1, layer + 1));
    }
}

void Circuit::align_component(Component* current_component, int current_layer)
{
    if (dynamic_cast<Output*>(current_component)) {
        Output* out = dynamic_cast<Output*>(current_component);

        // Set the location of the output's input based on sum of geometric series
        set_location(out->input_1, 3 * (num_layers)-2, static_cast<int>((pow(2, (num_layers - 1)) - 1)));

        // Recurse on the output's input
        align_component(out->input_1, 0);
    }
    else if (dynamic_cast<AndGate*>(current_component)) {

        AndGate* andgate = dynamic_cast<AndGate*>(current_component);

        if (!dynamic_cast<Input*>(andgate->input_1)) {

            // set the location of first input based on nth term of geometric serires
            set_location(andgate->input_1, andgate->x - 3, static_cast<int>(andgate->y - (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(andgate->input_1, current_layer + 1);
        }
        // do the same for the seconf input
        if (!dynamic_cast<Input*>(andgate->input_2)) {
            set_location(andgate->input_2, andgate->x - 3, static_cast<int>(andgate->y + (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(andgate->input_2, current_layer + 1);
        }
    }
    // repeat for all other gates
    else if (dynamic_cast<NandGate*>(current_component)) {

        NandGate* nandgate = dynamic_cast<NandGate*>(current_component);

        if (!dynamic_cast<Input*>(nandgate->input_1)) {
            set_location(nandgate->input_1, nandgate->x - 3, static_cast<int>(nandgate->y - (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(nandgate->input_1, current_layer + 1);
        }
        if (!dynamic_cast<Input*>(nandgate->input_2)) {
            set_location(nandgate->input_2, nandgate->x - 3, static_cast<int>(nandgate->y + (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(nandgate->input_2, current_layer + 1);
        }
    }
    else if (dynamic_cast<OrGate*>(current_component)) {

        OrGate* orgate = dynamic_cast<OrGate*>(current_component);

        if (!dynamic_cast<Input*>(orgate->input_1)) {
            set_location(orgate->input_1, orgate->x - 3, static_cast<int>(orgate->y - (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(orgate->input_1, current_layer + 1);
        }
        if (!dynamic_cast<Input*>(orgate->input_2)) {
            set_location(orgate->input_2, orgate->x - 3, static_cast<int>(orgate->y + (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(orgate->input_2, current_layer + 1);
        }
    }
    else if (dynamic_cast<NorGate*>(current_component)) {

        NorGate* norgate = dynamic_cast<NorGate*>(current_component);

        if (!dynamic_cast<Input*>(norgate->input_1)) {

            set_location(norgate->input_1, norgate->x - 3, static_cast<int>(norgate->y - (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(norgate->input_1, current_layer + 1);
        }
        if (!dynamic_cast<Input*>(norgate->input_2)) {
            set_location(norgate->input_2, norgate->x - 3, static_cast<int>(norgate->y + (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(norgate->input_2, current_layer + 1);
        }
    }
    else if (dynamic_cast<XorGate*>(current_component)) {

        XorGate* xorgate = dynamic_cast<XorGate*>(current_component);

        if (!dynamic_cast<Input*>(xorgate->input_1)) {
            set_location(xorgate->input_1, xorgate->x - 3, static_cast<int>(xorgate->y - (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(xorgate->input_1, current_layer + 1);
        }
        if (!dynamic_cast<Input*>(xorgate->input_2)) {
            set_location(xorgate->input_2, xorgate->x - 3, static_cast<int>(xorgate->y + (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(xorgate->input_2, current_layer + 1);
        }
    }
    else if (dynamic_cast<XnorGate*>(current_component)) {

        XnorGate* xnorgate = dynamic_cast<XnorGate*>(current_component);

        if (!dynamic_cast<Input*>(xnorgate->input_1)) {
            set_location(xnorgate->input_1, xnorgate->x - 3, static_cast<int>(xnorgate->y - (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(xnorgate->input_1, current_layer + 1);
        }
        if (!dynamic_cast<Input*>(xnorgate->input_2)) {
            set_location(xnorgate->input_2, xnorgate->x - 3, static_cast<int>(xnorgate->y + (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(xnorgate->input_2, current_layer + 1);
        }
    }
    else if (dynamic_cast<NotGate*>(current_component)) {

        NotGate* notgate = dynamic_cast<NotGate*>(current_component);

        // only set location of one input for not gate
        if (!dynamic_cast<Input*>(notgate->input_1)) {
            set_location(notgate->input_1, notgate->x - 3, static_cast<int>(notgate->y - (pow(2, (num_layers - 2)) * pow(0.5, current_layer))));
            align_component(notgate->input_1, current_layer + 1);
        }
    }
    // terminate recursion if component is Input
    else if (dynamic_cast<Input*>(current_component)) {
        return;
    }
}
void Circuit::fill_in_wires(Component* current_component)
{
    // terminate recursion if component is null
    if (current_component == nullptr) {
        return;
    }
    if (dynamic_cast<Output*>(current_component)) {

        // cast current component to output and get the next connected component
        Output* Circuit_output = dynamic_cast<Output*>(current_component);
        Component* next = Circuit_output->input_1;

        // create a new wire 
        Wires* gate_wire_ptr = new Wires();
        Wires& gate_wire = *gate_wire_ptr;

        // set the ouput wire with component name
        gate_wire.set_middle_output("-" + current_component->get_name() + "-");

        // set position of wire
        gate_wire.x = next->x + 1;
        gate_wire.y = next->y;

        // assign the wire to the circuit grid
        set_location(&gate_wire, gate_wire.x, gate_wire.y);

        // continue recursion with next component
        fill_in_wires(next);
    }
    else if (dynamic_cast<AndGate*>(current_component)) {

        // cast the current component to an AndGate
        AndGate* andGate_ref = dynamic_cast<AndGate*>(current_component);
        AndGate andGate = *andGate_ref;

        //  get two inputs of AndGate
        Component* next1 = andGate.input_1;
        Component* next2 = andGate.input_2;

        Component* next1_ptr = andGate_ref->input_1;
        Component* next2_ptr = andGate_ref->input_2;

        // create a new circuit wire to represent input 1 and 2 
        Wires* new_input_ptr = new Wires();
        Wires& new_input = *new_input_ptr;

        // cast andGate to wider type long long before subtraction operation to avoid arithmatic overflow
        locations[static_cast<long long>(andGate.x) - 1][andGate.y] = new_input_ptr;

        // set the input wire with component names
        new_input.set_top_input("-" + next1->get_name() + "-");
        new_input.set_bottom_input("-" + next2->get_name() + "-");

        // create new wires for the sources of the first input
        Wires* input1_source_ptr = new Wires();
        Wires& input1_source = *input1_source_ptr;

        // if the first input is not an Input, set its properties
        if (!dynamic_cast<Input*>(next1_ptr)) {
            input1_source.set_middle_output("-" + andGate.get_name() + "-");
            input1_source.x = next1->x + 1;
            input1_source.y = next1->y;

            // assign the wire to its position in the circuit
            set_location(&input1_source, input1_source.x, input1_source.y);
        }

        // reate new wire for the source of the second input
        Wires* input2_source_ptr = new Wires();
        Wires& input2_source = *input2_source_ptr;

        // if the first input is not an Input, set its properties
        if (!dynamic_cast<Input*>(next2_ptr)) {

            input2_source.set_middle_output("-" + andGate.get_name() + "-");
            input2_source.x = next2->x + 1;
            input2_source.y = next2->y;

            // assign the wire to its position in the circuit
            set_location(&input2_source, input2_source.x, input2_source.y);
        }
        // continue recursion
        fill_in_wires(next1_ptr);
        fill_in_wires(next2_ptr);
    }
    // repeat the same for all other gates
    else if (dynamic_cast<NandGate*>(current_component)) {

        NandGate* nandGate_ref = dynamic_cast<NandGate*>(current_component);
        NandGate nandGate = *nandGate_ref;

        Component* next1 = nandGate.input_1;
        Component* next2 = nandGate.input_2;

        Component* next1_ptr = nandGate_ref->input_1;
        Component* next2_ptr = nandGate_ref->input_2;

        Wires* new_input_ptr = new Wires();
        Wires& new_input = *new_input_ptr;

        locations[static_cast<long long>(nandGate.x) - 1][nandGate.y] = new_input_ptr; 

        new_input.set_top_input("-" + next1->get_name() + "-");
        new_input.set_bottom_input("-" + next2->get_name() + "-");

        Wires* input1_source_ptr = new Wires();
        Wires& input1_source = *input1_source_ptr;

        if (!dynamic_cast<Input*>(next1_ptr)) {
            input1_source.set_middle_output("-" + nandGate.get_name() + "-");
            input1_source.x = next1->x + 1;
            input1_source.y = next1->y;

            set_location(&input1_source, input1_source.x, input1_source.y);
        }
        Wires* input2_source_ptr = new Wires();
        Wires& input2_source = *input2_source_ptr;

        if (!dynamic_cast<Input*>(next2_ptr)) {

            input2_source.set_middle_output("-" + nandGate.get_name() + "-");
            input2_source.x = next2->x + 1;
            input2_source.y = next2->y;
            set_location(&input2_source, input2_source.x, input2_source.y);
        }
        fill_in_wires(next1_ptr);
        fill_in_wires(next2_ptr);
    }
    else if (dynamic_cast<OrGate*>(current_component)) {

        OrGate* orGate_ref = dynamic_cast<OrGate*>(current_component);
        OrGate orGate = *orGate_ref;

        Component* next1 = orGate.input_1;
        Component* next2 = orGate.input_2;

        Component* next1_ptr = orGate_ref->input_1;
        Component* next2_ptr = orGate_ref->input_2;

        Wires* new_input_ptr = new Wires();
        Wires& new_input = *new_input_ptr;

        locations[static_cast<long long>(orGate.x) - 1][orGate.y] = new_input_ptr;

        new_input.set_top_input("-" + next1->get_name() + "-");
        new_input.set_bottom_input("-" + next2->get_name() + "-");

        Wires* input1_source_ptr = new Wires();
        Wires& input1_source = *input1_source_ptr;

        if (!dynamic_cast<Input*>(next1)) {
            input1_source.set_middle_output("-" + orGate.get_name() + "-");
            input1_source.x = next1->x + 1;
            input1_source.y = next1->y;

            set_location(&input1_source, input1_source.x, input1_source.y);
        }
        Wires* input2_source_ptr = new Wires();
        Wires& input2_source = *input2_source_ptr;

        if (!dynamic_cast<Input*>(next2)) {

            input2_source.set_middle_output("-" + orGate.get_name() + "-");
            input2_source.x = next2->x + 1;
            input2_source.y = next2->y;
            set_location(&input2_source, input2_source.x, input2_source.y);
        }
        fill_in_wires(next1_ptr);
        fill_in_wires(next2_ptr);
    }
    else if (dynamic_cast<NorGate*>(current_component)) {

        NorGate* norGate_ref = dynamic_cast<NorGate*>(current_component);
        NorGate norGate = *norGate_ref;

        Component* next1 = norGate.input_1;
        Component* next2 = norGate.input_2;

        Component* next1_ptr = norGate_ref->input_1;
        Component* next2_ptr = norGate_ref->input_2;

        Wires* new_input_ptr = new Wires();
        Wires& new_input = *new_input_ptr;

        locations[static_cast<long long>(norGate.x) - 1][norGate.y] = new_input_ptr;

        new_input.set_top_input("-" + next1->get_name() + "-");
        new_input.set_bottom_input("-" + next2->get_name() + "-");

        Wires* input1_source_ptr = new Wires();
        Wires& input1_source = *input1_source_ptr;

        if (!dynamic_cast<Input*>(next1)) {
            input1_source.set_middle_output("-" + norGate.get_name() + "-");
            input1_source.x = next1->x + 1;
            input1_source.y = next1->y;

            set_location(&input1_source, input1_source.x, input1_source.y);
        }
        Wires* input2_source_ptr = new Wires();
        Wires& input2_source = *input2_source_ptr;

        if (!dynamic_cast<Input*>(next2)) {

            input2_source.set_middle_output("-" + norGate.get_name() + "-");
            input2_source.x = next2->x + 1;
            input2_source.y = next2->y;
            set_location(&input2_source, input2_source.x, input2_source.y);
        }
        fill_in_wires(next1_ptr);
        fill_in_wires(next2_ptr);
    }
    else if (dynamic_cast<XorGate*>(current_component))
    {
        XorGate* xorGate_ref = dynamic_cast<XorGate*>(current_component);
        XorGate xorGate = *xorGate_ref;

        Component* next1 = xorGate.input_1;
        Component* next2 = xorGate.input_2;

        Component* next1_ptr = xorGate_ref->input_1;
        Component* next2_ptr = xorGate_ref->input_2;

        Wires* new_input_ptr = new Wires();
        Wires& new_input = *new_input_ptr;

        locations[static_cast<long long>(xorGate.x) - 1][xorGate.y] = new_input_ptr;

        new_input.set_top_input("-" + next1->get_name() + "-");
        new_input.set_bottom_input("-" + next2->get_name() + "-");

        Wires* input1_source_ptr = new Wires();
        Wires& input1_source = *input1_source_ptr;

        if (!dynamic_cast<Input*>(next1)) {
            input1_source.set_middle_output("-" + xorGate.get_name() + "-");
            input1_source.x = next1->x + 1;
            input1_source.y = next1->y;

            set_location(&input1_source, input1_source.x, input1_source.y);
        }
        Wires* input2_source_ptr = new Wires();
        Wires& input2_source = *input2_source_ptr;

        if (!dynamic_cast<Input*>(next2)) {
            input2_source.set_middle_output("-" + xorGate.get_name() + "-");
            input2_source.x = next2->x + 1;
            input2_source.y = next2->y;
            set_location(&input2_source, input2_source.x, input2_source.y);
        }
        fill_in_wires(next1_ptr);
        fill_in_wires(next2_ptr);
    }
    else if (dynamic_cast<XnorGate*>(current_component)) {

        XnorGate* xnorGate_ref = dynamic_cast<XnorGate*>(current_component);
        XnorGate xnorGate = *xnorGate_ref;

        Component* next1 = xnorGate.input_1;
        Component* next2 = xnorGate.input_2;

        Component* next1_ptr = xnorGate_ref->input_1;
        Component* next2_ptr = xnorGate_ref->input_2;

        Wires* new_input_ptr = new Wires();
        Wires& new_input = *new_input_ptr;

        locations[static_cast<long long>(xnorGate.x) - 1][xnorGate.y] = new_input_ptr;

        new_input.set_top_input("-" + next1->get_name() + "-");
        new_input.set_bottom_input("-" + next2->get_name() + "-");

        Wires* input1_source_ptr = new Wires();
        Wires& input1_source = *input1_source_ptr;

        if (!dynamic_cast<Input*>(next1)) {
            input1_source.set_middle_output("-" + xnorGate.get_name() + "-");
            input1_source.x = next1->x + 1;
            input1_source.y = next1->y;

            set_location(&input1_source, input1_source.x, input1_source.y);
        }
        Wires* input2_source_ptr = new Wires();
        Wires& input2_source = *input2_source_ptr;

        if (!dynamic_cast<Input*>(next2)) {

            input2_source.set_middle_output("-" + xnorGate.get_name() + "-");
            input2_source.x = next2->x + 1;
            input2_source.y = next2->y;
            set_location(&input2_source, input2_source.x, input2_source.y);
        }
        fill_in_wires(next1_ptr);
        fill_in_wires(next2_ptr);
    }
    else if (dynamic_cast<NotGate*>(current_component))
    {
        NotGate* notGate_ref = dynamic_cast<NotGate*>(current_component);
        NotGate notGate = *notGate_ref;

        Component* next1 = notGate.input_1;
        Component* next1_ptr = notGate_ref->input_1;

        Wires* new_input_ptr = new Wires();
        Wires& new_input = *new_input_ptr;

        locations[static_cast<long long>(notGate.x) - 1][notGate.y] = new_input_ptr;

        new_input.set_middle_output("-" + next1->get_name() + "-");

        Wires* input1_source_ptr = new Wires();
        Wires& input1_source = *input1_source_ptr;

        if (!dynamic_cast<Input*>(next1)) {
            input1_source.set_middle_output("-" + notGate.get_name() + "-");
            input1_source.x = next1->x + 1;
            input1_source.y = next1->y;

            set_location(&input1_source, input1_source.x, input1_source.y);
        }
        fill_in_wires(next1_ptr);
    }
    // terminate recursion if component is input
    else if (dynamic_cast<Input*>(current_component)) {
        return;
    }
}
void Circuit::print_circuit()
{
    // prints number of coloumns depending on how many layers in the circuit
    for (int y = 0; y < (pow(2, (num_layers)) - 1); y++) { 
    
        for (int l = 0; l < 3; l++) {
            
            // iterate over the x axis 
            for (int x = 0; x < (3 * num_layers); x++) {
              
                // retreive component from current x-y location 
                Component* current_comp = locations[x][y];
                if (current_comp == nullptr) {
                
                    if (l == 1) {
                    
                        std::cout << "\t";
                    }
                    else {
                        // print tab character if there is no component
                        std::cout << "\t";
                    }
                }
                else {
                    // if there is component, retreive symbol and print
                    std::cout << current_comp->get_symbol(l) + "\t";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }
}
void Circuit::print_truth_table()
{
    // Print column headings

    for (int i = 0; i < inputs.size(); i++) {
        std::cout << inputs[i]->get_name() + "\t";
    }

    std::cout << "| Outputs" << std::endl;

    // Print a separator line

    for (int k = 1; k <= inputs.size(); k++) {
        std::cout << "--------";
    }

    std::cout << "| " << std::endl;

    //Calculate the number of input combinations
    int input_combinations = pow(2, inputs.size());

    // Loop through each input combination
    for (int i = 0; i < input_combinations; i++) {
        //Set the input values for this combination
        for (int j = 0; j < inputs.size(); j++) {
            bool input_value = (i >> j) & 1;
            inputs[j]->change_state(input_value);
            std::cout << digital_output(inputs[j]->get_output()) << "\t";
        }
        std::cout << "|";
        bool output_value = outputs[0]->get_output();
        std::cout << " " + digital_output(output_value) << "\t";

        std::cout << "\n";
    }
    std::cout << "\n\n";
}

