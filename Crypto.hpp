#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include "Request.hpp"
#include "Handler.hpp"
#include <vector>

class Crypto
{
  private:
  Handler* encryptionStartHandler;
  Handler* decryptionStartHandler;
  std::vector<Handler*> ownedHandlers;

public:
    Crypto();
    ~Crypto();

    Crypto(const Crypto&) = delete;
    Crypto& operator=(const Crypto&) = delete;

    bool executeRequest(Request &request);
};

#endif 
