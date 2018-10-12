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
    _tprintf(_T("\n%s"), PTCHAR(_T("Input Test number to start. For more information read the ReadMe file.\n")));
    SetConsoleColor(9);
    if(_tscanf_s(_T("%d"), &TestNum))
    {
        SetConsoleColor(7);
        if(TestNum > 17 || TestNum < 1)
        {
            RunAll = true;
            TestNum = 1;
        }
        switch(TestNum)
        {
            case 1:
                _tprintf(_T("%s\n"), PTCHAR(_T("Test 1.1: Error Handling.\n")));
                TestPrintLastErrorText();
                if(RunAll)
                {
                    TestNum = 2;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 2:
                _tprintf(_T("%s"), PTCHAR(_T("Test 1.2: Getting command line arguments and enviroment variables.\n")));
                GetArgsAndVars(argc, argv, envp);
                GetCurrDir();
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 3:
                _tprintf(_T("%s"), PTCHAR(_T("Test 1.3: CopyingFiles.Take a look at the files in command line arguments.\n")));
                TestFileCopy(argc, argv);
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 4:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 5:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 6:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 7:
                _tprintf(_T("%s"), PTCHAR(_T("Test 1.7: Writing from file to console.\n")));
                TestFromFileToConsole(argc, argv);
                TestFromFileToOutput(argc, argv);
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 8:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 9:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 10:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 11:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 12:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 13:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 14:
                _tprintf(_T("%s"), PTCHAR(_T("Test 1.14: Changing file creation time.\n")));
                TestChangeFileTime(argc, argv);
                while(getchar() != _T('\n'));
                if(RunAll)
                {
                    TestNum = 15;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 15:
                _tprintf(_T("%s"), PTCHAR(_T("Test 1.15: Setting an enviroment variable.\n")));
                SetVars();
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 16:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 17:
                _tprintf(_T("%s"), PTCHAR(_T("Problem not implemented yet")));
                if(RunAll)
                {
                    TestNum++;
                    _tprintf(_T("\n%s"), PTCHAR(_T("Press enter to get to next test.\n")));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
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
