#include "OutputHandler.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

/** 
 * Displays output if the user wants it printed,
 * Otherwise, if they want it saved, write it to a file.
 */
bool OutputHandler::handle(Request& request) {
    // If they want the result printed on the screen
    if(request.output == "print") {
        // If we're encrypting, show the result in hexadecimal; we don't want to show binary
        if(request.mode == CryptoMode::EN) {

            // Loops through every encrypted byte
            // Prints each byte as a 2 digit hex value; ex. 161 becomes A1
            for(int i = 0; i < request.result.size(); i++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0')
                << (int)request.result[i];
            }
// Switch back from hexadecimal mode to decimal mode
            std::cout << std::dec;
        }

        // If we're decrypting, then show the result as text
        else {
            // loop through each byte in the result
            for(int i = 0; i < request.result.size(); i++) {
                std::cout << (char)request.result[i]; // convert each byte to a character, print it
            }
        }
        std::cout << std::endl;
    }

    // Otherwise, if we just want to save to a file
    else {
        std::string filename = request.output; // start with the filename given by the user

        // Encrypted files should end in .bin, otherwise, regular decrypted text files are in txt
        if(request.mode == CryptoMode::EN) {
            filename += ".bin";
        } else {
            filename += ".txt";
        }
// Opens the output file
        std::ofstream file(filename, std::ios::binary
        );
// If the file didn't open correctly
        if(!file) {
            std::cout << "Error opening output file." << std::endl;
            return false;
        }

        // Loops through every byte in the result
        for(int i = 0; i < request.result.size(); i++) {
            file.put(request.result[i]); // Writes the current byte into the file
        }

        // If writing to the file failed
        if(!file) {
            std::cout << "Error writing output file." << std::endl;
            return false;
        }
    }

    return callNext(request);
}