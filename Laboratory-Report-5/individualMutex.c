#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

typedef struct
{
	int ordinal;
} ThreadParams;

DWORD WINAPI ThreadFunc(LPVOID lpParam);
const char *priorityToString(int priority);

int compareThreads(const void *a, const void *b)
{
	return (*(int *)b - *(int *)a);
}

HANDLE g_hMutex = NULL;

int main(int argc, TCHAR *argv[])
{
	DWORD idThreadA, idThreadB, idThreadC;
	ThreadParams paramsA = {1};
	ThreadParams paramsB = {2};
	ThreadParams paramsC = {3};
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	HANDLE hThreadA =
			CreateThread(
					NULL,
					0,
					ThreadFunc,
					&paramsA,
					0,
					&idThreadA);

	HANDLE hThreadB =
			CreateThread(
					NULL,
					0,
					ThreadFunc,
					&paramsB,
					0,
					&idThreadB);

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

	HANDLE hThreads[3] = {hThreadA, hThreadB, hThreadC};
	WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);
	// WaitForSingleObject(hThreadA, INFINITE);
	// WaitForSingleObject(hThreadB, INFINITE);
	// WaitForSingleObject(hThreadC, INFINITE);

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
	CloseHandle(g_hMutex);

	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	DWORD dw;
	ThreadParams *params = (ThreadParams *)lpParam;
	DWORD threadId = GetCurrentThreadId();
	HANDLE hThread = GetCurrentThread();

	// Lock mutex before accessing stdout
	dw = WaitForSingleObject(g_hMutex, INFINITE);

	if (dw == WAIT_OBJECT_0)
	{
		int priority = GetThreadPriority(hThread);
		const char *priorityString = priorityToString(priority);

		printf("A new thread has been created\n");
		printf("Ordinal number (by creating): %d\n", params->ordinal);
		printf("Current Thread ID: %lu\n", threadId);
		printf("Priority: %s\n", priorityString);

		// Release mutex after accessing stdout
		ReleaseMutex(g_hMutex);
	}

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