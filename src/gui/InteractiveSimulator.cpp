#include "InteractiveSimulator.h"
#include <sstream>   // For std::stringstream
#include <algorithm> // For std::transform
#include <cctype>    // For ::tolower
#include <iostream>

void InteractiveSimulator::displayWelcomeMessage()
{
    std::cout << "=== Digital Logic Simulator ===" << std::endl;
    std::cout << "Type 'help' for available commands" << std::endl;
    std::cout << "Available gate types: and, or, not, nand, nor, xor, xnor, buffer" << std::endl;
    std::cout << std::endl;
}

void InteractiveSimulator::displayPrompts()
{
    std::cout << "> ";
}

std::string InteractiveSimulator::getUserInput()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void InteractiveSimulator::cleanUp()
{
    gates.clear();
    std::cout << "Goodbye!" << std::endl;
}

std::vector<std::string> InteractiveSimulator::parseInput(const std::string &input)
{
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (ss >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

GateType InteractiveSimulator::parseGateType(const std::string &typeStr)
{
    std::string lowerType = typeStr;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);

    if (lowerType == "and")
        return GateType::And;
    if (lowerType == "or")
        return GateType::Or;
    if (lowerType == "not")
        return GateType::Not;
    if (lowerType == "nand")
        return GateType::Nand;
    if (lowerType == "nor")
        return GateType::Nor;
    if (lowerType == "xor")
        return GateType::Xor;
    if (lowerType == "xnor")
        return GateType::Xnor;
    if (lowerType == "buffer")
        return GateType::Buffer;

    throw std::invalid_argument("Unknown gate type: " + typeStr);
}

bool InteractiveSimulator::validateCommand(const std::vector<std::string> &tokens)
{
    if (tokens.empty())
        return false;

    std::string command = tokens[0];
    return (command == "create" || command == "help" || command == "exit" ||
            command == "clear" || command == "list" || command == "set" ||
            command == "eval" || command == "table" || command == "info" ||
            command == "delete" || command == "test");
}

// Missing executeCommand method implementation
void InteractiveSimulator::executeCommand(const std::string &input)
{
    if (input.empty())
        return;

    std::vector<std::string> tokens = parseInput(input);
    if (tokens.empty())
        return;

    std::string command = tokens[0];
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    try
    {
        if (command == "create")
            handleCreate(tokens);
        else if (command == "list")
            handleList(tokens);
        else if (command == "set")
            handleSet(tokens);
        else if (command == "eval")
            handleEval(tokens);
        else if (command == "table")
            handleTable(tokens);
        else if (command == "info")
            handleInfo(tokens);
        else if (command == "delete")
            handleDelete(tokens);
        else if (command == "test")
            handleTest(tokens);
        else if (command == "help")
            handleHelp(tokens);
        else if (command == "exit")
            handleExit(tokens);
        else if (command == "clear")
            handleClear(tokens);
        else
            std::cout << "Unknown command: " << command << ". Type 'help' for available commands." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Fixed handleCreate implementation
void InteractiveSimulator::handleCreate(const std::vector<std::string> &tokens)
{
    try
    {
        if (tokens.size() != 3)
        {
            std::cout << "Usage: create <gate_type> <name>" << std::endl;
            std::cout << "Example: create and MyAndGate" << std::endl;
            return;
        }

        std::string gateName = tokens[2];

        // Check if gate name already exists
        if (gates.find(gateName) != gates.end())
        {
            std::cout << "Gate '" << gateName << "' already exists!" << std::endl;
            return;
        }

        // Create gate
        GateType gateType = parseGateType(tokens[1]);
        auto gate = GateFactory::createGate(gateType, gateName);
        gates[gateName] = gate;

        std::cout << "✓ Created " << tokens[1] << " gate '" << gateName << "' with "
                  << gate->getInputCount() << " inputs" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "✗ Error: " << e.what() << std::endl;
    }
}

// Add missing essential command implementations
void InteractiveSimulator::handleList(const std::vector<std::string> &tokens)
{
    if (gates.empty())
    {
        std::cout << "No gates created yet. Use 'create <type> <name>' to create a gate." << std::endl;
        return;
    }

    std::cout << "Active Gates:" << std::endl;
    for (const auto &pair : gates)
    {
        auto &gate = pair.second;
        std::cout << "- " << pair.first << " (" << getGateTypeName(gate->getType())
                  << ", " << gate->getInputCount() << " inputs)" << std::endl;
    }
}

void InteractiveSimulator::handleSet(const std::vector<std::string> &tokens)
{
    if (tokens.size() < 3)
    {
        std::cout << "Usage: set <gate_name> <input1> <input2> ..." << std::endl;
        std::cout << "Example: set MyAndGate 1 0" << std::endl;
        return;
    }

    std::string gateName = tokens[1];
    auto it = gates.find(gateName);
    if (it == gates.end())
    {
        std::cout << "Gate '" << gateName << "' not found." << std::endl;
        return;
    }

    auto &gate = it->second;
    std::vector<bool> inputs;

    // Parse input values
    for (size_t i = 2; i < tokens.size(); ++i)
    {
        if (tokens[i] == "1" || tokens[i] == "true")
        {
            inputs.push_back(true);
        }
        else if (tokens[i] == "0" || tokens[i] == "false")
        {
            inputs.push_back(false);
        }
        else
        {
            std::cout << "Invalid input value: " << tokens[i] << ". Use 0, 1, true, or false." << std::endl;
            return;
        }
    }

    if (inputs.size() != gate->getInputCount())
    {
        std::cout << "Gate '" << gateName << "' expects " << gate->getInputCount()
                  << " inputs, got " << inputs.size() << std::endl;
        return;
    }

    // Set inputs
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        gate->setInput(i, inputs[i]);
    }

    std::cout << "✓ Set inputs for '" << gateName << "': ";
    for (bool input : inputs)
    {
        std::cout << (input ? "1" : "0") << " ";
    }
    std::cout << std::endl;
}

void InteractiveSimulator::handleEval(const std::vector<std::string> &tokens)
{
    if (tokens.size() != 2)
    {
        std::cout << "Usage: eval <gate_name>" << std::endl;
        return;
    }

    std::string gateName = tokens[1];
    auto it = gates.find(gateName);
    if (it == gates.end())
    {
        std::cout << "Gate '" << gateName << "' not found." << std::endl;
        return;
    }

    auto &gate = it->second;
    gate->evaluate();
    bool output = gate->getOutput();

    std::cout << "Output: " << (output ? "1" : "0") << " (" << (output ? "true" : "false") << ")" << std::endl;
}

void InteractiveSimulator::handleInfo(const std::vector<std::string> &tokens)
{
    if (tokens.size() != 2)
    {
        std::cout << "Usage: info <gate_name>" << std::endl;
        return;
    }

    std::string gateName = tokens[1];
    auto it = gates.find(gateName);
    if (it == gates.end())
    {
        std::cout << "Gate '" << gateName << "' not found." << std::endl;
        return;
    }

    auto &gate = it->second;
    std::cout << "Gate: " << gateName << std::endl;
    std::cout << "Type: " << getGateTypeName(gate->getType()) << std::endl;
    std::cout << "Inputs: " << gate->getInputCount() << std::endl;
    std::cout << "Current inputs: ";
    for (int i = 0; i < gate->getInputCount(); ++i)
    {
        std::cout << (gate->getInput(i) ? "1" : "0") << " ";
    }
    std::cout << std::endl;
    std::cout << "Last output: " << (gate->getOutput() ? "1" : "0") << std::endl;
}

void InteractiveSimulator::handleHelp(const std::vector<std::string> &tokens)
{
    std::cout << "Available Commands:" << std::endl;
    std::cout << "  create <type> <name>  - Create a new gate" << std::endl;
    std::cout << "  list                  - Show all created gates" << std::endl;
    std::cout << "  set <name> <inputs>   - Set gate inputs (e.g., set MyGate 1 0)" << std::endl;
    std::cout << "  eval <name>           - Evaluate gate and show output" << std::endl;
    std::cout << "  info <name>           - Show gate information" << std::endl;
    std::cout << "  table <name>          - Generate truth table for gate" << std::endl;
    std::cout << "  test <name>           - Interactive testing mode" << std::endl;
    std::cout << "  delete <name>         - Delete a gate" << std::endl;
    std::cout << "  clear                 - Clear screen" << std::endl;
    std::cout << "  help                  - Show this help message" << std::endl;
    std::cout << "  exit                  - Exit the simulator" << std::endl;
    std::cout << std::endl;
    std::cout << "Gate types: and, or, not, nand, nor, xor, xnor, buffer" << std::endl;
}

void InteractiveSimulator::handleExit(const std::vector<std::string> &tokens)
{
    running = false;
    std::cout << "Exiting simulator..." << std::endl;
}

void InteractiveSimulator::handleClear(const std::vector<std::string> &tokens)
{
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear screen
}

// Helper method to convert GateType to string
std::string InteractiveSimulator::getGateTypeName(GateType type)
{
    switch (type)
    {
    case GateType::And:
        return "AND";
    case GateType::Or:
        return "OR";
    case GateType::Not:
        return "NOT";
    case GateType::Nand:
        return "NAND";
    case GateType::Nor:
        return "NOR";
    case GateType::Xor:
        return "XOR";
    case GateType::Xnor:
        return "XNOR";
    case GateType::Buffer:
        return "BUFFER";
    default:
        return "UNKNOWN";
    }
}

// Stub implementations for missing handlers (implement these based on your needs)
void InteractiveSimulator::handleTable(const std::vector<std::string> &tokens)
{
    // TODO: Implement truth table generation
    std::cout << "Truth table generation not yet implemented." << std::endl;
}

void InteractiveSimulator::handleTest(const std::vector<std::string> &tokens)
{
    // TODO: Implement interactive testing mode
    std::cout << "Interactive testing mode not yet implemented." << std::endl;
}

void InteractiveSimulator::handleDelete(const std::vector<std::string> &tokens)
{
    if (tokens.size() != 2)
    {
        std::cout << "Usage: delete <gate_name>" << std::endl;
        return;
    }

    std::string gateName = tokens[1];
    auto it = gates.find(gateName);
    if (it == gates.end())
    {
        std::cout << "Gate '" << gateName << "' not found." << std::endl;
        return;
    }

    gates.erase(it);
    std::cout << "✓ Deleted gate '" << gateName << "'" << std::endl;
}