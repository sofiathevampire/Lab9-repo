#include "KeyHandler.hpp"
#include <iostream>

// Checks to see if the encryption key is valid
bool KeyHandler::handle(Request& request) {
    // Finds the number of characters in the key
    int keyLength = request.key.length();

    // Decryption only allows keys with a length of 8, 16, or 24 chars
    if(keyLength != 8 && keyLength != 16 && keyLength != 24) {
        std::cout << "Error, the key length has to be either 8, 16, or 24" << std::endl;
        return false;
    }

    return callNext(request);
}