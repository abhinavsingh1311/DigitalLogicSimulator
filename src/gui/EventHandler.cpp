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
    LATCH,
    REGISTER,
    COUNTER,
    MEMORY,
    ROM,
    RAM,
    ALU,
    MUX,
    DEMUX,
    ENCODER,
    DECODER,
    COMPARATOR,
    ADDER,
    SUBTRACTOR,
    MULTIPLIER,
    DIVIDER,

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

    void addInput(Gate *input)
    {
        inputs.push_back(input);
    };

    // getOutput

    bool getOutput()
    {
        return output;
    };

    // setOutput
    void setOutput(bool output)
    {
        this->output = output;
    };
};
