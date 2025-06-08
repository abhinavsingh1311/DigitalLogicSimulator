#include <memory>
#include "Gate.h"
#include "BasicGates.h"

class GateFactory
{

public:
    //  Static method to create gates by type
    static std::shared_ptr<Gate> createGate(GateType type, const std::string &gateLabel = "");
    //  Handle invalid gate type request
    static bool isValidGateType(GateType type);
    static std::vector<GateType> getSupportedTypes();
    static std::string getGateTypeName(GateType type);
};