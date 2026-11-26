#include "DecryptionHandler.hpp"
#include "des/DesCipher.hpp"

#include <iostream>
#include <stdexcept>

// Handles a request for decryption
bool DecryptionHandler::handle(Request& request) {

    // Creates a vector that stores the key as bytes
    std::vector<unsigned char> keyBytes;

    // Loop through every character in the key string
    for(int i = 0; i < request.key.size(); i++) {
        keyBytes.push_back(request.key[i]);
        // copy current character into the vector
    }

    // Tries to perform the decryption using
    // the key bytes and the encypted input data
    // Stores the result of the decryption in the request object
    try {
        request.result = Des::decrypt(keyBytes,*request.dataInput);
    // Catch all possible errors and display this message
    } catch(...) {
        std::cout << "Error during decryption." << std::endl;
        return false;
    }

    return callNext(request);
}