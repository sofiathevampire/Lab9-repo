#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include "Request.hpp"

// Implements a small, hand-rolled argument parser (there is no bundled
// CLI-argument library in this course's labs). Parses argv into a Request.
class CommandLineParser
{
public:
    // Parses argv into a Request. If something goes wrong with the
    // provided arguments, prints an error message and exits the
    // application.
    static Request parse(int argc, char *argv[]);

private:
    static void printHelp(const char *programName);
};

#endif // COMMANDLINEPARSER_HPP
