#pragma once
#include "Handler.hpp"

class OutputHandler : public Handler {
    public:
    bool handle(Request& request) override;
};