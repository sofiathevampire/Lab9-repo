#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include "Request.hpp"
#include "Handler.hpp"
#include <vector>

// Manages both encryption & decryption handler chains
class Crypto {
  private:
  // Handler #1 in the encryption chain
  Handler* encryptionStartHandler;

  // Handler #2: decryption chain
  Handler* decryptionStartHandler;

  // a vector of all the handlers that belong to Crypto
  std::vector<Handler*> ownedHandlers;

public:
    Crypto();
    ~Crypto();

    // Disables the copy constructor so you cannot copy
    // Crypto objects
    Crypto(const Crypto&) = delete;

    // Prevents assignment so you cannot assign
    // to another object, thereby making a copy
    Crypto& operator=(const Crypto&) = delete;

    // Conducts either encryption or decryption
    // depending on what the request is
    bool executeRequest(Request &request);
};

#endif 
