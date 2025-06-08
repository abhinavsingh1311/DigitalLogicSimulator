#pragma once
#include <vector>
#include <string>
// gatetype enum
enum class GateType
{
    And,
    Or,
    Not,
    Nor,
    Nand,
    Xor,
    Xnor,
    Buffer,
    FlipFlop,
    Latch
};

class Gate
{
    // define protected members
protected:
    // input signals
    std::vector<bool> inputSignals;
    // output signal
    bool outputSignal;
    // add label and id management
    static int nextId;
    std::string label;
    int id;
    GateType type;

public:
    // constructor with proper initialization
    Gate(GateType type, const std::string &gateLabel = "");
    // destructor
    virtual ~Gate() = default;
    // pure virtual evaluate method
    virtual void evaluate() = 0;
    // input access maanagement methods
    // setinput
    void setInput(int index, bool value);
    bool getInput(int index) const;
    // output access methods
    // getoutput
    bool getOutput() const;
    // addinput
    void addInput(bool value);
    // getter methods for id,label,type
    int getId() const;
    std::string getLabel() const;
    GateType getType() const;

    // utility methods
    // reset
    void reset();
    // getInputCount
    int getInputCount() const;
};