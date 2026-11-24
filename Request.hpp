#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <optional>
#include <string>
#include <vector>

// Lists the various modes that the Crypto application can run in.
enum class CryptoMode
{
    EN, // Encryption mode
    DE  // Decryption mode
};

inline std::string toString(CryptoMode mode)
{
    return mode == CryptoMode::EN ? "en" : "de";
}

/*
The request object represents a request to either encrypt or decrypt
certain data. The request object comes with certain accompanying
configuration options as well as a field that holds the result. The
attributes are:
    - mode: CryptoMode::EN to encrypt, CryptoMode::DE to decrypt
    - dataInput: The raw byte data that needs to be encrypted or decrypted.
      This is std::nullopt if the data is coming in from a file instead.
    - inputFile: The path to the file that contains the data to be
      encrypted or decrypted. This is std::nullopt if the data is not
      coming from a file and was provided directly via dataInput.
    - output: The requested method of output. At the moment the program
      supports printing to the console ("print") or writing to another
      file (any other value is treated as a file path).
    - key: The key value to use for encryption or decryption.
    - result: Placeholder for the result of the encryption/decryption.
      This does not come in with the request; handlers fill it in.
*/
struct Request
{
    CryptoMode mode = CryptoMode::EN;
    std::optional<std::vector<unsigned char>> dataInput;
    std::optional<std::string> inputFile;
    std::string output = "print";
    std::string key;
    std::vector<unsigned char> result;
};

inline std::ostream &operator<<(std::ostream &os, const Request &request)
{
    os << "Request: Mode: " << toString(request.mode)
       << ", Data: " << (request.dataInput ? "<" + std::to_string(request.dataInput->size()) + " bytes>" : "None")
       << ", Input file: " << (request.inputFile ? *request.inputFile : "None")
       << ", Output: " << request.output
       << ", Key: " << request.key;
    return os;
}

#endif // REQUEST_HPP
