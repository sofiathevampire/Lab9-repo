#include "OutputHandler.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>

bool OutputHandler::handle(Request& request) {
    if (request.output == "print") {
        if (request.mode == CryptoMode::EN) {
            for (unsigned char byte : request.result) {
                std::cout << std::hex
                << std::setw(2)
                << std::setfill('0')
                << static_cast<int>(byte);
            }

            std::cout << std::dec << std::setfill(' ');
        }
        else {
            for (unsigned char byte : request.result) {
                std::cout << static_cast<char>(byte);
            }
        }
        std::cout << std::endl;
    }
    else {
        std::filesystem::path path(request.output);

        if (request.mode == CryptoMode::EN) {
            path.replace_extension(".bin");
        }
        else {
            path.replace_extension(".txt");
        }
        
        std::ofstream file(path, std::ios::binary);

        if (!file) {
            std::cerr <<"Error, cannot open output file"
            << std::endl;
            return false;
        }

        file.write(
            reinterpret_cast<const char*>(request.result.data()),
            request.result.size()
        );

        if (!file) {
            std::cerr <<"Error, cannot write output file"
            << std::endl;
            return false;
        }
    }

    return callNext(request);
}