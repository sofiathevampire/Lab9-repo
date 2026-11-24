#include "DesCipher.hpp"
#include "d3des.h"

namespace
{
    constexpr size_t BLOCK_SIZE = 8;

    // Loads the internal D3DES key register(s) for the given key, picking
    // single/double/triple-length DES based on key.size(). `mode` is EN0 or
    // DE1 from d3des.h.
    void setupKey(const std::vector<unsigned char> &key, short mode)
    {
        if (key.size() == 8)
        {
            deskey(const_cast<unsigned char *>(key.data()), mode);
        }
        else if (key.size() == 16)
        {
            des2key(const_cast<unsigned char *>(key.data()), mode);
        }
        else if (key.size() == 24)
        {
            des3key(const_cast<unsigned char *>(key.data()), mode);
        }
        else
        {
            throw std::invalid_argument(
                "DES key must be 8, 16, or 24 bytes long (got " +
                std::to_string(key.size()) + ")");
        }
    }

    // Runs one 8-byte block through the key register(s) loaded by
    // setupKey(). Single-length DES uses des(); double/triple-length use
    // Ddes() (which, after des2key/des3key, chains KnL/KnR/Kn3 correctly
    // for both cases).
    void processBlock(const std::vector<unsigned char> &key,
                       unsigned char *block, unsigned char *out)
    {
        if (key.size() == 8)
        {
            des(block, out);
        }
        else
        {
            Ddes(block, out);
        }
    }
}

namespace Des
{
    std::vector<unsigned char> encrypt(const std::vector<unsigned char> &key,
                                        const std::vector<unsigned char> &plaintext)
    {
        setupKey(key, EN0);

        // PKCS#7 padding: pad with N bytes of value N, where N is the
        // number of bytes needed to reach the next multiple of 8 (always
        // between 1 and 8, even if plaintext is already block-aligned, so
        // decrypt() can always find and strip the padding unambiguously).
        size_t padLen = BLOCK_SIZE - (plaintext.size() % BLOCK_SIZE);
        std::vector<unsigned char> padded = plaintext;
        padded.insert(padded.end(), padLen, static_cast<unsigned char>(padLen));

        std::vector<unsigned char> ciphertext(padded.size());
        for (size_t i = 0; i < padded.size(); i += BLOCK_SIZE)
        {
            processBlock(key, &padded[i], &ciphertext[i]);
        }
        return ciphertext;
    }

    std::vector<unsigned char> decrypt(const std::vector<unsigned char> &key,
                                        const std::vector<unsigned char> &ciphertext)
    {
        if (ciphertext.empty() || ciphertext.size() % BLOCK_SIZE != 0)
        {
            throw std::invalid_argument(
                "DES ciphertext length must be a non-zero multiple of 8 bytes (got " +
                std::to_string(ciphertext.size()) + ")");
        }

        setupKey(key, DE1);

        std::vector<unsigned char> padded(ciphertext.size());
        std::vector<unsigned char> block = ciphertext; // mutable copy for processBlock
        for (size_t i = 0; i < block.size(); i += BLOCK_SIZE)
        {
            processBlock(key, &block[i], &padded[i]);
        }

        unsigned char padLen = padded.back();
        if (padLen == 0 || padLen > BLOCK_SIZE || padLen > padded.size())
        {
            throw std::runtime_error(
                "Invalid PKCS#7 padding after decryption - this usually means "
                "the wrong key was used.");
        }
        for (size_t i = padded.size() - padLen; i < padded.size(); i++)
        {
            if (padded[i] != padLen)
            {
                throw std::runtime_error(
                    "Invalid PKCS#7 padding after decryption - this usually means "
                    "the wrong key was used.");
            }
        }

        padded.resize(padded.size() - padLen);
        return padded;
    }
}
