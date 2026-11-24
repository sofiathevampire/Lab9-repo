#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include "Request.hpp"

/*
TODO: This is intentionally left as a stub - you design and implement the
Chain of Responsibility pattern yourself (the Handler base class/interface,
every concrete handler, and this Crypto class all need your own code).

This file is yours to edit. At minimum, Crypto needs to:

- In its constructor, build up two separate chains of handlers: one for
  encryption, one for decryption, and keep a pointer to the FIRST handler
  of each chain (add whatever member fields your Handler design needs -
  e.g. `Handler *encryptionStartHandler;`).
- In executeRequest(request), look at request.mode and kick off the first
  handler of the matching chain.
- In its destructor, delete every handler object it created in the
  constructor (this class owns them via raw `new`, matching the rest of
  this course - skipping the destructor leaks memory every time a Crypto
  object is destroyed).

See README.md for suggested handlers for each chain and how to call into
Des::encrypt/Des::decrypt (des/DesCipher.hpp) from your encryption/
decryption handlers.
*/
class Crypto
{
public:
    Crypto();
    ~Crypto();

    void executeRequest(Request &request);
};

#endif // CRYPTO_HPP
