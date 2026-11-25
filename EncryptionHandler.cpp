#include "EncryptionHandler.hpp"
#include "DesCipher.hpp"
#include <iostream>

bool EncryptionHandler::handle(Request& request) {
    std::vector<unsigned char> keyBytes(
        request.key.begin(),
        request.key.end()
    );

    try {
        request.result = Des::encrypt(
            keyBytes,
            *request.dataInput
        );
    }
    catch (const std::invalid_argument& error) {
        std::cerr << "Encryption error: "
        << error.what()  << std::endl;
        return false;
    }

    return callNext(request);
}