#include "EncryptionHandler.hpp"
#include "des/DesCipher.hpp"

#include <iostream>

bool EncryptionHandler::handle(Request& request) {
    // Stores the key as bytes
    std::vector<unsigned char> keyBytes;

    // Copies every character from the key string into the byte vector.
    for(int i = 0; i < request.key.size(); i++){
        keyBytes.push_back(request.key[i]);
    }

    // Tries to do encryption
    try {
        // Encrypts the input data using the key
        request.result = Des::encrypt(keyBytes, *request.dataInput);
    } catch(...) {
        std::cout << "Error during encryption." << std::endl;
        return false;
    }

    // Otherwise, continue on
    return callNext(request);
}