#include "stdafx.h"

#pragma region ErrorHandling
void PrintLastErrorText()
{

    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  dw,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                             (LPTSTR)&lpMsgBuf,
                             0, NULL);

    _tprintf(_T("%s"), (PTCHAR)lpMsgBuf);
    LocalFree(lpMsgBuf);
}
#pragma endregion

