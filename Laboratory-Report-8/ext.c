#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void AllocateAndFillMemory(long long size, long long chunkSize);

#define GB (1024LL*1024LL*1024LL)
#define MB (1024LL*1024LL)
#define KB (1024LL)

int main()
{
  long long size, chunkSize, limit;
  size = 1 * GB;
  chunkSize = 256 * MB;
  limit = 10 * GB;
  // laptop
  // size = 256 * KB;
  // chunkSize = 128 * KB;
  // limit = 2 * GB;

  while (size < limit)
  {
    printf("Size: %lld GB.\n", size / GB);
    AllocateAndFillMemory(size, chunkSize);
    size *= 2;
    chunkSize *= 2;
  }
  return 0;
}

void AllocateAndFillMemory(long long size, long long chunkSize)
{
  LPVOID address;
  DWORD start, end, elapsed;

  address = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if (address == NULL)
  {
    puts("Allocation virtual and physical memory error.\n");
    return;
  }

  start = GetTickCount();

  for (int i = 0; i < size; i++)
  {
    ((char *)address)[i] = rand() % 256;
    
    // if (i % chunkSize == 0)
      // printf("Filled %lu kilobytes\n", i / 1024);
  }

  end = GetTickCount();
  elapsed = end - start;
  printf("Elapsed time %lu ms.\n", elapsed);
  VirtualFree(address, 0, MEM_RELEASE);
}
