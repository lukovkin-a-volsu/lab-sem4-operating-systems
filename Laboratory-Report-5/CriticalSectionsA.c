#include <windows.h>
#include <stdio.h>

int g_nIndex = 0;
const int MAX_TIMES = 100;
DWORD g_dwTimes[MAX_TIMES];

DWORD WINAPI FirstThread(PVOID pvParam);
DWORD WINAPI SecondThread(PVOID pvParam);

int main()
{
  DWORD idThread1, idThread2;
  HANDLE hThread1 = CreateThread(NULL, 0, FirstThread, NULL, 0, &idThread1);
  HANDLE hThread2 = CreateThread(NULL, 0, SecondThread, NULL, 0, &idThread2);

  WaitForSingleObject(hThread1, INFINITE);
  WaitForSingleObject(hThread2, INFINITE);

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
  }
  return 0;
}

DWORD WINAPI SecondThread(PVOID pvParam)
{
  BOOL fDone = FALSE;
  while (!fDone)
  {
    if (g_nIndex >= MAX_TIMES)
    {
      fDone = TRUE;
    }
    else
    {
      g_dwTimes[g_nIndex++] = GetTickCount();
      Sleep(10);
    }
  }
  return 0;
}
