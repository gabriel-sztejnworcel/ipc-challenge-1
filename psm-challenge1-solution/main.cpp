
#include <Windows.h>

#include <iostream>
#include <stdexcept>
#include <string>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
    try
    {
        wchar_t mailslot_name[] = L"\\\\.\\mailslot\\logging_service";

        HANDLE mailslot_client_handle = CreateFile(
            mailslot_name,
            GENERIC_WRITE,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr
        );

        if (mailslot_client_handle == INVALID_HANDLE_VALUE)
        {
            throw std::runtime_error(
                "CreateFile failed with error code "
                + std::to_string(GetLastError()));
        }

        std::cout << "[+] Connected to mailslot server" << std::endl;

        std::string str = "hello & Notepad.exe";
        DWORD bytes_written = 0;

        BOOL result = WriteFile(
            mailslot_client_handle,
            str.c_str(),
            str.length(),
            &bytes_written,
            nullptr
        );

        if (!result)
        {
            throw std::runtime_error(
                "WriteFile failed with error code "
                + std::to_string(GetLastError()));
        }

        /*while (true)
        {
            std::string str;
            std::getline(std::cin, str);

            DWORD bytes_written = 0;

            BOOL result = WriteFile(
                mailslot_client_handle,
                str.c_str(),
                str.length(),
                &bytes_written,
                nullptr
            );

            if (!result)
            {
                throw std::runtime_error(
                    "WriteFile failed with error code "
                    + std::to_string(GetLastError()));
            }
        }*/
    }
    catch (const std::exception& ex)
    {
        std::cerr << "ERROR: " << ex.what() << std::endl;
    }
}
