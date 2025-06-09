#include "TruthTable.h"

// constructor

TruthTable::TruthTable(Gate *gate, const std::vector<bool> &expectedresults)
{
    /*Store the gate pointer in member variable
    Determine number of inputs from the gate (gate->getInputCount())
    Store expected results vector
    Call generateInputCombinations(numInputs) to create all input patterns
    Validate that expectedResults size matches 2^numInputs
    If size doesn't match, throw exception with helpful message

    Error checking needed:

    Null gate pointer check
    Expected results size validation (should be 2^n where n = numInputs)*/

    if (gate == nullptr)
    {
        throw std::invalid_argument("Gate pointer cannot be null");
    };
    this->gate = gate;
    this->numInputs = gate->getInputCount();
    int expectedSize = 1 << numInputs;
    if (expectedresults.size() != expectedSize)
    {
        throw std::invalid_argument("Expected results size does not match number of rows");
    }
    generateInputCombinations(numInputs);
    setExpectedOutputs(expectedresults);
};

// core functions

void TruthTable::generateInputCombinations(int numInputs)
{
    int totalCombinations = 1 << numInputs; // bit shift
    // clear existing rows
    rows.clear();
    // loop from 0 to totalCombinations
    for (int i = 0; i < totalCombinations; i++)
    {
        // vector of size inputs
        std::vector<bool> row(numInputs);
        // Use bit manipulation: check if (i >> bit_position) & 1 is true
        for (int bit_position = 0; bit_position < numInputs; bit_position++)
        {
            row[bit_position] = (i >> bit_position) & 1;
        }

        TruthTableRow tableRow(row, false);
        rows.push_back(tableRow);
    }
};

void TruthTable::evaluateGate()
{
    // loop through each row in rows vector
    for (auto &row : rows)
    {
        setGateInputs(gate, row.inputs);
        gate->evaluate();
        row.actualOutput = gate->getOutput();
    }
    compareResults();
};

