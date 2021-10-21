
#include "LoggingService.h"

#include <Windows.h>

#include <iostream>
#include <stdexcept>
#include <string>

#define BUFFER_SIZE 1024

LoggingService::LoggingService(const std::string& filename) : filename_(filename)
{

}

void LoggingService::run()
{
    wchar_t mailslot_name[] = L"\\\\.\\mailslot\\logging_service";

    HANDLE mailslot_server_handle = CreateMailslot(
        mailslot_name,
        BUFFER_SIZE,
        0,
        nullptr
    );

    if (mailslot_server_handle == INVALID_HANDLE_VALUE)
    {
        throw std::runtime_error(
            "CreateMailslot failed with error code " + std::to_string(GetLastError()));
    }

    std::cout << "[+] Logging service mailslot server created" << std::endl;

    while (true)
    {
        char buf[BUFFER_SIZE] = { 0 };
        DWORD bytes_read = 0;

        BOOL result = ReadFile(
            mailslot_server_handle,
            buf,
            BUFFER_SIZE - 1,
            &bytes_read,
            nullptr
        );

        if (!result)
        {
            auto last_error = GetLastError();

            if (last_error == ERROR_SEM_TIMEOUT)
            {
                Sleep(200);
                continue;
            }

            throw std::runtime_error(
                "ReadFile failed with error code " + std::to_string(last_error));
        }

        buf[bytes_read] = '\0';
        write_message(buf);
    }
}

void LoggingService::write_message(const std::string& msg)
{
    std::string cmd = "Powershell.exe -Command Add-Content -Path " + filename_ + " -Value " + msg;
    system(cmd.c_str());
}
