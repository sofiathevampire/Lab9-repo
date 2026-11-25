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

    return callNext(request);
}