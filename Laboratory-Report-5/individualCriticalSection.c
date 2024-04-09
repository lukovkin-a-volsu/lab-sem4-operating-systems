#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

typedef struct
{
	int ordinal;
} ThreadParams;

int priority;
ThreadParams *params;
DWORD threadId;
HANDLE hThread;
const char *priorityString;
CRITICAL_SECTION g_CriticalSection;

DWORD WINAPI ThreadFunc(LPVOID lpParam);
const char *priorityToString(int priority);

int compareThreads(const void *a, const void *b)
{
	return (*(int *)b - *(int *)a);
}

int main(int argc, TCHAR *argv[])
{
	InitializeCriticalSection(&g_CriticalSection);
	DWORD idThreadA;
	ThreadParams paramsA = {1};
	HANDLE hThreadA =
			CreateThread(
					NULL,
					0,
					ThreadFunc,
					&paramsA,
					0,
					&idThreadA);

	DWORD idThreadB;
	ThreadParams paramsB = {2};
	HANDLE hThreadB =
			CreateThread(
					NULL,
					0,
					ThreadFunc,
					&paramsB,
					0,
					&idThreadB);

	DWORD idThreadC;
	ThreadParams paramsC = {3};
	HANDLE hThreadC =
			CreateThread(
					NULL,
					0,
					ThreadFunc,
					&paramsC,
					0,
					&idThreadB);

	if (!SetThreadPriority(hThreadB, THREAD_PRIORITY_ABOVE_NORMAL))
	{
		printf("Failed to set hThreadB priority");
	}
	if (!SetThreadPriority(hThreadC, THREAD_PRIORITY_HIGHEST))
	{
		printf("Failed to set hThreadC priority");
	}

	// HANDLE hThreads[3] = {hThreadA, hThreadB, hThreadC};
	// WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);
	WaitForSingleObject(hThreadA, INFINITE);
	WaitForSingleObject(hThreadB, INFINITE);
	WaitForSingleObject(hThreadC, INFINITE);

	const size_t size = 3;
	int *threadsPriorities = (int *)malloc(size * sizeof(int));
	threadsPriorities[0] = GetThreadPriority(hThreadA);
	threadsPriorities[1] = GetThreadPriority(hThreadB);
	threadsPriorities[2] = GetThreadPriority(hThreadC);
	qsort(threadsPriorities, size, sizeof(int), compareThreads);
	printf("\nThreads priorities: \n");
	for (size_t i = 0; i < size; i++)
	{
		printf("%s\n", priorityToString(threadsPriorities[i]));
	}

	TerminateThread(hThreadA, 0);
	TerminateThread(hThreadB, 0);
	TerminateThread(hThreadC, 0);
	DeleteCriticalSection(&g_CriticalSection);
	
	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	EnterCriticalSection(&g_CriticalSection);
	params = (ThreadParams *)lpParam;
	threadId = GetCurrentThreadId();
	hThread = GetCurrentThread();

	// static int num = 1;
	priority = GetThreadPriority(hThread);
	priorityString = priorityToString(priority);

	printf("A new thread has been created\n");
	printf("Ordinal number (by creating): %d\n", params->ordinal);
	// printf("Ordinal number (by launching): %d\n", num++);
	printf("Current Thread ID: %lu\n", threadId);
	printf("Priority: %s\n", priorityString);
	LeaveCriticalSection(&g_CriticalSection);
	return 0;
}

const char *priorityToString(int priority)
{
	switch (priority)
	{
	case THREAD_PRIORITY_IDLE:
		return "IDLE";
	case THREAD_PRIORITY_LOWEST:
		return "LOWEST";
	case THREAD_PRIORITY_BELOW_NORMAL:
		return "BELOW NORMAL";
	case THREAD_PRIORITY_NORMAL:
		return "NORMAL";
	case THREAD_PRIORITY_ABOVE_NORMAL:
		return "ABOVE NORMAL";
	case THREAD_PRIORITY_HIGHEST:
		return "HIGHEST";
	case THREAD_PRIORITY_TIME_CRITICAL:
		return "TIME CRITICAL";
	default:
		return "UNKNOWN";
	}
}