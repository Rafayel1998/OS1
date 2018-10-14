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

    _tprintf(_T("%s"), lpMsgBuf);
    LocalFree(lpMsgBuf);
}
#pragma endregion

#pragma region Files
const DWORD N = 64;
const DWORD bigN = 1024;

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
    DWORD Written;

    while(ReadFile(h1, buffer,
                   N, &Read, NULL)
          && Read)
    {
        if(!WriteFile(h2, buffer, Read, &Written, NULL)
           || Read != Written)
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

bool FileReverseCopy(TCHAR* file1, TCHAR* file2)
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
                           FILE_APPEND_DATA,
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
    DWORD Read = N;
    DWORD Written;
    DWORD CurrPtr = SetFilePointer(h1, 0, NULL, FILE_END);
    DWORD ToRead = N;

    ///This doesn't work, but I don't know why.
    ///Seems like SetFilePointer doesn't work proprly
    /*while(ReadFile(h1, buffer, N, &Read, NULL) && Read)
    {
        int count = Read / sizeof(TCHAR);
        for(int i = 0; 2 * i < count; i++)
        {
            TCHAR tmp = buffer[i];
            buffer[i] = buffer[count - i - 1];
            buffer[count - i - 1] = tmp;
        }

        if(INVALID_SET_FILE_POINTER == SetFilePointer(h2, 0, NULL, FILE_BEGIN))
        {
            PrintLastErrorText();
            CloseHandle(h1);
            CloseHandle(h2);
            return false;
        }
        if(!WriteFile(h2, buffer, Read, &Written, NULL)
           || Read != Written)
        {
            PrintLastErrorText();
            CloseHandle(h1);
            CloseHandle(h2);
            return false;
        }
    }*/
    while(CurrPtr)
    {
        if(CurrPtr < Read)
            CurrPtr = SetFilePointer(h1, 0, NULL, FILE_BEGIN);
        else
            CurrPtr = SetFilePointer(h1, 0 - N, NULL, FILE_CURRENT);
        if(INVALID_SET_FILE_POINTER == CurrPtr)
        {
            PrintLastErrorText();
            CloseHandle(h1);
            CloseHandle(h2);
            return false;
        }
        if(!ReadFile(h1, buffer, ToRead, &Read, NULL))
        {
            PrintLastErrorText();
            CloseHandle(h1);
            CloseHandle(h2);
            return false;
        }
        if(INVALID_SET_FILE_POINTER == SetFilePointer(h1, 0 - Read, NULL, FILE_CURRENT))
        {
            PrintLastErrorText();
            CloseHandle(h1);
            CloseHandle(h2);
            return false;
        }
        int count = Read / sizeof(TCHAR);
        for(int i = 0; 2 * i < count; i++)
        {
            TCHAR tmp = buffer[i];
            buffer[i] = buffer[count - i - 1];
            buffer[count - i - 1] = tmp;
        }

        if(!WriteFile(h2, buffer, Read, &Written, NULL)
           || Read != Written)
        {
            PrintLastErrorText();
            CloseHandle(h1);
            CloseHandle(h2);
            return false;
        }
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

bool CopyHandles(HANDLE h1, HANDLE h2)
{
    DWORD read = -1, write;
    TCHAR buffer[N];
    while(ReadFile(h1, buffer, N, &read, NULL) && read)
    {
        if(!WriteFile(h2, buffer, read, &write, NULL) || read != write)
        {
            PrintLastErrorText();
            return false;
        }
    }
    if(read)
    {
        PrintLastErrorText();
        return false;
    }
    return true;
}

bool FromFileToOutput(TCHAR* FileName)
{
    HANDLE h1 = CreateFile(FileName,
                           GENERIC_READ,
                           0, NULL,
                           OPEN_EXISTING,
                           0, NULL);
    if(INVALID_HANDLE_VALUE == h1)
    {
        PrintLastErrorText();
        return false;
    }
    HANDLE h2 = GetStdHandle(STD_OUTPUT_HANDLE);
    if(INVALID_HANDLE_VALUE == h2)
    {
        PrintLastErrorText();
        CloseHandle(h1);
        return false;
    }
    if(!CopyHandles(h1, h2))
    {
        PrintLastErrorText();
        CloseHandle(h1);
    }
    CloseHandle(h1);
    return true;
}

bool FromInputToFile(TCHAR* FileName)
{
    HANDLE h1 = GetStdHandle(STD_INPUT_HANDLE);
    if(INVALID_HANDLE_VALUE == h1)
    {
        PrintLastErrorText();
        return false;
    }

    HANDLE h2 = CreateFile(FileName,
                           GENERIC_WRITE,
                           0, NULL,
                           OPEN_ALWAYS,
                           0, NULL);
    if(INVALID_HANDLE_VALUE == h2)
    {
        PrintLastErrorText();
        CloseHandle(h2);
        return false;
    }

    if(!CopyHandles(h1, h2))
    {
        PrintLastErrorText();
        CloseHandle(h2);
    }
    CloseHandle(h2);
    return true;
}

bool FromInputToOutput()
{
    HANDLE h1 = GetStdHandle(STD_INPUT_HANDLE);
    if(INVALID_HANDLE_VALUE == h1)
    {
        PrintLastErrorText();
        return false;
    }

    HANDLE h2 = GetStdHandle(STD_OUTPUT_HANDLE);
    if(INVALID_HANDLE_VALUE == h2)
    {
        PrintLastErrorText();
        return false;
    }

    if(!CopyHandles(h1, h2))
        PrintLastErrorText();
    return true;
}

bool FromFileToConsole(TCHAR* FileName)
{
    HANDLE h1 = CreateFile(FileName,
                           GENERIC_READ,
                           0, NULL,
                           OPEN_EXISTING,
                           0, NULL);
    if(INVALID_HANDLE_VALUE == h1)
    {
        PrintLastErrorText();
        return false;
    }
    HANDLE h2 = CreateFile(_T("CONOUT$"),
                           GENERIC_WRITE,
                           0, NULL,
                           OPEN_EXISTING,
                           0, NULL);
    if(INVALID_HANDLE_VALUE == h2)
    {
        PrintLastErrorText();
        CloseHandle(h1);
        return false;
    }
    if(!CopyHandles(h1, h2))
    {
        PrintLastErrorText();
        CloseHandle(h1);
        CloseHandle(h2);
    }
    CloseHandle(h1);
    CloseHandle(h2);
    return true;
}

bool FromASCIIToUnicode(TCHAR* ASCII, TCHAR* Unicode)
{
    HANDLE hASCII = CreateFile(ASCII,
                               GENERIC_READ,
                               0, NULL,
                               OPEN_EXISTING,
                               0, NULL);
    if(INVALID_HANDLE_VALUE == hASCII)
    {
        PrintLastErrorText();
        return false;
    }

    HANDLE hUnicode = CreateFile(Unicode,
                                 GENERIC_WRITE,
                                 0, NULL,
                                 CREATE_ALWAYS,
                                 FILE_ATTRIBUTE_NORMAL,
                                 NULL);
    if(INVALID_HANDLE_VALUE == hUnicode)
    {
        CloseHandle(hASCII);
        PrintLastErrorText();
        return false;
    }

    char buffer[N];
    TCHAR buf[N];
    DWORD Read;
    DWORD Written;

    while(ReadFile(hASCII, buffer,
                   N, &Read, NULL)
          && Read)
    {
        for(int i = 0; i < Read; i++)
            buf[i] = (TCHAR)buffer[i];
        if(!WriteFile(hUnicode, &buf, 2 * Read, &Written, NULL)
           || 2 * Read != Written)
        {
            PrintLastErrorText();
            CloseHandle(hASCII);
            CloseHandle(hUnicode);
            return false;
        }
    }
    if(Read)
    {
        PrintLastErrorText();
        CloseHandle(hASCII);
        CloseHandle(hUnicode);
        return false;
    }

    CloseHandle(hASCII);
    CloseHandle(hUnicode);
    return true;
}

bool envpFile(TCHAR* file, TCHAR** envp)
{
    if(file)
    {
        HANDLE h = CreateFile(file,
                              GENERIC_WRITE,
                              0, NULL,
                              OPEN_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
        if(INVALID_HANDLE_VALUE == h)
        {
            PrintLastErrorText();
            CloseHandle(h);
        }
        DWORD Written;
        while(*envp)
        {
            DWORD count = _tcslen(*envp);
            if(!WriteFile(h, *envp, count, &Written, NULL)
               || Written != count)
            {
                PrintLastErrorText();
                CloseHandle(h);
                return false;
            }
            if(!WriteFile(h, _T("\n"), sizeof(TCHAR), &Written, NULL)
               || Written != sizeof(TCHAR))
            {
                PrintLastErrorText();
                CloseHandle(h);
                return false;
            }
            envp++;
        }
        CloseHandle(h);
    }
    else
        while(*envp)
        {
            _tprintf(_T("%s\n"), *envp);
            envp++;
        }
}
#pragma endregion