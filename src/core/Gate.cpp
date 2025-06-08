#include <stdexcept>
#include "Gate.h"

int Gate::nextId = 0;

Gate::Gate(GateType type, const std::string &gateLabel)
    : type(type), label(gateLabel.empty() ? "Gate" + std::to_string(nextId) : gateLabel), outputSignal(false)
{
    // inputSignals.resize(2, false);
    id = nextId++;
}

void Gate::addInput(bool value)
{
    inputSignals.push_back(value);
};

void Gate::setInput(int index, bool value)
{
    if (index < 0 || index >= inputSignals.size())
    {
        throw std::runtime_error("Index out of range");
    }

    inputSignals[index] = value;
};

bool Gate::getInput(int index) const
{
    if (index < 0 || index >= inputSignals.size())
    {
        throw std::runtime_error("Index out of range");
    }
    return inputSignals[index];
};

bool Gate::getOutput() const
{
    // get output value
    return outputSignal;
};

int Gate::getId() const
{
    return id;
}

std::string Gate::getLabel() const
{
    return label;
}

GateType Gate::getType() const
{
    return type;
}

void Gate::reset()
{
    // reset output value
    outputSignal = false;
}

int Gate::getInputCount() const
{
    return inputSignals.size();
}
