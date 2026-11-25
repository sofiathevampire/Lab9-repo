#include "DataInputHandler.hpp"
#include <iostream>

bool DataInputHandler::handle(Request& request) {
    if(!request.dataInput.has_value()) {
        std::cout << "Error, no input data was given" << std::endl;
        return false;
    }

    if(request.dataInput->empty()) {
        std::cout << "Error, input data is empty" << std::endl;
        return false;
    }

    if (request.mode == CryptoMode::DE &&
    !request.inputFile.has_value()) {

        const auto& input = *request.dataInput;

        if (input.size() % 2 !=0) {
            std::cout << "Eroor, invalid hexadecimal length"
            << std::endl;
            return false;
        }

        auto hexValue = [](unsigned char c) -> int {
            if (c >= '0' && c <= '9')
            return c - '0';

            if (c >= 'a' && c <= 'f')
            return c - 'a' + 10;

            if (c >= 'A' && c <= 'F')
            return c - 'A' + 10;

            return -1;

        };

        std::vector<unsigned char> bytes;

        for (std::size_t i = 0; i < input.size(); i +=2) {
            int high = hexValue(input[i]);
            int low = hexValue(input[i + 1]);

            if (high < 0 || low < 0) {
                std::cout << "Error, invalid hexadecimal input"
                << std::endl;
                return false;
            }

            bytes.push_back(
                static_cast<unsigned char>(high * 16 + low)
            );
        }

        request.dataInput = bytes;
    }

    if(request.mode == CryptoMode::DE &&
    request.dataInput->size() % 8 != 0) {
        std::cout <<"Error, invalid ciphertext length" << std::endl;
        return false;
    }

    return callNext(request);
}