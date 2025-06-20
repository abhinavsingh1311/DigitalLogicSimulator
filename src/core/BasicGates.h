#pragma once
#include "Gate.h"
#include <stdexcept>

class ANDGate : public Gate
{
public:
    ANDGate(const std::string& gateLabel);
    void evaluate() override;
};

class ORGate : public Gate
{
public:
    ORGate(const std::string& gateLabel = "");
    void evaluate() override;
};

class NOTGate : public Gate
{
public:
    NOTGate(const std::string& gateLabel = "");
    void evaluate() override;

private:
    void addInputCountRestriction() {}
};

class NANDGate : public Gate
{
public:
    NANDGate(const std::string& gateLabel = "");
    void evaluate() override;
};

class NORGate : public Gate
{
public:
    NORGate(const std::string& gateLabel = "");
    void evaluate() override;
};

class XORGate : public Gate
{
public:
    XORGate(const std::string& gateLabel = "");
    void evaluate() override;
};

class XNORGate : public Gate
{
public:
    XNORGate(const std::string& gateLabel = "");
    void evaluate() override;
};

class BufferGate : public Gate
{
public:
    BufferGate(const std::string& gateLabel = "");
    void evaluate() override;
};
