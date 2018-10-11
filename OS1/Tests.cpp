#include "stdafx.h"
#include "Functions.h"

#pragma region ErrorHandling
void TestPrintLastErrorText()
{
    PrintLastErrorText();
    SetLastError(2);
    PrintLastErrorText();
    SetLastError(36);
    PrintLastErrorText();
}
#pragma endregion

#pragma region Command line arguments, enviroment variables and current directory
const unsigned int N = 50;

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

void GetCurrDir()
{
    TCHAR buf[N];
    DWORD val = GetEnvironmentVariable(_T("PAT"), buf, N);

    val = GetCurrentDirectory(N, buf);
    ErrorCheck(val);
    val = GetCurrentDirectory(N, buf);
    ErrorCheck(val);
}
#pragma endregion