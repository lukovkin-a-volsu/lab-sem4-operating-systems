#include <stdio.h>
#include <windows.h>
#include <string.h>

void ErrorHandler(HANDLE);

int main()
{
  HANDLE hFile, hFileMapping;
  char *pFileView = "";
  const char *FILE_NAME = "task_b.txt";
  const char *DATA_TO_WRITE = "Hello, world!            ";
  const char *MODIFIED_DATA = "Hello, o brave new world!";
  WINBOOL isFileWritten, isUnmappedView;

  // File creation and data writing
  hFile = CreateFileA(
      // (LPCSTR)FILE_NAME,
      FILE_NAME,
      GENERIC_READ | GENERIC_WRITE,
      0,
      NULL,
      CREATE_ALWAYS,
      FILE_ATTRIBUTE_NORMAL,
      NULL);
  ErrorHandler(hFile);

  isFileWritten = WriteFile(hFile, DATA_TO_WRITE, strlen(DATA_TO_WRITE), NULL, NULL);
  ErrorHandler(&isFileWritten);

  hFileMapping = CreateFileMappingA(
      hFile,
      NULL,
      PAGE_READWRITE,
      0,
      strlen(DATA_TO_WRITE),
      // (LPCSTR)FILE_NAME
      FILE_NAME);
  ErrorHandler(hFileMapping);
  pFileView = MapViewOfFile(hFileMapping,
                            FILE_MAP_ALL_ACCESS,
                            0,
                            0,
                            strlen(DATA_TO_WRITE));
  ErrorHandler(pFileView);

  printf("File content: %s\n", pFileView);
  strcpy(pFileView, MODIFIED_DATA);
  printf("Modified file content: %s\n", pFileView);

  isUnmappedView = UnmapViewOfFile(pFileView);
  ErrorHandler(&isUnmappedView);
  CloseHandle(hFile);
  CloseHandle(hFileMapping);

  return 0;
}

void ErrorHandler(HANDLE h)
{
  if (h == NULL)
  {
    printf("Error %d: ", GetLastError());
    system("pause");
    exit(1);
  }
}