#include <windows.h>
#include <stdio.h>

int g_nIndex = 0;
const int MAX_TIMES = 100;
DWORD g_dwTimes[MAX_TIMES];
HANDLE g_hMutex = NULL;

DWORD WINAPI FirstThread(PVOID pvParam);
DWORD WINAPI SecondThread(PVOID pvParam);

int main()
{
  DWORD idThread1, idThread2;
  g_hMutex = CreateMutex(NULL, FALSE, NULL);
  HANDLE hThread1 = CreateThread(NULL, 0, FirstThread, NULL, 0, &idThread1);
  HANDLE hThread2 = CreateThread(NULL, 0, SecondThread, NULL, 0, &idThread2);
  HANDLE hThreads[2] = {hThread1, hThread2};

  WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
  TerminateThread(hThread1, 0);
  TerminateThread(hThread2, 0);
  CloseHandle(g_hMutex);

  // output
  for (int i = 0; i < MAX_TIMES; i++)
  {
    printf("%lu ", g_dwTimes[i]);
  }

  return 0;
}

DWORD WINAPI FirstThread(PVOID pvParam)
{
  DWORD dw;
  BOOL fDone = FALSE;
  while (!fDone)
  {
    dw = WaitForSingleObject(g_hMutex, INFINITE);
    if (dw == WAIT_OBJECT_0)
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
      ReleaseMutex(g_hMutex);
    }
    else
    {
      break;
    }
  }
  return 0;
}

DWORD WINAPI SecondThread(PVOID pvParam)
{
  DWORD dw;
  BOOL fDone = FALSE;
  while (!fDone)
  {
    dw = WaitForSingleObject(g_hMutex, INFINITE);
    if (dw == WAIT_OBJECT_0)
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
      ReleaseMutex(g_hMutex);
    }
    else
    {
      break;
    }
  }
  return 0;
}
