#include "GateFactory.h"
#include <stdexcept>

std::shared_ptr<Gate> GateFactory::createGate(GateType type, const std::string &gateLabel)
{
    if (!isValidGateType(type))
    {
        throw std::invalid_argument("Invalid gate type");
    }
    else if (type == GateType::And)
    {
        return std::make_shared<ANDGate>(gateLabel);
    }
    else if (type == GateType::Or)
    {
        return std::make_shared<ORGate>(gateLabel);
    }
    else if (type == GateType::Not)
    {
        return std::make_shared<NOTGate>(gateLabel);
    }
    else if (type == GateType::Nor)
    {
        return std::make_shared<NORGate>(gateLabel);
    }
    else if (type == GateType::Nand)
    {
        return std::make_shared<NANDGate>(gateLabel);
    }
    else if (type == GateType::Xor)
    {
        return std::make_shared<XORGate>(gateLabel);
    }
    else if (type == GateType::Xnor)
    {
        return std::make_shared<XNORGate>(gateLabel);
    }
    else if (type == GateType::Buffer)
    {
        return std::make_shared<BufferGate>(gateLabel);
    }
    else
    {
        throw std::invalid_argument("Invalid gate type");
    }
}

bool GateFactory::isValidGateType(GateType type)
{
    if (type == GateType::And || type == GateType::Or || type == GateType::Not || type == GateType::Nor || type == GateType::Nand || type == GateType::Xor || type == GateType::Xnor || type == GateType::Buffer)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<GateType> GateFactory::getSupportedTypes()
{
    return {
        GateType::And, GateType::Or, GateType::Not, GateType::Nor,
        GateType::Nand, GateType::Xor, GateType::Xnor, GateType::Buffer};
}

std::string GateFactory::getGateTypeName(GateType type)
{
    switch (type)
    {
    case GateType::And:
        return "AND";
    case GateType::Or:
        return "OR";
    case GateType::Not:
        return "NOT";
    case GateType::Nor:
        return "NOR";
    case GateType::Nand:
        return "NAND";
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
