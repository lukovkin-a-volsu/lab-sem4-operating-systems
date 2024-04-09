# ps  

Tool that allows you to view information about the processes running on your Linux system

## Примеры

* ps 
* ps m (просмотр потоков)
* ps m -o pid,tid,command
* ps -o pid,min_flt,maj_flt pid (мажорные ошибки большие)
 
# top

## Примеры

* top
* top -p pid1 [-p pid2, ...] (отследить один или несколько процессов с течением времени)

## Манипуляции

* Пробел -- Немедленно обновить экран
* M -- Сортировка по количеству используемой резидентной памяти
* T -- Сортировка по общему применению ЦПУ
* P -- Сортировка по текущему применению ЦПУ
* u -- Отобразить процессы только для одного пользователя
* f -- Другие параметры отобраажения
* ? -- Статистика использования всех команд top
* H -- Показать потоки

## Назначения

* PID: The unique process ID
* USER: The user name of the task owner
* PR: The priority of the task
* NI: The nice value of the task
* VIRT: The total virtual memory used by the task
* RES: The amount of physical memory a process is consuming
* SHR: The shared memory size used by a task

RES represents non-swapped physical memory. VIRT indicates the total amount of virtual memory used by the task

# lsof (list open files)

## Примеры

* lsof /mnt/d
* lsof -p PID

## Назначения

FD - file descriptor

* \# - The number in front of flag(s) is the file descriptor number of used by the process to associated with the file
* u - File open with Read and Write permission
* r - File open with Read permission
* w - File open with Write permission
* W - File open with Write permission and with Write Lock on entire file
* mem - Memory mapped file, usually for share library

# strace

## Примеры

strace cat /dev/null

## fork

fork() -- системный вызов в Unix-подобных операционных системах, создающий новый процесс (потомок), который является практически полной копией процесса-родителя, выполняющего этот вызов

## brk

brk() and sbrk() change the location of the program break, which defines the end of the process's data segment.

## Демон

Daemon -- In multitasking computer operating systems, a daemon is a computer program that runs as a background process, rather than being under the direct control of an interactive user.

## Показатели

Системный вызов запуска новой команды:
execve("/usr/bin/cat", ["cat", "/dev/null"], 0x7fff6fc30c08 /* 26 vars */) = 0

3 в следующем случае означает успешное заввершение:
openat(AT_FDCWD, "/dev/null", O_RDONLY) = 3

Выполнение чтения из устройства /dev/null, обладает файловым дескриптором 3:
read(3, "", 131072)                     = 0

Закрытия файлового дескриптора:
close ...

Выход:
exit_group(0)                           = ?

# ltrace

Отслеживает вызовы совместно используемых библиотек. Результаты напоминают strace. 
Не отслеживает ничего на уровне ядра. Вызов библиотек намного больше чем системных вызовов.

# time

* real -- время, затраченное на полное выполнение программы от начала до конца
* sys -- время, которое затрачивает ядро на выполнение процесса
* user -- время (секунды), которое ЦП потратил на выполнение собственного кода программы

# Настройка приоритетов процесса

-20 -- высший приоритет, 20 -- низший

The difference in the values displayed for "pri" (ps) and "pr" (top) for the same process can be due to several reasons:

Different Calculations: Both "pri" and "pr" represent the process's priority, but they use slightly different calculation methods. "ps" typically shows the nice value combined with the process's scheduling information, resulting in a higher value (like 80). "top" often displays the adjusted nice value, which can be lower (like 20).

Command Options: The specific options used with ps and top can affect the displayed priority value. ps -l provides a more detailed output format, while top focuses on real-time resource usage. Using the -o pri option with top might give a value closer to what ps -l displays.

# renice

Значение относительного приоритета (NI)
Когда необходимо, чтобы некоторый процесс не замедлял работу в интерактивном сеансе, можно сделать, чтобы он работал тогда, когда другим нечего делать, для этого нужно установить значение относительного приоритета 20 (renice 20 pid)

# uptime

Среднее значение нагрузки является средним количеством процессом, которые в данный момент готовы к запуску. Только те процессы, которые действительно что-то выполняют, влияют на среднее значение загрузки

## Показатели

1) Текущее время 22:42:15 up
2) Как долго запущена система 1:42
3) Сколько пользователей авторизовано 0
4) Средняя нагрузка за 1, 5 и 15 минут 0.0, 0.0, 0.0

# Как работает память

MMU -- модуль управления памятью, содержащийся в процессоре, который переводит виртуальные адреса памяти, используемые процессами в реальные. Ядро помогает MMU, разбивая память на маленькие фрагменты, называемые страницами и также содержит структуру данных называющейся таблицей страниц.

# free

Один из самых простых способов проверить состояние системной памяти в целом.

# cat /proc/meminfo

Файл содержащий информацию о системной памяти.

# vmstat

vmstat (virtual memory statistics) is a computer system monitoring tool that collects and displays summary information about operating system memory, processes, interrupts, paging and block I/O.

## Примеры

* vmstat
* vmstat 2 (обновление каждые 2 секунды)

## Назначения

* swpd: Total amount of virtual memory used by kswapd (kswapd is a process that manages virtual memory and swap space in response to memory demands that are greater than the amount of memory available for all processes), сколько памяти система переместила на диск в Кбайтах

In most cases, swpd should be zero unless the physical CPU is out of space

* b: The number of processes in uninterruptible sleep
  
--swap--:

* si: Amount of memory swapped in from disk (входящая подкачка)
* so: Amount of memory swapped to disk (выходящая подкачка)
* free: Total free memory
* buff: Total memory temporarily used as a data buffer

--cpu--:

* us: The percentage of time spent on non-kernel processes
* sy: The percentage of time spent on kernel processes
* id: The percentage of time spent idle (в бездействии)
* wa: The percentage of time spent waiting for input/output (в ожидании ввода\вывода)

--io--:

* bi: blocks in
* bo: blocks out

# iostat

The vmstat command is useful for obtaining an overall picture of CPU, paging, and memory usage. The iostat command is useful for determining disk and CPU usage. Подобно vmstat, без параметров показывает статистику за все время работы компьютера.

## Примеры

* iostat
* iostat 2
* iostat -d 2 (только информацию о девайсе)
* iostat -p ALL (с информацией о разделах)

## Назначения

* tps (transfers per second) -- количество пересылок данных с секунду
* kB_read/s -- среднее кол-во считанных КБ в секунду
* kB_wrtn/s -- среднее кол-во записанных КБ в секунду
* kB_read -- общее количество считанных КБ
* kB_wrtn -- общее количество записанных КБ

# iotop

Для более глубокого представления, чтобы посмотреть ресурсы ввода\вывода, используемые отдельными процессами. Отображает потоки вместо процессов

## Назначения

* PRIO -- приоритет ввода\вывода (влияет насколько быстро ядро распределяет операции чтения и записи для процесса)
  * be -- наилучший объем работы (ядро старается справедливо распределить время)
  * rt -- реальное время (ядро планирует в реальном времени перед любым другим классом ввода\вывода)
  * idle -- бездействие (выполняет ввод\вывод этого класса, когда не был выполнен никакой другой)

Можно изменить приоритет с помощью ionice

# pidstat

Позволяет в стиле vmstat отследить процессы с течением времени.

## Примеры

* sudo pidstat
* sudo pidstat -r 
* sudo pidstat -d

## Манипуляции

* -r: отслеживать память
* -d: отслеживать диск