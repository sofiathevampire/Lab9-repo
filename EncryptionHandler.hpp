# pragma once
# include "Handler.hpp"

class EncryptionHandler : public Handler {
    public:
    bool handle(Request& request) override;
};