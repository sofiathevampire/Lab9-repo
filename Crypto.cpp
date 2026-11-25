#include "Crypto.hpp"
#include "KeyHandler.hpp"
#include "InputFileHandler.hpp"
#include "DataInputHandler.hpp"
#include "EncryptionHandler.hpp"
#include "DecryptionHandler.hpp"
#include "OutputHandler.hpp"
  
// TODO: build your two handler chains here and store pointers to their
// first handlers (add member fields to Crypto.hpp for this).
Crypto::Crypto()
{
    Handler* enKey = new KeyHandler();
    Handler* enFile = new InputFileHandler();
    Handler* enData = new DataInputHandler();
    Handler* enEncrypt = new EncryptionHandler();
    Handler* enOutput = new OutputHandler();

    enKey->setNext(enFile);
    enFile->setNext(enData);
    enData->setNext(enEncrypt);
    enEncrypt->setNext(enOutput);

    encryptionStartHandler = enKey;

    Handler* deKey = new KeyHandler();
    Handler* deFile = new InputFileHandler();
    Handler* deData = new DataInputHandler();
    Handler* deDecrypt = new DecryptionHandler();
    Handler* deOutput = new OutputHandler();

    deKey->setNext(deFile);
    deFile->setNext(deData);
    deData->setNext(deDecrypt);
    deDecrypt->setNext(deOutput);

    decryptionStartHandler = deKey;

    ownedHandlers = {
        enKey, enFile, enData, enEncrypt, enOutput,
        deKey, deFile, deData, deDecrypt, deOutput
    };
}

// TODO: delete every handler you allocated with `new` in the constructor.
Crypto::~Crypto()
{
    for (Handler* handler : ownedHandlers) {
        delete handler;
    }
}

// TODO: dispatch to the encryption or decryption chain based on
// request.mode.
bool Crypto::executeRequest(Request &request)
{
    if (request.mode == CryptoMode::EN) {
        return encryptionStartHandler->handle(request);
    }

    return decryptionStartHandler->handle(request);
}
