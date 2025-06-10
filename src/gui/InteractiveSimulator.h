#pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include "core/BasicGates.h"
#include "core/GateFactory.h"

class InteractiveSimulator
{
private:
    std::map<std::string, std::shared_ptr<Gate>> gates;
    bool running;

public:
    // Constructor
    InteractiveSimulator() : running(true) {}

    // Public interface methods (called by main)
    void displayWelcomeMessage();
    bool isRunning() const { return running; }
    void displayPrompts();
    std::string getUserInput();
    void executeUserInput(const std::string &input) { executeCommand(input); }
    void cleanUp();

    // Command execution
    void executeCommand(const std::string &input);

private:
    // Command parsing and validation
    std::vector<std::string> parseInput(const std::string &input);
    bool validateCommand(const std::vector<std::string> &tokens); // Fixed parameter type
    GateType parseGateType(const std::string &typeStr);           // Missing declaration

    // Command handlers
    void handleCreate(const std::vector<std::string> &tokens);
    void handleConnect(const std::vector<std::string> &tokens);
    void handleSimulate(const std::vector<std::string> &tokens);
    void handleRun(const std::vector<std::string> &tokens);
    void handleStop(const std::vector<std::string> &tokens);
    void handleReset(const std::vector<std::string> &tokens);
    void handleSave(const std::vector<std::string> &tokens);
    void handleLoad(const std::vector<std::string> &tokens);
    void handleHelp(const std::vector<std::string> &tokens);
    void handleExit(const std::vector<std::string> &tokens);
    void handleClear(const std::vector<std::string> &tokens);
    void handleList(const std::vector<std::string> &tokens);
    void handleSet(const std::vector<std::string> &tokens);
    void handleEval(const std::vector<std::string> &tokens);
    void handleInfo(const std::vector<std::string> &tokens);
    void handleTable(const std::vector<std::string> &tokens);
    void handleTest(const std::vector<std::string> &tokens);
    void handleDelete(const std::vector<std::string> &tokens);
    std::string getGateTypeName(GateType type);
};