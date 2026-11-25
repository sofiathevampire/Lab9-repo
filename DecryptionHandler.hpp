#pragma once
#include "Handler.hpp"

class DecryptionHandler : public Handler {
    public:  
    bool handle(Request& request) override;
};