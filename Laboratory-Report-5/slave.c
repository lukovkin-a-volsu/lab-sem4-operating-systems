#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

HANDLE hEvent;

int main()
{
  // EVENT_ALL_ACCESS: Полный доступ к событию. Это позволяет вызывать все функции, которые работают с событиями, такие как SetEvent, ResetEvent, WaitForSingleObject и PulseEvent.
  // EVENT_MODIFY_STATE: Разрешает изменение состояния события. Это позволяет вызывать функции SetEvent и ResetEvent.
  // EVENT_READ_CONTROL: Разрешает чтение информации о безопасности события.
  // EVENT_WAIT_ACCESS: Разрешает ожидание события. Это позволяет вызывать функции WaitForSingleObject и WaitForMultipleObjects.
  // TRUE: Дескриптор события наследуется дочерними процессами.
  // FALSE: Дескриптор события не наследуется дочерними процессами.
  hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, "MyEvent");
  if (hEvent == NULL)
  {
    printf("OpenEvent failed: %d\n", GetLastError());
    return 1;
  }

  while (1)
  {
    // Вводим символ
    char c = getchar();

    // Отображаем символ
    printf("%c", c);

    // Сигнализируем MASTER
    SetEvent(hEvent);
  }

  CloseHandle(hEvent);
  return 0;
}
