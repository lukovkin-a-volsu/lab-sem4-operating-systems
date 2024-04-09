#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

HANDLE hEvent;

int main()
{
  // Указывает на атрибуты безопасности события. Если этот параметр равен NULL, то событие создается с атрибутами безопасности по умолчанию
  // TRUE: Событие сбросом вручную. Это означает, что событие остается в установленном состоянии, пока оно не будет сброшено вручную с помощью функции ResetEvent.
  // FALSE: Событие сбросом автоматически. Это означает, что событие автоматически сбрасывается в исходное состояние после того, как один или несколько потоков сигнализируют о его наступлении.
  // TRUE: Событие устанавливается в начальное состояние.
  // FALSE: Событие сбрасывается в начальное состояние.
  hEvent = CreateEvent(NULL, FALSE, FALSE, "MyEvent");
  if (hEvent == NULL)
  {
    printf("CreateEvent failed: %d\n", GetLastError());
    return 1;
  }

  while (1)
  {
    // Ждем события от SLAVE
    WaitForSingleObject(hEvent, INFINITE);

    // Отображаем символ
    printf("*");

    // Сброс события
    ResetEvent(hEvent);
  }

  CloseHandle(hEvent);
  return 0;
}
