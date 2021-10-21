
#include "LoggingService.h"

#include <iostream>
#include <stdexcept>
#include <string>

int main()
{
    try
    {
        LoggingService logging_service("application.log");
        logging_service.run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
    }
}
