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

void InitFiles(int argc, TCHAR* argv[])
{
    if(argc > 1)
    {
        HANDLE h = CreateFile(argv[1],
                               GENERIC_WRITE,
                               0, NULL,
                               CREATE_ALWAYS,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);
        if(INVALID_HANDLE_VALUE == h)
            TPrintLastErrorText();
        TCHAR buffer[] = _T("When I was 5 years old, my mother always told me that happiness was the key to life.\nWhen I went to school, they asked me what I wanted to be when I grew up.\nI wrote down ‘happy’.\nThey told me I didn’t understand the assignment, and I told them they didn’t understand life.\n\nՋոն Լեննոն\n");
        DWORD Written;
        if(!WriteFile(h, buffer, sizeof(buffer) - sizeof(TCHAR),&Written, NULL)
           || sizeof(buffer) - sizeof(TCHAR) != Written)
            TPrintLastErrorText();
        CloseHandle(h);
    }
    if(argc > 3)
    {
        HANDLE h = CreateFile(argv[3],
                              GENERIC_WRITE,
                              0, NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
        if(INVALID_HANDLE_VALUE == h)
            TPrintLastErrorText();
        TCHAR buffer[] = _T("If you are born poor it’s not your mistake, but if you die poor it’s your mistake.\nԲիլ Գեյթս\n");
        DWORD Written;
        if(!WriteFile(h, buffer, sizeof(buffer) - sizeof(TCHAR), &Written, NULL)
           || sizeof(buffer) - sizeof(TCHAR) != Written)
            TPrintLastErrorText();
        CloseHandle(h);
    }
    if(argc > 4)
    {
        HANDLE h = CreateFile(argv[4],
                              GENERIC_WRITE,
                              0, NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
        if(INVALID_HANDLE_VALUE == h)
            TPrintLastErrorText();
        TCHAR buffer[] = _T("Success consists of going from failure to failure without loss of enthusiasm.\nՎինսթն Չերչիլ\n");
        DWORD Written;
        if(!WriteFile(h, buffer, sizeof(buffer) - sizeof(TCHAR), &Written, NULL)
           || sizeof(buffer) - sizeof(TCHAR) != Written)
            TPrintLastErrorText();
        CloseHandle(h);
    }
    if(argc > 9)
    {
        HANDLE h = CreateFile(argv[9],
                              GENERIC_WRITE,
                              0, NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
        if(INVALID_HANDLE_VALUE == h)
            TPrintLastErrorText();
        char buffer[] = "Debugging is like being the detective in a crime movie where you are also the murderer.\n";
        DWORD Written;
        if(!WriteFile(h, buffer, sizeof(buffer) - sizeof(char), &Written, NULL)
           || sizeof(buffer) - sizeof(char)!= Written)
            TPrintLastErrorText();
        CloseHandle(h);
    }
    if(argc > 12)
    {
        HANDLE h = CreateFile(argv[12],
                              GENERIC_WRITE,
                              0, NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
        if(INVALID_HANDLE_VALUE == h)
            TPrintLastErrorText();
        TCHAR buffer[] = _T("Wanting to be someone else is a waste of the person you are.\nԿուրտ Քոբեյն\n");
        DWORD Written;
        if(!WriteFile(h, buffer, sizeof(buffer) - sizeof(TCHAR), &Written, NULL)
           || sizeof(buffer) - sizeof(TCHAR) != Written)
            TPrintLastErrorText();
        CloseHandle(h);
    }
}

int _tmain(int argc, TCHAR* argv[], TCHAR** envp)
{
    int TestNum;
    bool RunAll = false;
    static bool old;
    if(!old)
    {
        _tprintf(_T("\n%s"), _T("Initilazing the files.\n"));
        InitFiles(argc, argv);
    }
    SetConsoleColor(12);
    _tprintf(_T("\n%s"), _T("Input Test number to start. For more information read the ReadMe file.\n"));
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
                _tprintf(_T("\n%s"), _T("Test 1.1: Error Handling.\n"));
                TestPrintLastErrorText();
                if(RunAll)
                {
                    TestNum = 2;
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 2:
                _tprintf(_T("\n%s"), _T("Test 1.2: Getting command line arguments and enviroment variables.\n"));
                GetArgsAndVars(argc, argv, envp);
                _tprintf(_T("\n%s"), _T("Test 1.2: Getting current directory.\n"));
                GetCurrDir();
                _tprintf(_T("\n%s"), _T("Test 1.2: Getting version info.\n"));
                MyGetVersion();
                if(RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 3:
                _tprintf(_T("\n%s"), _T("Test 1.3: Copying files.\n"));
                TestFileCopy(argc, argv);
                if(RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 4:
                _tprintf(_T("\n%s"), _T("Test 1.4: Copying files in reverse order.\n"));
                TestFileReverseCopy(argc, argv);
                if(RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 5:
                _tprintf(_T("\n%s"), _T("Problem not implemented yet"));
                if(RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 6:
                _tprintf(_T("\n%s"), _T("Problem not implemented yet"));
                if(RunAll)
                {

                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 7:
                _tprintf(_T("\n%s"), _T("Test 1.7: Writing from file to console.\n"));
                TestFromFileToConsole(argc, argv);
                TestFromFileToOutput(argc, argv);
                if(RunAll)
                {

                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 8:
                if(!RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Test 1.8: Copying from standart input to file.\n"));
                    TestFromInputToFile(argc, argv);
                    break;
                }
            case 9:
                if(!RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Test 1.9: Copying from standart input to standart output.\n"));
                    TestFromInputToOutput();
                    break;
                }
            case 10:
                _tprintf(_T("\n%s"), _T("Test 1.10: Copying handles.\n"));
                TestFromFileToConsole(argc, argv);
                TestFromFileToOutput(argc, argv);
                if(RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 11:
                _tprintf(_T("\n%s"), _T("Test 1.11: Cpying ASCII symbols to Unicode file.\n"));
                TestFromASCIIToUnicode(argc, argv);
                if(RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 12:
                _tprintf(_T("\n%s"), _T("Test 1.12: Enviroment variables to file.\n"));
                TestenvpFile(argc, argv, envp);
                if(RunAll) 
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 13:
                _tprintf(_T("\n%s"), _T("Problem not implemented yet"));
                if(RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 14:
                _tprintf(_T("\n%s"), _T("Test 1.14: Changing file creation time.\n"));
                TestChangeFileTime(argc, argv);
                while(getchar() != _T('\n'));
                if(RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 15:
                _tprintf(_T("\n%s"), _T("Test 1.15: Setting an enviroment variable.\n"));
                SetVars(argc, argv);
                if(RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 16:
                _tprintf(_T("\n%s"), _T("Problem not implemented yet"));
                if(RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Press enter to get to next test.\n"));
                    while(getchar() != _T('\n'));
                }
                else
                    break;
            case 17:

                if(!RunAll)
                {
                    _tprintf(_T("\n%s"), _T("Test 1.17: Copying from file to console until Ctrl+c is hit.\n"));
                    TestFileToConsole(argc, argv);
                }
                else
                    break;
        }
        old = true;
        _tmain(argc, argv, envp);
    }
    else
    {
        SetConsoleColor(12);
        _tprintf(_T("%s"), _T("Programm terminated!\n"));
    }
    return 0;
}
