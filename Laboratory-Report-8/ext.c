#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void AllocateAndFillMemory(size_t, size_t);

#define GB (1024ULL * 1024ULL * 1024ULL)
#define MB (1024ULL * 1024ULL)
#define KB (1024ULL)

int main()
{
  size_t size, chunkSize, limit;
  // size = 1 * GB;
  // chunkSize = 256 * MB;
  // limit = 10 * GB;
  // laptop
  // size = 1ULL * MB;
  // chunkSize = 128ULL * KB;
  // limit = 4LL * GB;

  puts("Min chunkSize in MB: ");
  scanf("%zu", &size); size *= MB;
  puts("Max limit in GB: ");
  scanf("%zu", &limit); limit *= GB;
  system("cls");

  while (size <= limit)
  {
    // printf("Size: %lld GB.\n", size / GB);
    printf("Size: %llu/%llu MB.\n", size / MB, limit / MB);
    AllocateAndFillMemory(size, chunkSize);
    size *= 2ULL;
    chunkSize *= 2ULL;
  }
  return 0;
}

void AllocateAndFillMemory(size_t size, size_t chunkSize)
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

  size_t *arr = address;
  for (size_t i = 0; i < size / sizeof(size); i++)
  {
    arr[i] = i;
    // if (i % chunkSize == 0)
    // printf("Filled %lu kilobytes\n", i / 1024);
  }

  end = GetTickCount();
  elapsed = end - start;
  printf("Elapsed time %lu ms.\n", elapsed);
  VirtualFree(address, 0, MEM_RELEASE);
}
