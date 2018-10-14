#pragma once
#include "tchar.h"

#pragma region Error Handling
void PrintLastErrorText();                  // problem 1.1
#pragma endregion                           

#pragma region Files                        
bool FileCopy(TCHAR*, TCHAR*);              // problem 1.3
bool FileReverseCopy(TCHAR*, TCHAR*);       // problem 1.4
bool FromFileToOutput(TCHAR*);              // problem 1.7
bool CopyHandles(HANDLE, HANDLE);           // problem 1.10
bool FromFileToConsole(TCHAR*);             // problem 1.10
bool envpFile(TCHAR*, TCHAR**);             // problrm 1.12
bool ChangeFileTime(TCHAR*);                // problem 1.14
#pragma endregion