void TruthTable::setGateInputs(Gate *gate, const std::vector<bool> &inputs)
{

    // validate inputs size matches gate's expected input count
    if (inputs.size() != gate->getInputCount())
    {
        throw std::invalid_argument("Number of inputs does not match gate's expected input count");
    }

    // loop through the input vectors
    for (int i = 0; i < gate->getInputCount(); i++)
    {
        // handle potential exceptions
        try
        {
            gate->setInput(i, inputs[i]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error setting input: " << e.what() << std::endl;
        }
    }
};

void TruthTable::compareResults()
{
    // loop through each row in rows vector
    for (auto &row : rows)
    {
        row.isMatch = row.expectedOutput == row.actualOutput;
    }
};

// display methods

void TruthTable::printToConsole() const
{
    printSeparator();
    printHeader();
    printSeparator();
    for (const auto &row : rows)
    {
        printRow(row);
    }
    printSeparator();
    std::cout << "Total Rows: " << rows.size() << std::endl;
    std::cout << "Accuracy: " << getAccuracy() << std::endl;
};

void TruthTable::printHeader() const
{
    std::cout << "Inputs";
    for (int i = 0; i < numInputs; i++)
    {
        std::cout << "\t" << "I" << i;
    }
    std::cout << "\tExpected\tActual\tMatch" << std::endl;
};

void TruthTable::printRow(const TruthTableRow &row) const
{
    std::cout << "Row";
    for (const auto &input : row.inputs)
    {
        std::cout << "\t" << boolToString(input);
    }
    std::cout << "\t" << boolToString(row.expectedOutput) << "\t" << boolToString(row.actualOutput) << "\t" << boolToString(row.isMatch) << std::endl;
};

void TruthTable::printSeparator() const
{
    // calculate total width based on number of columns
    int totalWidth = 0;
    for (int i = 0; i < numInputs; i++)
    {
        totalWidth += 1 + 3 + 1; // 1 for tab, 3 for input name, 1 for tab
    }
    totalWidth += 1 + 1 + 1 + 1 + 1; // 1 for tab, 1 for expected, 1 for actual, 1 for match, 1 for tab

    // print horizontal lines using "+","-" and "|" characters
    for (int i = 0; i < totalWidth; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
};

// analysis methods

void TruthTable::setExpectedOutputs(const std::vector<bool> &expectedOutputs)
{
    // check that expectedOutputs size matches rows size
    if (expectedOutputs.size() != rows.size())
    {
        throw std::invalid_argument("Expected outputs size does not match number of rows");
    }
    // loop through rows and set expected output
    for (int i = 0; i < rows.size(); i++)
    {
        rows[i].expectedOutput = expectedOutputs[i];
    }
    // reset all isMatch to false
    for (auto &row : rows)
    {
        row.isMatch = false;
    }
};

void TruthTable::validateResults()
{
    // calls compare results to update all isMatch flags
    compareResults();
};

double TruthTable::getAccuracy() const
{
    // count how many rows have isMatch as true
    int numMatches = 0;
    for (const auto &row : rows)
    {
        if (row.isMatch)
        {
            numMatches++;
        }
    }
    // calculate accuracy as percentage of rows with isMatch as true
    double accuracy = static_cast<double>(numMatches) / rows.size() * 100;
    return accuracy;
};

std::vector<int> TruthTable::getMismatches() const
{
    std::vector<int> result;
    // loop through rows with index
    for (int i = 0; i < rows.size(); i++)
    {
        if (rows[i].isMatch == false)
        {
            result.push_back(i);
        }
    }
    return result;
};

// error reporting

void TruthTable::printValidationReport() const
{

    // print total number of test cases
    std::cout << "Total number of test cases: " << rows.size() << std::endl;
    std::cout << "Number of passing test cases: " << (rows.size() - getMismatches().size()) << std::endl;
    std::cout << "Number of failing test cases: " << getMismatches().size() << std::endl;
    // print accuracy
    std::cout << "Accuracy: " << getAccuracy() << "%" << std::endl;
    // print mismatches, row numbers
    std::cout << "Mismatches: ";
    for (const auto &row : getMismatches())
    {
        std::cout << row << " ";
    }
    std::cout << std::endl;
    // print overall pass/fail status
    if (getMismatches().size() == 0)
    {
        std::cout << "Test passed!" << std::endl;
    }
    else
    {
        std::cout << "Test failed!" << std::endl;
    }
};

void TruthTable::highlightErrors() const
{
    // only print rows where isMatch is false
    for (const auto &row : rows)
    {
        if (row.isMatch == false)
        {
            printRow(row);
        }
    }
};

// getters

int TruthTable::getNumInputs() const
{
    // return number of inputs
    return numInputs;
};

int TruthTable::getNumRows() const
{
    // check if rows is empty
    if (rows.empty())
    {
        throw std::invalid_argument("Number of rows cannot be zero");
    }
    // return number of rows
    return rows.size();
};

const std::vector<TruthTable::TruthTableRow> &TruthTable::getRows() const
{
    // check if rows is empty
    if (rows.empty())
    {
        throw std::invalid_argument("Number of rows cannot be zero");
    }
    // return reference to rows
    return rows;
};

bool TruthTable::isPassing() const
{
    return getAccuracy() == 100.00;
};

// utilities

void TruthTable::reset()
{
    rows.clear();
    numInputs = 0;
    gate = nullptr;
    // return object to default state
    return;
};

void TruthTable::addRow(const std::vector<bool> &inputs, bool expectedOutput)
{
    // validate inputs size matches numInputs
    if (inputs.size() != numInputs)
    {
        throw std::invalid_argument("Number of inputs does not match number of inputs in truth table");
    }
    // create new row
    TruthTableRow row(inputs, expectedOutput);
    // add row to rows
    rows.push_back(row);
};

// helper methods
void TruthTable::setGateInputsHelper(const std::vector<bool> &inputs)
{
    // uses members gates to validate
    if (inputs.size() != gate->getInputCount())
    {
        throw std::invalid_argument("Number of inputs does not match gate's expected input count");
    }
    for (int i = 0; i < inputs.size(); i++)
    {
        // handle potential exceptions
        try
        {
            gate->setInput(i, inputs[i]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error setting input: " << e.what() << std::endl;
        }
    }
};

std::string TruthTable::boolToString(bool value) const
{
    return value ? "1" : "0";
};

void TruthTable::validateRowIndex(int index) const
{
    if (index < 0 || index >= rows.size())
    {
        throw std::out_of_range("Index out of range");
    }
};
