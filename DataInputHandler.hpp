#include "Handler.hpp"
#pragma once

class DataInputHandler : public Handler {
    public:
    bool handle(Request& request) override;
};