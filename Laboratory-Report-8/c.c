#include <windows.h>
#include <stdio.h>

void ErrorHandler(HANDLE);
void PrintView(char *, DWORD);

/*
Описание того что происходит (если забуду):
запуская два экземпляра исполняемого файла, вводятся символы
второй может получить их вывод с помощью p,
во втором вводя символы, сначала будут убераться имеющиеся
потом добавляться новые уже
и в первом с помощью p они уже будут выводиться
*/

int main()
{
  HANDLE hFile;
  char *pFileView;
  const char *FILE_NAME = "task_c.txt"; /* uid for mapping file */

  hFile = CreateFileMappingA(
      INVALID_HANDLE_VALUE, // указатель на объект файла
      NULL,                 // атрибуты безопасности
      PAGE_READWRITE,       // тип доступа
      0,                    // размер старшего порядка файла
      1024,                 // размер младшего порядка файла
      FILE_NAME             // уникальный идентификатор проецируемого файла
  );
  ErrorHandler(hFile);

  pFileView = MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
  ErrorHandler(pFileView);

  char c;
  while (1)
  {
    puts("Enter character:");
    c = getchar();
    while (getchar() != '\n')
      ;
    if (c == 'q')
      break;
    if (c == 'p')
    {
      printf("View file content: %s\n", pFileView);
      continue;
    }
    *pFileView++ = c;
  }

  printf("View file content: %s\n", pFileView);

  UnmapViewOfFile(pFileView);
  ErrorHandler(pFileView);

  CloseHandle(hFile);

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

void PrintView(char *view, DWORD max)
{
  DWORD i = 0;
  while (i < max || view[i] == '\0')
  {
    printf("%c", view[i]);
  }
  puts("\n");
}