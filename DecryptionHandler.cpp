#include "DecryptionHandler.hpp"
#include "DesCipher.hpp"
#include <iostream>
#include <stdexcept>

bool DecryptionHandler::handle(Request& request) {
    std::vector<unsigned char> keyBytes(
        request.key.begin(),
        request.key.end()
    );

    try {
        request.result = Des::decrypt(
            keyBytes,
            *request.dataInput
        );
    }
    catch (const std::runtime_error& error) {
        std::cerr <<"Decryption error: "
        <<error.what() << std::endl;
        return false;
    }
    catch (const std::invalid_argument& error) {
        std::cerr << "Decryption error: "
        << error.what() << std::endl;
        return false;
    }

    return callNext(request);
}