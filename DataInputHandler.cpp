#include "DataInputHandler.hpp"
#include <iostream>

// Checks whether any input data exists
bool DataInputHandler::handle(Request& request) {
    if(!request.dataInput.has_value()) {
        std::cout << "Error, no input data was given" << std::endl;
        return false;
    }

// If there is input data, but its all empty, it should also return false
    if(request.dataInput->empty()) {
        std::cout << "Error, input data is empty" << std::endl;
        return false;
    }

    // If we are decrypting, and if the user submitted raw text instead of a file
    if(request.mode == CryptoMode::DE && !request.inputFile.has_value()) {
        
        // Since hex stores two characters per byte in the form A1, FF, etc
        // so this means the total number of characters always needs to be even
        // If not, there is an error.
        if(request.dataInput->size() % 2 != 0) {
            std::cout << "Error, invalid hexadecimal length" << std::endl;
            return false;
        }

        // Stores all of the bytes that were converted
        std::vector<unsigned char> bytes;

        // Processes the hex characters two at a time
        // So if the input is AB12C3, then it does AB, then 12, then C3
        for(int i = 0; i < request.dataInput->size(); i += 2) {
            // Holds the first hex character
            char high = request.dataInput.value()[i];
            // Holds the second hex character
            char low = request.dataInput.value()[i + 1];

            // Stores the decimal value of the characters
            int highValue;
            int lowValue;

            // Converts hex digits between 0 and 9
            if(high >= '0' && high <= '9') {
                highValue = high - '0';
            }

            // Also converts hex letters between A and F
            else if(high >= 'A' && high <= 'F') {
                highValue = high - 'A' + 10;
            }
            else if(high >= 'a' && high <= 'f') {
                highValue = high - 'a' + 10;
            }
            // If there's anything else, it's not hex, its invalid
            else {
                std::cout
                    << "Error, invalid hexadecimal input" << std::endl;
                return false;
            }

            // Does the same thing for the second hexadecimal character
            if(low >= '0' && low <= '9') {
                lowValue = low - '0';
            }
            else if(low >= 'A' && low <= 'F') {
                lowValue = low - 'A' + 10;
            }
            else if(low >= 'a' && low <= 'f') {
                lowValue = low - 'a' + 10;
            } else {
                std::cout
                    << "Error, invalid hexadecimal input" << std::endl;
                return false;
            }

            // Afterwards, it combines the two hex digits into a single byte
            // ex. A1 means A = 10, 1 = 1, so (10*16) + 1 gives 161
            // Adds it to the vector of bytes
            bytes.push_back(highValue * 16 + lowValue);
        }

        // Replaces the hex text with the bytes we just converted
        request.dataInput = bytes;
    }

    // If the mode is Decryption, check to see if divisible by 8
    // Because decryption works on blocks of 8 bytes
    if(request.mode == CryptoMode::DE && request.dataInput->size() % 8 != 0) {
        std::cout << "Error, invalid ciphertext length" << std::endl;
        return false;
    }

    // If all the validation passed, we can send it to the next handler
    return callNext(request);
}