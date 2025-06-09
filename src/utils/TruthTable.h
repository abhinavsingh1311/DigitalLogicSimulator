#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "BasicGates.h"

class TruthTable
{
public:
    //  Store input combinations and expected outputs
    struct TruthTableRow
    {
        std::vector<bool> inputs;
        bool expectedOutput;
        bool actualOutput;
        bool isMatch;

        TruthTableRow(const std::vector<bool> &inputs, bool expectedOutput)
            : inputs(inputs), expectedOutput(expectedOutput), actualOutput(false), isMatch(false) {};
    };

private:
    std::vector<TruthTableRow> rows;
    Gate *gate; // gate we are testing
    int numInputs;

public:
    // constructor
    TruthTable(Gate *gate, const std::vector<bool> &expectedresults);

    //  Method to generate all input combinations for N inputs
    // for n inputs, there are 2^n possible input combinations
    // e.g n = 2, there are 2^2 = 4 possible input combinations (00,01,10,11)

    void generateInputCombinations(int n);

    //  Method to evaluate gate for all combinations
    void evaluateGate();
    void setGateInputs(Gate *gate, const std::vector<bool> &inputs);
    void compareResults();
    //  Method to display truth table in formatted way
    void printToConsole() const;
    void printHeader() const;
    void printRow(const TruthTableRow &row) const;
    void printSeparator() const;
    //  Method to compare expected vs actual results
    void setExpectedOutputs(const std::vector<bool> &expectedOutputs);
    void validateResults();
    double getAccuracy() const;
    std::vector<int> getMismatches() const;

    // Error reporting
    void printValidationReport() const;
    void highlightErrors() const;

    // Getters

    int getNumInputs() const;
    int getNumRows() const;
    const std::vector<TruthTableRow> &getRows() const;
    bool isPassing() const;

    // utilities
    void reset();
    void addRow(const std::vector<bool> &inputs, bool expectedOutput);

private:
    void setGateInputsHelper(const std::vector<bool> &inputs);
    std::string boolToString(bool value) const;
    void validateRowIndex(int index) const;
};
