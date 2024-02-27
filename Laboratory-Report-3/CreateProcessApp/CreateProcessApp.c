#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main(int argc, TCHAR* argv[])
{
	//https://learn.microsoft.com/en-us/windows/win32/procthread/creating-processes
	//https://learn.microsoft.com/en-us/cpp/code-quality/c6277?view=msvc-170

	//You are creating a new process(notepad.exe) from a parent process(your console application), and let parent process wait for child process to finish.The console window is the main window of your parent process.You can hide and restore is as show below.
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	char* app = "\"C:\\Windows\\notepad.exe\"";

	//"C:\\Program Files\\WindowsApps\\Microsoft.Paint_11.2311.30.0_x64__8wekyb3d8bbwe\\PaintApp\\mspaint.exe"
	//"C:/Program Files/WindowsApps/Microsoft.Paint_11.2311.30.0_x64__8wekyb3d8bbwe/PaintApp/mspaint.exe"
	if (!CreateProcessA(NULL,   // No module name (use command line)
		app,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags dwCreationFlags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		) {
		DWORD errorCode = GetLastError();

		// Print the error code to the console
		printf("\nProcess Creation Error\n");
		printf("Error code: %lu\n", errorCode);
		return 0;
	}


	// Information about the running process
	printf("The first process\n");
	printf("Process id: %d\n", pi.dwProcessId);
	printf("Process descriptor: 0x%p\n", pi.hProcess);
	printf("Primary thread id: %d\n", pi.dwThreadId);
	printf("Primary thread descriptor: 0x%p\n", pi.hThread);

	// Getting priority class of the process
	DWORD priorityClass = GetPriorityClass(pi.hProcess);
	if (priorityClass == 0) {
		printf("Error when getting the priority class of the process: %d\n", GetLastError());
	}
	else {
		printf("Priority class of the process: %d\n", priorityClass);
	}

	if (!TerminateProcess(pi.hProcess, 0)) {
		printf("Process ShutDown Error\n");
		return 0;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	//ShowWindow(GetConsoleWindow(), SW_RESTORE);
	return 0;
}