#pragma once
#include "tchar.h"

#pragma region Error Handling
void PrintLastErrorText();
#pragma endregion

#pragma region Files
bool FileCopy(TCHAR*, TCHAR*);
bool ChangeFileTime(TCHAR* file);
#pragma endregion