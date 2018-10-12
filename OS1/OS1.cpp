// OS1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void SetConsoleColor(char color)
{
    HANDLE ConsoleHandle = CreateFile(_T("CONOUT$"),
                                      GENERIC_WRITE | GENERIC_READ,
                                      0, NULL,
                                      OPEN_EXISTING,
                                      0, NULL);
    if(ConsoleHandle != INVALID_HANDLE_VALUE)
        SetConsoleTextAttribute(ConsoleHandle, color);
}
int _tmain(int argc, TCHAR* argv[], TCHAR** envp)
{
    int TestNum;
    bool RunAll = false;
    SetConsoleColor(12);
    _tprintf(_T("%s"), PTCHAR(_T("Input Test number to start. For more information read the ReadMe file.\n")));
    SetConsoleColor(9);
    if(_tscanf_s(_T("%d"), &TestNum))
    {
        SetConsoleColor(7);
        if(TestNum > 2 || TestNum < 0)
        {
            RunAll = true;
            TestNum = 0;
        }
        switch(TestNum)
        {
            case 0:
                _tprintf(_T("%s\n"), PTCHAR(_T("Test 0: Error Handling.\n")));
                TestPrintLastErrorText();
                if(RunAll)
                {
                    TestNum = 1;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 1:
                _tprintf(_T("%s"), PTCHAR(_T("Test 1.0: Getting command line arguments and enviroment variables.\n")));
                GetArgsAndVars(argc, argv, envp);
                _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                if(!RunAll)
                    while(getchar() != _T('\n'));
                while(getchar() != _T('\n'));
                _tprintf(_T("%s"), PTCHAR(_T("Test 1.1: Setting an enviroment variable.\n")));
                SetVars();
                _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                while(getchar() != _T('\n'));
                _tprintf(_T("%s"), PTCHAR(_T("Test 1.2: Getting current directory.\n")));
                GetCurrDir();
                if(RunAll)
                {
                    TestNum = 2;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 2:
                _tprintf(_T("%s"), PTCHAR(_T("Test 2.0: CopyingFiles.Take a look at the files in command line arguments.\n")));
                TestFileCopy(argc, argv);
                _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                if(!RunAll)
                    while(getchar() != _T('\n'));
                while(getchar() != _T('\n'));
                _tprintf(_T("%s"), PTCHAR(_T("Test 2.1: Changing file creation time.\n")));
                TestChangeFileTime(argc, argv);
        }
        _tmain(argc, argv, envp);
    }
    else
    {
        SetConsoleColor(12);
        _tprintf(_T("%s"), PTCHAR(_T("Programm terminated!\n")));
    }
    return 0;
}
