#pragma once

#include <string>

class LoggingService
{
public:
    LoggingService(const std::string& filename);
    void run();

private:
    void write_message(const std::string& msg);

    std::string filename_;
};
