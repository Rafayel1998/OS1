#pragma once
#include "tchar.h"

#pragma region Error Handling
void TestPrintLastErrorText();
#pragma endregion

#pragma region Command line arguments and enviroment variables
void GetArgsAndVars(int argc, TCHAR* argv[], TCHAR** envp);
void SetVars();
void GetCurrDir();
#pragma endregion

#pragma region Files
void TestFileCopy(int argc, TCHAR* argv[]);
void TestChangeFileTime(int argc, TCHAR* argv[]);
#pragma endregion