#include "stdafx.h"

#pragma region ErrorHandling
void PrintLastErrorText()
{

    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  dw,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                             (LPTSTR)&lpMsgBuf,
                             0, NULL);

    _tprintf(_T("%s"), (PTCHAR)lpMsgBuf);
    LocalFree(lpMsgBuf);
}
#pragma endregion
#pragma region Files
const int N = 100;

bool FileCopy(TCHAR* file1, TCHAR* file2)
{
    HANDLE h1 = CreateFile(file1,
                           GENERIC_READ,
                           0, NULL,
                           OPEN_EXISTING,
                           0, NULL);
    if(INVALID_HANDLE_VALUE == h1)
    {
        PrintLastErrorText();
        return false;
    }

    HANDLE h2 = CreateFile(file2,
                           GENERIC_WRITE,
                           0, NULL,
                           CREATE_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL);
    if(INVALID_HANDLE_VALUE == h2)
    {
        CloseHandle(h1);
        PrintLastErrorText();
        return false;
    }

    TCHAR buffer[N];
    DWORD Read;
    DWORD Writen;

    while(ReadFile(h1, buffer,
                   N * sizeof(TCHAR),
                   &Read, NULL)
          && Read)
    {
        if(!WriteFile(h2, buffer, Read, &Writen, NULL)
           || Read != Writen)
        {
            PrintLastErrorText();
            CloseHandle(h1);
            CloseHandle(h2);
            return false;
        }
    }
    if(Read)
    {
        PrintLastErrorText();
        CloseHandle(h1);
        CloseHandle(h2);
        return false;
    }

    CloseHandle(h1);
    CloseHandle(h2);
    return true;
}

bool ChangeFileTime(TCHAR* file)
{
    HANDLE h = CreateFile(file,
                          GENERIC_WRITE, 0,
                          NULL, OPEN_ALWAYS,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL);
    if(INVALID_HANDLE_VALUE == h)
    {
        PrintLastErrorText();
        return false;
    }
    if(ERROR_ALREADY_EXISTS != GetLastError())
    {
        CloseHandle(h);
        return true;
    }

    SYSTEMTIME stNow;
    GetSystemTime(&stNow);
    FILETIME ftNow;
    if(!SystemTimeToFileTime(&stNow, &ftNow))
    {
        CloseHandle(h);
        PrintLastErrorText();
        return false;
    }
    if(!SetFileTime(h, &ftNow, NULL, NULL))
    {
        CloseHandle(h);
        PrintLastErrorText();
        return false;
    }
    CloseHandle(h);
    return true;
}
#pragma endregion
