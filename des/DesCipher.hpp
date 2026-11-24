#ifndef DES_CIPHER_HPP
#define DES_CIPHER_HPP

#include <vector>
#include <stdexcept>

/*
C++ has no standard-library DES implementation, so this header wraps a
small, public-domain DES/Triple-DES implementation (D3DES by Richard
Outerbridge, vendored in des/d3des.c/.h) behind two functions,
`Des::encrypt` and `Des::decrypt`, that take a key and a byte buffer and
return a byte buffer.

You are not expected to modify this file. Your Chain of Responsibility
handlers should call Des::encrypt/Des::decrypt directly; everything else
(choosing single/double/triple-length DES based on key size, ECB block
processing, PKCS#7 padding) is handled here.
*/
namespace Des
{
    // Encrypts plaintext under key using DES. key.size() must be 8, 16, or
    // 24 bytes, selecting single-length DES, double-length (2-key) Triple
    // DES, or triple-length (3-key) Triple DES respectively - these are
    // exactly the "valid length (8, 16, 24)" key sizes the lab asks the
    // KeyHandler to validate. Pads plaintext with PKCS#7 padding so the
    // result is always a multiple of 8 bytes.
    // Throws std::invalid_argument if key.size() is not 8, 16, or 24.
    std::vector<unsigned char> encrypt(const std::vector<unsigned char> &key,
                                        const std::vector<unsigned char> &plaintext);

    // Decrypts ciphertext under key using DES (see encrypt() for key sizing)
    // and strips the PKCS#7 padding that encrypt() added.
    // Throws std::invalid_argument if key.size() is not 8, 16, or 24, or if
    // ciphertext.size() is not a non-zero multiple of 8.
    // Throws std::runtime_error if the decrypted padding is invalid - this
    // almost always means the wrong key was used.
    std::vector<unsigned char> decrypt(const std::vector<unsigned char> &key,
                                        const std::vector<unsigned char> &ciphertext);
}

#endif // DES_CIPHER_HPP
