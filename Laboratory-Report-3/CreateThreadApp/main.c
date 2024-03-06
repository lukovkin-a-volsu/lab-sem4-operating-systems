#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

DWORD WINAPI ThreadA(void* arg);
DWORD WINAPI ThreadB(void* arg);

int main(int argc, TCHAR* argv[])
{
	DWORD idThreadA;
	HANDLE hThreadA =
	CreateThread(
		NULL,
		0,
		ThreadA,
		NULL,
		0,
		&idThreadA
		);

	if (!SetThreadPriority(hThreadA, THREAD_PRIORITY_IDLE)) {
		printf("Failed to set hThreadA priority");
	}

	DWORD idThreadB;
	HANDLE hThreadB =
		CreateThread(
			NULL,
			0,
			ThreadB,
			NULL,
			0,
			&idThreadB
		);

	if (!SetThreadPriority(hThreadB, THREAD_PRIORITY_TIME_CRITICAL)) {
		printf("Failed to set hThreadB priority");
	}

	// WaitForSingleObject(hThreadA, INFINITE);
	//WaitForSingleObject(hThreadA, 5000); // optional
	//WaitForSingleObject(hThreadB, INFINITE);


	Sleep(1000);
	TerminateThread(hThreadB, 0);
	Sleep(1000);
	TerminateThread(hThreadA, 0);

	return 0;
}

DWORD WINAPI ThreadA(void* arg) {
	while (1) {
		printf("A");
		Sleep(100);
	}
}

DWORD WINAPI ThreadB(void* arg) {
	long counter = 0;
	while (1) {
		printf("B");
		Sleep(100);
		if (++counter == 100) {
			ExitThread(0);
		}
	}
}