#pragma once
#include "tchar.h"

#pragma region Error Handling
void TestPrintLastErrorText();
#pragma endregion

#pragma region Command line arguments and enviroment variables
void GetArgsAndVars(int, TCHAR*[], TCHAR**);
void SetVars();
void GetCurrDir();
#pragma endregion

#pragma region Files
void TestFileCopy(int, TCHAR*[]);
void TestFileReverseCopy(int, TCHAR*[]);
void TestChangeFileTime(int, TCHAR*[]);
void TestFromFileToOutput(int, TCHAR*[]);
void TestFromFileToConsole(int, TCHAR*[]);
#pragma endregion