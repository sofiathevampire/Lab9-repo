#pragma once
#include "Handler.hpp"

class KeyHandler : public Handler {
    public:
    bool handle(Request& request) override;
};
