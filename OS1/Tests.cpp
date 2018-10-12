#include "stdafx.h"
#include "Functions.h"

#pragma region ErrorHandling
void TestPrintLastErrorText()
{
    PrintLastErrorText();
    SetLastError(56);
    PrintLastErrorText();
    SetLastError(36);
    PrintLastErrorText();
    SetLastError(39);
    PrintLastErrorText();
}
#pragma endregion

#pragma region Command line arguments, enviroment variables and current directory
const unsigned int N = 50;

//problem 1.2
void GetArgsAndVars(int argc, TCHAR* argv[], TCHAR** envp)
{
    if(argc > 0)
        for(int i = 1; i < argc; i++)
            _tprintf(_T("%s\n"), (PTCHAR)argv[i]);
    while(*envp)
    {
        _tprintf(_T("%s\n"), (PTCHAR)*envp);
        envp++;
    }
}

void ErrorCheck(int ErrNo)
{
    if(!ErrNo)
        PrintLastErrorText();
    else if(ErrNo > N)
        _tprintf(_T("%s\n"), _T("Buffer size is insufficient."));
    else
        _tprintf(_T("%s\n"), _T("Succes"));
}

//problem 1.15
void SetVars()
{
    TCHAR buf[N];
    DWORD val = GetEnvironmentVariable(_T("PAT"), buf, N);
    ErrorCheck(val);
    val = GetEnvironmentVariable(_T("PATH"), buf, N);
    ErrorCheck(val);
    SetEnvironmentVariable(_T("NewEnvVariale"), _T("It'sValue"));
    val = GetEnvironmentVariable(_T("NewEnvVariale"), buf, N);
    ErrorCheck(val);
}

//problem 1.2
void GetCurrDir()
{
    TCHAR buf[N];
    DWORD val = GetCurrentDirectory(N, buf);
    ErrorCheck(val);
    val = GetCurrentDirectory(N, buf);
    ErrorCheck(val);
}
#pragma endregion

#pragma region Files
void TestFileCopy(int argc, TCHAR* argv[])
{
    if(argc > 2)
        FileCopy(argv[1], argv[2]);
    else
        _tprintf(_T("%s"), PTCHAR(_T("Insufficient command line arguments.\n")));
}

void TestChangeFileTime(int argc, TCHAR* argv[])
{
    if(argc > 1)
    {
        if(ChangeFileTime(argv[1]))
        {
            HANDLE h = CreateFile(argv[1],
                                  GENERIC_READ, 
                                  0, NULL,
                                  OPEN_EXISTING,
                                  0, NULL);
            if(INVALID_HANDLE_VALUE == h)
            {
                PrintLastErrorText();
                exit(-1);
            }
            BY_HANDLE_FILE_INFORMATION info;
            if(!GetFileInformationByHandle(h, &info))
            {
                PrintLastErrorText();
                exit(-1);
            }
            SYSTEMTIME st;
            FileTimeToSystemTime(&info.ftCreationTime, &st);
            _tprintf(_T("%d:%d:%d:%d\n"),
                     (st.wHour + 4)%24, st.wMinute, st.wSecond, st.wMilliseconds);
        }
    }
    else
        _tprintf(_T("%s"), PTCHAR(_T("Insufficient command line arguments.\n")));
}

void TestFromFileToOutput(int argc, TCHAR* argv[])
{
    if(argc > 4)
    {
        FromFileToOutput(argv[4]);
        if(argc > 5)
        {
            HANDLE h = CreateFile(argv[5],
                                  GENERIC_WRITE, 
                                  0, NULL,
                                  OPEN_ALWAYS,
                                  0, NULL);
            if(INVALID_HANDLE_VALUE == h)
                PrintLastErrorText();
            else
            {
                _tprintf(_T("\n"));
                SetStdHandle(STD_OUTPUT_HANDLE, h);
                FromFileToOutput(argv[4]);
            }
        }
        else
            _tprintf(_T("%s"), PTCHAR(_T("Insufficient command line arguments.\n")));
    }
    else
        _tprintf(_T("%s"), PTCHAR(_T("Insufficient command line arguments.\n")));
}

void TestFromFileToConsole(int argc, TCHAR* argv[])
{
    if(argc > 3)
        FromFileToConsole(argv[3]);
    else
        _tprintf(_T("%s"), PTCHAR(_T("Insufficient command line arguments.\n")));
}
#pragma endregion