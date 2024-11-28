#include "arguments.h"
#include "server.h"
#include "rw.h"
#include <iostream>

void go(Parser &parser)
{
    Server server(
        parser.getAddress(), parser.getPort(),
        readUsers(parser.getPathToUsers()));
    server.startup();
    while (true)
    {
        try
        {
            server.connect();
            server.authentication();
            server.averange();
        }
        catch (const UnknownError &error)
        {
            if (error.isCritical())
                throw error;
            std::cerr << error.what();
            writeLog(parser.getPathToLog(), error);
        }
    }
}

int main(int argc, char *argv[])
{
    Parser parser;
    try
    {
        parser.parse(argc, argv);
        go(parser); // запуск сервера с аргументами
    }
    catch (const UnknownError &error)
    {
        std::cerr << error.what();
        writeLog(parser.getPathToLog(), error);
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred.\n";
        return 1;
    }

    return 0;
}
