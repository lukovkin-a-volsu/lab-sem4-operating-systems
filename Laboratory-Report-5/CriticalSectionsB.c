#include <windows.h>
#include <stdio.h>

int g_nIndex = 0;
const int MAX_TIMES = 100;
DWORD g_dwTimes[MAX_TIMES];
CRITICAL_SECTION g_CriticalSection;

DWORD WINAPI FirstThread(PVOID pvParam);
DWORD WINAPI SecondThread(PVOID pvParam);

int main()
{
  DWORD idThread1, idThread2;
  InitializeCriticalSection(&g_CriticalSection);
  HANDLE hThread1 = CreateThread(NULL, 0, FirstThread, NULL, 0, &idThread1);
  HANDLE hThread2 = CreateThread(NULL, 0, SecondThread, NULL, 0, &idThread2);
  HANDLE hThreads[2] = {hThread1, hThread2};

  WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
  TerminateThread(hThread1, 0);
  TerminateThread(hThread2, 0);
  DeleteCriticalSection(&g_CriticalSection);

  // output
  for (int i = 0; i < MAX_TIMES; i++)
  {
    printf("%lu ", g_dwTimes[i]);
  }

  return 0;
}

DWORD WINAPI FirstThread(PVOID pvParam)
{
  BOOL fDone = FALSE;
  while (!fDone)
  {
    EnterCriticalSection(&g_CriticalSection);
    if (g_nIndex >= MAX_TIMES)
    {
      fDone = TRUE;
    }
    else
    {
      g_dwTimes[g_nIndex] = GetTickCount();
      Sleep(10);
      g_nIndex++;
    }
    LeaveCriticalSection(&g_CriticalSection);
  }
  return 0;
}

DWORD WINAPI SecondThread(PVOID pvParam)
{
  BOOL fDone = FALSE;
  while (!fDone)
  {
    EnterCriticalSection(&g_CriticalSection);
    if (g_nIndex >= MAX_TIMES)
    {
      fDone = TRUE;
    }
    else
    {
      g_dwTimes[g_nIndex++] = GetTickCount();
      Sleep(10);
    }
    LeaveCriticalSection(&g_CriticalSection);
  }
  return 0;
}
