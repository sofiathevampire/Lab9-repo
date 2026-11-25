#include "CommandLineParser.hpp"
#include "Crypto.hpp"
#include "Request.hpp"

int main(int argc, char *argv[])
{
    Request request = CommandLineParser::parse(argc, argv);

    Crypto crypto;

    if (!crypto.executeRequest(request)) {
        return 1;
    }
    
    return 0;
}
