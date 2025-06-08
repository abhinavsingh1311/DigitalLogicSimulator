#include "BasicGates.h"
#include <algorithm>
#include <stdexcept>

// ANDGate Implementation
ANDGate::ANDGate(const std::string &gateLabel) : Gate(GateType::And, gateLabel)
{
    // Initialize with 2 inputs and 1 output
    inputSignals.resize(2, false);
}

void ANDGate::evaluate()
{
    // Check if there are at least 2 inputs
    if (inputSignals.size() < 2)
    {
        throw std::invalid_argument("ANDGate: At least 2 inputs are required.");
    }
    //  Implement AND logic using std::all_of or manual loop
    bool result = std::all_of(inputSignals.begin(), inputSignals.end(), [](bool value)
                              { return value; });

    //  Update output signal after evaluation
    outputSignal = result;
}

// ORGate Implementation
ORGate::ORGate(const std::string &gateLabel) : Gate(GateType::Or, gateLabel)
{
    // Initialize with 2 inputs and 1 output
    inputSignals.resize(2, false);
}
void ORGate::evaluate()
{
    // Check if there are at least 2 inputs
    if (inputSignals.size() < 2)
    {
        throw std::invalid_argument("ORGate: At least 2 inputs are required.");
    }
    // Implement OR logic using std::any_of or manual loop
    bool result = std::any_of(inputSignals.begin(), inputSignals.end(), [](bool value)
                              { return value; });

    // Update output signal after evaluation
    outputSignal = result;
}

// NOTGate Implementation
NOTGate::NOTGate(const std::string &gateLabel) : Gate(GateType::Not, gateLabel)
{
    // Initialize with 1 input and 1 output
    inputSignals.resize(1, false);
}
void NOTGate::evaluate()
{
    //  Validate exactly one input
    if (inputSignals.size() != 1)
    {
        throw std::invalid_argument("NOTGate: Exactly one input is required.");
    }
    //  Implement NOT logic
    bool result = !inputSignals[0];
    //  Update output signal after evaluation
    outputSignal = result;
}

//  Implement NAND (AND + inversion)
NANDGate::NANDGate(const std::string &gateLabel) : Gate(GateType::Nand, gateLabel)
{
    // Initialize with 2 inputs and 1 output
    inputSignals.resize(2, false);
}
void NANDGate::evaluate()
{
    // Check if there are at least 2 inputs
    if (inputSignals.size() < 2)
    {
        throw std::invalid_argument("NANDGate: At least 2 inputs are required.");
    }
    //  Implement NAND logic using std::all_of or manual loop
    bool result = !std::all_of(inputSignals.begin(), inputSignals.end(), [](bool value)
                               { return value; });
    //  Update output signal after evaluation
    outputSignal = result;
}

//  Implement NOR (OR + inversion)
NORGate::NORGate(const std::string &gateLabel) : Gate(GateType::Nor, gateLabel)
{
    // Initialize with 2 inputs and 1 output
    inputSignals.resize(2, false);
}
void NORGate::evaluate()
{
    // Check if there are at least 2 inputs
    if (inputSignals.size() < 2)
    {
        throw std::invalid_argument("NORGate: At least 2 inputs are required.");
    }
    //  Implement NOR logic using std::any_of or manual loop
    bool result = !std::any_of(inputSignals.begin(), inputSignals.end(), [](bool value)
                               { return value; });

    //  Update output signal after evaluation
    outputSignal = result;
}

//  Implement XOR (odd parity logic)
XORGate::XORGate(const std::string &gateLabel) : Gate(GateType::Xor, gateLabel)
{
    // Initialize with 2 inputs and 1 output
    inputSignals.resize(2, false);
}
void XORGate::evaluate()
{
    // Check if there are at least 2 inputs
    if (inputSignals.size() < 2)
    {
        throw std::invalid_argument("XORGate: At least 2 inputs are required.");
    }
    //  Implement XOR logic using std::count or manual loop
    bool result = std::count(inputSignals.begin(), inputSignals.end(), true) % 2 == 1;

    //  Update output signal after evaluation
    outputSignal = result;
}

//  Implement XNOR (even parity logic)
XNORGate::XNORGate(const std::string &gateLabel) : Gate(GateType::Xnor, gateLabel)
{
    // Initialize with 2 inputs and 1 output
    inputSignals.resize(2, false);
}
void XNORGate::evaluate()
{
    // Check if there are at least 2 inputs
    if (inputSignals.size() < 2)
    {
        throw std::invalid_argument("XNORGate: At least 2 inputs are required.");
    }
    //  Implement XNOR logic using std::count or manual loop
    bool result = std::count(inputSignals.begin(), inputSignals.end(), true) % 2 == 0;
    //  Update output signal after evaluation
    outputSignal = result;
}

// BUFFER (direct pass-through)
BufferGate::BufferGate(const std::string &gateLabel) : Gate(GateType::Buffer, gateLabel)
{
    // Initialize with 1 input and 1 output
    inputSignals.resize(1, false);
}
void BufferGate::evaluate()
{
    // Check if there is exactly 1 input
    if (inputSignals.size() != 1)
    {
        throw std::invalid_argument("BufferGate: Exactly 1 input is required.");
    }
    outputSignal = inputSignals[0];
}
