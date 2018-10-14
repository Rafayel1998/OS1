#pragma once
#include "tchar.h"

#pragma region Error Handling
void TestPrintLastErrorText();                      // problem 1.1
#pragma endregion

#pragma region Command line arguments and enviroment variables
void GetArgsAndVars(int, TCHAR*[], TCHAR**);        // problem 1.2
void MyGetVersion();                                // problem 1.2
void GetCurrDir();                                  // problem 1.2
void SetVars(int, TCHAR*[]);                        // problem 1.15
#pragma endregion

#pragma region Files
void TestFileCopy(int, TCHAR*[]);                   // problem 1.3
void TestFileReverseCopy(int, TCHAR*[]);            // problem 1.4
void TestFromFileToOutput(int, TCHAR*[]);           // problem 1.7
void TestFromFileToConsole(int, TCHAR*[]);          // problem 1.10
void TestenvpFile(int, TCHAR*[], TCHAR**);          // problem 1.12
void TestChangeFileTime(int, TCHAR*[]);             // problem 1.14
#pragma endregion