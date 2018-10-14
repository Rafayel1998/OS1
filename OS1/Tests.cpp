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

void TPrintLastErrorText()
{
    PrintLastErrorText();
}
#pragma endregion

#pragma region Command line arguments, enviroment variables and current directory
const DWORD N = 64;
const DWORD bigN = 1024;

void GetArgsAndVars(int argc, TCHAR* argv[], TCHAR** envp)
{
    if(argc > 0)
        for(int i = 1; i < argc; i++)
            _tprintf(_T("%s\n"), argv[i]);
    while(*envp)
    {
        _tprintf(_T("%s\n"), *envp);
        envp++;
    }
}

void ErrorCheck(int ErrNo)
{
    if(!ErrNo)
        PrintLastErrorText();
    else if(ErrNo > bigN)
        _tprintf(_T("%s\n"), _T("Buffer size is insufficient."));
    else
        _tprintf(_T("%s\n"), _T("Succes"));
}

void SetVars(int argc, TCHAR* argv[])
{
    TCHAR buf[bigN];
    SetEnvironmentVariable(_T("NewEnvVariale"), _T("It'sValue"));
    DWORD val = GetEnvironmentVariable(_T("NewEnvVariale"), buf, bigN);
    ErrorCheck(val);
    val = GetEnvironmentVariable(_T("PAT"), buf, bigN);
    ErrorCheck(val);
    val = GetEnvironmentVariable(_T("PATH"), buf, bigN);
    ErrorCheck(val);
    if(val <= bigN)
    {
        if(argc > 6)
        {
            TCHAR path[2 * bigN + 1];
            int i,j;
            for(j = 0; j < bigN && buf[j] != '\0'; j++)
                path[j] = buf[j];
            for(i = j; i < bigN + j && argv[6][i] != '\0'; i++)
                path[i] = argv[6][i];
            if(i == bigN + j)
            {
                _tprintf(_T("%s\n"), _T("Catalogue name too long.\n"));
                return;
            }
            path[i] = '\0';
            SetEnvironmentVariable(_T("PATH"), path);
            val = GetEnvironmentVariable(_T("PATH"), buf, bigN);
            ErrorCheck(val);
            if(val <= bigN)
                _tprintf(_T("%s\n"), buf);
        }
        else
            _tprintf(_T("%s"), _T("Insufficient command line arguments.\n"));
    }
}

void GetCurrDir()
{
    TCHAR buf[bigN];
    DWORD val = GetCurrentDirectory(bigN, buf);
    ErrorCheck(val);
    val = GetCurrentDirectory(bigN, buf);
    ErrorCheck(val);
}

void MyGetVersion()
{
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if(0 == GetVersionEx((LPOSVERSIONINFO)&osvi))
        PrintLastErrorText();
    else
    {
        _tprintf(_T("BuildNumber: %d\n"), osvi.dwBuildNumber);
        _tprintf(_T("MajorVersion: %d\n"), osvi.dwMajorVersion);
        _tprintf(_T("MinorVersion: %d\n"), osvi.dwMinorVersion);
        _tprintf(_T("OSVersionInfoSize: %d\n"), osvi.dwOSVersionInfoSize);
        _tprintf(_T("PlatformId: %d\n"), osvi.dwPlatformId);
        _tprintf(_T("CSDVersion: %s\n"), osvi.szCSDVersion);
        _tprintf(_T("ProductType: %d\n"), osvi.wProductType);
        _tprintf(_T("Reserved: %d\n"), osvi.wReserved);
        _tprintf(_T("ServicePackMajor: %d\n"), osvi.wServicePackMajor);
        _tprintf(_T("ServicePackMinor: %d\n"), osvi.wServicePackMinor);
        _tprintf(_T("SuiteMask: %d\n"), osvi.wSuiteMask);
    }

}
#pragma endregion

#pragma region Files
void TestFileCopy(int argc, TCHAR* argv[])
{
    if(argc > 2)
        FileCopy(argv[1], argv[2]);
    else
        _tprintf(_T("%s"), _T("Insufficient command line arguments.\n"));
}

void TestFileReverseCopy(int argc, TCHAR* argv[])
{
    if(argc > 11)
        FileReverseCopy(argv[1], argv[11]);
    else
        _tprintf(_T("%s"), _T("Insufficient command line arguments.\n"));
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
                (st.wHour + 4) % 24, st.wMinute, st.wSecond, st.wMilliseconds);
        }
    }
    else
        _tprintf(_T("%s"), _T("Insufficient command line arguments.\n"));
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
            _tprintf(_T("%s"), _T("Insufficient command line arguments.\n"));
    }
    else
        _tprintf(_T("%s"), _T("Insufficient command line arguments.\n"));
}

void TestFromFileToConsole(int argc, TCHAR* argv[])
{
    if(argc > 3)
        FromFileToConsole(argv[3]);
    else
        _tprintf(_T("%s"), _T("Insufficient command line arguments.\n"));
}

void TestFromInputToFile(int argc, TCHAR* argv[])
{
    if(argc > 8)
        FromInputToFile(argv[8]);
    else
        _tprintf(_T("%s"), _T("Insufficient command line arguments.\n"));
}

void TestFromInputToOutput()
{
    FromInputToOutput();
}

void TestFromASCIIToUnicode(int argc, TCHAR* argv[])
{
    if(argc > 10)
        FromASCIIToUnicode(argv[9], argv[10]);
    else
        _tprintf(_T("%s"), _T("Insufficient command line arguments.\n"));
}

void TestenvpFile(int argc, TCHAR* argv[], TCHAR** envp)
{
    if(argc > 7)
    {
        envpFile(argv[7], envp);
    }
    else
    {
        _tprintf(_T("%s\n"), _T("Insufficient command line arguments.\n"));
        envpFile(NULL, envp);
    }
}
#pragma endregion