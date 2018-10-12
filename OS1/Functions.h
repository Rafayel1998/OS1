#pragma once
#include "tchar.h"

#pragma region Error Handling
void PrintLastErrorText();
#pragma endregion

#pragma region Files
bool FileCopy(TCHAR*, TCHAR*);
bool FileReverseCopy(TCHAR*, TCHAR*);
bool ChangeFileTime(TCHAR* file);
bool FromFileToOutput(TCHAR*);
bool FromFileToConsole(TCHAR*);
#pragma endregion