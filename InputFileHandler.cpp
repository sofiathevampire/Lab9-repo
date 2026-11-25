#include "InputFileHandler.hpp"
#include <fstream>
#include <iostream>

bool InputFileHandler::handle(Request& request) {
    if(!request.inputFile.has_value()) {
        return callNext(request);
    }


    std::ifstream inputFile(*request.inputFile, std::ios::binary);


    if(!inputFile) {
        std::cout << "There was an error opening the input file." << std::endl;
        return false;
    }

    std::vector<unsigned char> fileData;
    char byte;

    while(inputFile.get(byte)) {
        fileData.push_back(byte);
    }

    request.dataInput = fileData;
    return callNext(request);
}
