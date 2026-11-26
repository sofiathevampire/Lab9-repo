#include "Crypto.hpp"
#include "KeyHandler.hpp"
#include "InputFileHandler.hpp"
#include "DataInputHandler.hpp"
#include "EncryptionHandler.hpp"
#include "DecryptionHandler.hpp"
#include "OutputHandler.hpp"
  
// Created by Nio
Crypto::Crypto() {
    // A handler to validate keys
    Handler* enKey = new KeyHandler();

    // A handler to deal with file inputs
    Handler* enFile = new InputFileHandler();

    // A handler to deal with data validation
    Handler* enData = new DataInputHandler();

    // A handler to deal with encryption
    Handler* enEncrypt = new EncryptionHandler();

    // A handler to deal with output
    Handler* enOutput = new OutputHandler();

    // Connects each of the handlers to each other
    // so that the request gets sent down this chain
    // as we go along.
    enKey->setNext(enFile);
    enFile->setNext(enData);
    enData->setNext(enEncrypt);
    enEncrypt->setNext(enOutput);

    // Keeps track of where the chain starts
    encryptionStartHandler = enKey;

    // Creates a decryption handler for validating keys
    Handler* deKey = new KeyHandler();
    Handler* deFile = new InputFileHandler();
    Handler* deData = new DataInputHandler();
    Handler* deDecrypt = new DecryptionHandler();
    Handler* deOutput = new OutputHandler();

    // Connects each of the handlers in the chain
    deKey->setNext(deFile);
    deFile->setNext(deData);
    deData->setNext(deDecrypt);
    deDecrypt->setNext(deOutput);

    // Keeps track of where it starts
    decryptionStartHandler = deKey;

    // Stores all of the handlers
    ownedHandlers = {
        enKey, enFile, enData, enEncrypt, enOutput,
        deKey, deFile, deData, deDecrypt, deOutput
    };
}

// The destructor
Crypto::~Crypto() {
    for (Handler* handler : ownedHandlers) {
        delete handler;
    } // deletes all of the handlers to free the memory when we are done
}

// Decides if we should encrypt or decrypt
bool Crypto::executeRequest(Request &request) {

    // If they requested encryption, then perform encryption, otherwise
    // perform decryption.
    if (request.mode == CryptoMode::EN) {
        return encryptionStartHandler->handle(request);
    }

    return decryptionStartHandler->handle(request);
}
