#include "CommandLineParser.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

void CommandLineParser::printHelp(const char *programName)
{
    std::cout
        << "Usage: " << programName << " [-h] [-s STRING] [-f FILE] [-o OUTPUT] [-m MODE] key\n\n"
        << "positional arguments:\n"
        << "  key                    The key to use when encrypting or decrypting. This\n"
        << "                         needs to be of length 8, 16 or 24\n\n"
        << "optional arguments:\n"
        << "  -h, --help             show this help message and exit\n"
        << "  -s STRING, --string STRING\n"
        << "                         The string that needs to be encrypted or decrypted\n"
        << "  -f FILE, --file FILE   The file that needs to be encrypted or decrypted\n"
        << "  -o OUTPUT, --output OUTPUT\n"
        << "                         The output of the program. This is 'print' by\n"
        << "                         default, but can be set to a file name as well.\n"
        << "  -m MODE, --mode MODE   The mode to run the program in. If 'en' (default)\n"
        << "                         then the program will encrypt, 'de' will cause the\n"
        << "                         program to decrypt\n";
}

Request CommandLineParser::parse(int argc, char *argv[])
{
    std::optional<std::string> key;
    std::optional<std::string> dataString;
    std::optional<std::string> inputFile;
    std::string output = "print";
    std::string mode = "en";

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        auto nextValue = [&](const std::string &flag) -> std::string
        {
            if (i + 1 >= argc)
            {
                std::cerr << "Error! " << flag << " expects a value.\n";
                std::exit(1);
            }
            return argv[++i];
        };

        if (arg == "-h" || arg == "--help")
        {
            printHelp(argv[0]);
            std::exit(0);
        }
        else if (arg == "-s" || arg == "--string")
        {
            dataString = nextValue(arg);
        }
        else if (arg == "-f" || arg == "--file")
        {
            inputFile = nextValue(arg);
        }
        else if (arg == "-o" || arg == "--output")
        {
            output = nextValue(arg);
        }
        else if (arg == "-m" || arg == "--mode")
        {
            mode = nextValue(arg);
        }
        else if (!arg.empty() && arg[0] == '-')
        {
            std::cerr << "Error! Unrecognized argument: " << arg << "\n";
            std::exit(1);
        }
        else if (!key.has_value())
        {
            key = arg;
        }
        else
        {
            std::cerr << "Error! Unexpected extra positional argument: " << arg << "\n";
            std::exit(1);
        }
    }

    if (!key.has_value())
    {
        std::cerr << "Error! Could not read arguments.\nThe 'key' positional argument is required.\n";
        std::exit(1);
    }
    if (mode != "en" && mode != "de")
    {
        std::cerr << "Error! Could not read arguments.\n'mode' must be 'en' or 'de' (got '" << mode << "').\n";
        std::exit(1);
    }

    Request request;
    request.mode = (mode == "en") ? CryptoMode::EN : CryptoMode::DE;
    if (dataString.has_value())
    {
        request.dataInput = std::vector<unsigned char>(dataString->begin(), dataString->end());
    }
    request.inputFile = inputFile;
    request.output = output;
    request.key = *key;

    std::cout << request << std::endl;
    return request;
}
