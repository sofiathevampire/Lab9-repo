#include "InputFileHandler.hpp"
#include <fstream>
#include <iostream>

// Handles loading data from a file
bool InputFileHandler::handle(Request& request) {
    // Checks if the user provided a file;
    // If they did not provide a file, then we can move on to the next handler
    if(!request.inputFile.has_value()) {
        return callNext(request);
    }

    // Opens the file in binary mode
    std::ifstream inputFile(*request.inputFile, std::ios::binary);

    // If it failed, print error msg
    if(!inputFile) {
        std::cout << "There was an error opening the input file." << std::endl;
        return false;
    }

    // Stores every byte read from the file
    std::vector<unsigned char> fileData;
    char byte;

    // Reads the file one byte at a time 
    while(inputFile.get(byte)) {
        fileData.push_back(byte); // Adds the current byte to the vector
    }

    // Stores the file data inside the request object
    request.dataInput = fileData;
    return callNext(request);
}
