#pragma once
#include "Handler.hpp"

class InputFileHandler : public Handler {
    public:
    bool handle(Request& request) override;
};