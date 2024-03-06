#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

// CREATE PROCESS
int main(int argc, TCHAR* argv[])
{
	// ABOVE_NORMAL_PRIORITY_CLASS (0x00008000): 32768
	// BELOW_NORMAL_PRIORITY_CLASS (0x00004000): 16384
	// HIGH_PRIORITY_CLASS (0x00000080): 128
	// IDLE_PRIORITY_CLASS (0x00000040): 64
	// NORMAL_PRIORITY_CLASS (0x00000020): 32
	// REALTIME_PRIORITY_CLASS (0x00000100): 256

	//https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getpriorityclass
	//https://learn.microsoft.com/en-us/windows/win32/procthread/creating-processes
	//https://learn.microsoft.com/en-us/cpp/code-quality/c6277?view=msvc-170
	STARTUPINFO si;
	STARTUPINFO si1;
	PROCESS_INFORMATION pi;
	PROCESS_INFORMATION pi1;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si1, sizeof(si1));
	si1.cb = sizeof(si1);
	ZeroMemory(&pi1, sizeof(pi1));

	//char* app = "\"C:/Windows/notepad.exe\"";
	//char* app = "\"C:/Program Files/WindowsApps/Microsoft.Paint_11.2311.30.0_x64__8wekyb3d8bbwe/PaintApp/mspaint.exe\"";
	char* app = "C:\\Users\\User\\AppData\\Local\\Microsoft\\WindowsApps\\mspaint.exe";
	char* app1 = "cmd";

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
	SetPriorityClass(pi.hProcess, HIGH_PRIORITY_CLASS);

	if (!CreateProcessA(NULL,   // No module name (use command line)
		app1,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		CREATE_NEW_CONSOLE,              // No creation flags dwCreationFlags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si1,            // Pointer to STARTUPINFO structure
		&pi1)           // Pointer to PROCESS_INFORMATION structure
		) {
		DWORD errorCode = GetLastError();

		// Print the error code to the console
		printf("\nProcess Creation Error\n");
		printf("Error code: %lu\n", errorCode);
		return 0;
	}
	SetPriorityClass(pi1.hProcess, IDLE_PRIORITY_CLASS);


	// Information about the running process
	printf("The first process\n");
	printf("Process id: %d\n", pi.dwProcessId);
	printf("Process descriptor: 0x%p\n", pi.hProcess);
	printf("Primary thread id: %d\n", pi.dwThreadId);
	printf("Primary thread descriptor: 0x%p\n", pi.hThread);
	// Getting priority class of the first process
	DWORD priorityClass = GetPriorityClass(pi.hProcess);
	if (priorityClass == 0) {
		printf("Error when getting the priority class of the first process: %d\n", GetLastError());
	}
	else {
		printf("Priority class of the first process: %d\n", priorityClass);
	}

	if (!TerminateProcess(pi.hProcess, 0)) {
		printf("The first process shutdown error\n");
		return 0;
	}

	// Information about the running process
	printf("The second one\n");
	printf("Process id: %d\n", pi1.dwProcessId);
	printf("Process descriptor: 0x%p\n", pi1.hProcess);
	printf("Primary thread id: %d\n", pi1.dwThreadId);
	printf("Primary thread descriptor: 0x%p\n", pi1.hThread);
	// Getting priority class of the second one
	DWORD priorityClass1 = GetPriorityClass(pi1.hProcess);
	if (priorityClass1 == 0) {
		printf("Error when getting the priority class of the second process: %d\n", GetLastError());
	}
	else {
		printf("Priority class of the second process: %d\n", priorityClass1);
	}

	if (!TerminateProcess(pi1.hProcess, 0)) {
		printf("The second process shutdown error\n");
		return 0;
	}

	return 0;
}