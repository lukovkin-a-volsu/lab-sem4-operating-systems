#include <stdio.h>
#include <windows.h>

int main()
{
  // MEM_RESERVE -- параметр, резервирующий область виртуального адресного пространства без выделения физической.
  // MEM_COMMIT -- параметр, выделяющий физическую память в оперативной памяти или в файле подкачки.

  // allocated memory size (bytes)
  SIZE_T regionSize = 4096;

  LPVOID address = VirtualAlloc(NULL, regionSize, MEM_RESERVE, PAGE_READWRITE);
  if (address == NULL)
  {
    puts("Allocation virtual memory error\n");
    return 1;
  }

  // physical memory allocation
  if (!VirtualAlloc(address, regionSize, MEM_COMMIT, PAGE_READWRITE))
  {
    puts("Allocation physical memory error\n");
    VirtualFree(address, 0, MEM_RELEASE);
    return 1;
  }

  puts("Success.");
  VirtualFree(address, 0, MEM_RELEASE);
  system("pause");

  return 0;
}
