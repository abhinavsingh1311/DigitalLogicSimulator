#include <string>
#include "gui/InteractiveSimulator.h"

int main()
{
    InteractiveSimulator simulator;
    simulator.displayWelcomeMessage();

    // Main loop
    while (simulator.isRunning())
    {
        simulator.displayPrompts();
        std::string userInput = simulator.getUserInput();
        simulator.executeUserInput(userInput);
    }

    simulator.cleanUp();
    return 0;
}