#include "KeyHandler.hpp"
#include <iostream>

bool KeyHandler::handle(Request& request) {
    int keyLength = request.key.length();

    if(keyLength != 8 && keyLength != 16 && keyLength != 24) {
        std::cout << "Error, the key length has to be either 8, 16, or 24" << std::endl;
        return false;
    }

    return callNext(request);
}