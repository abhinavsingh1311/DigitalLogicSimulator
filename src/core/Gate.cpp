#include <vector>
#include <string>
#include <memory>

enum GateType
{
    AND,
    OR,
    NOT,
    NAND,
    NOR,
    XOR,
    XNOR,
    BUFFER,
    FLIPFLOP,
    LATCH
};

class Gate
{
private:
    GateType type;
    std::vector<Gate *> inputs;
    bool output;
    std::string label;
    int id;

public:
    // constructor
    Gate(GateType type, std::string label, int id)
    {
        this->type = type;
        this->label = label;
        this->id = id;
    }

    // addInput

    void addInput(bool value)
    {
        inputSignals.push_back(value);
    };

    // getOutput
    bool getOutput() const
    {
        return outputSignals;
    };

    // setOutput
    void setInput(int index, bool value)
    {
        if (index < 0 || index > 2)
        {
            throw runtime_error("Index out of range");
        }
        if (type == GateType::Not && index != 0)
        {
            throw runtime_error("Not gate has only one input");
        }
        if (type == GateType::And || type == GateType::Or || type == GateType::Xor || type == GateType::Xnor)
        {
            if (index > 1)
            {
                throw runtime_error("And, Or, Xor, and Xnor gates have only two inputs");
            }
        }
        if (type == GateType::Nand || type == GateType::Nor)
        {
            if (index > 1)
            {
                throw runtime_error("Nand and Nor gates have only two inputs");
            }
        }
        if (type == GateType::Buffer && index != 0)
        {
            throw runtime_error("Buffer gate has only one input");
        }
        if (type == GateType::FlipFlop && index > 1)
        {
            throw runtime_error("FlipFlop gate has only two inputs");
        }
        if (type == GateType::Latch && index > 1)
        {
            throw runtime_error("Latch gate has only two inputs");
        }

        inputSignals[index] = value;
    };
};
