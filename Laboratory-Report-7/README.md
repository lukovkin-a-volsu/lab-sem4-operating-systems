# Theory

Традиционная таблица -- MBR
Новый стандарт -- GPT (Globally Unique Identifier Partition Table)

parted -- терминал (MBR, GPT)
gparted -- GUI (MBR, GPT)
fdisk -- терминал (MBR)
gdisk -- терминал (GPT)

Предельное количество основных разделов в MBR равно четырем. Если необходим о больше четырех, то один обозначается за расширенный раздел. Который делится на логические разделы.
В parted изменения происходят во время ввода команды. В fdisk изменения происходят после выхода из нее. 

dmesg (diagnostic messages) is a command on most Unix-like operating systems that prints the message buffer of the kernel

FAT -- windows
ISO 9660 -- CD-ROM
HFS+ -- apple

Btrfs (pronounced as "better F S", "butter F S", "b-tree F S", or B.T.R.F.S.) is a computer storage format that combines a file system based on the copy-on-write (COW) principle with a logical volume manager (not to be confused with Linux's LVM), developed together

NTFS, which stands for NT file system and the New Technology File System, is the file system that the Windows NT operating system (OS) uses for storing and retrieving files on hard disk drives (HDDs) and solid-state drives (SSDs).

NTFS and FAT32 file systems differ in the following ways: The FAT32 file system cannot store individual files larger than 4 GB, while the NTFS file system can. Compared to FAT32, the NTFS file system has higher disk utilization and can manage disk space more effectively.

Если по каким-либо причинам невозможно демонтировать
файловую систему до выхода из операционной системы, обязательно запустите
сначала команду sync

1. Создание файловой системы:
    - Сначала необходимо определить устройство, на котором будет создаваться файловая система. Обычно это блочное устройство (например, /dev/sda, /dev/sdb и т. д.).
    - Выполнить команду mkfs с указанием необходимого типа файловой системы (например, ext4) и устройства. Например: mkfs -t ext4 /dev/sdb1. Это создаст файловую систему на указанном устройстве.

2. Монтирование файловой системы:
    - Создайте точку монтирования (обычно это каталог на вашей системе).
    - Выполните команду mount для монтирования созданной файловой системы на точку монтирования. Например: mount /dev/sdb1 /mnt/data. Теперь созданная файловая система будет доступна для использования в указанной точке монтирования.


# Commands

1. Просмотр таблицы разделов
 - parted -l
 - fdisk -l (если необходимо точно узнать идентификатор системы для таблицы MBR)
 - dmesg (отладочный результат при первичном чтении MBR)
 - cat /proc/partitions
 - ls /sys/block
 - ls /dev
2. Принудительно перезагрузить таблицу разделов
 - blockdev --rereadpt /dev/nvme0n1
3. Узнать где начинается наш раздел (в случае SSD считывается порциями 4096 байт)
 - cat /sys/block/nvme0n1/nvme0n1p3/start
4. Создание файловой системы
 - mkfs -t ext4 /dev/sdf2
 - ls -l /sbin/mkfs.* (что скрывается за лицевой стороной mkfs)
5. Монтирование файловой системы
 - mount -t ext4 /dev/sdf2 /home/extra (обычно не используется -t ext4, потому как система сама способна догадаться о типе)
6. Демонтирование системы
 - umount mountpoint
7. Посмотреть список устройств (вместе с UUID)
 - blkid
8. Смонтировать файловую систему по UUID
 - mount UUID=a9011c2b-1c03-4288-b3fe-8ba961ab0898 /home/extra
9. Присоединить недавно смонтированную ф.с. к той же mountpoint, изменив параметры
 - mount -n -o remount /
10. Таблица файловой системы /etc/fstab
 - cat /etc/fstab (список ф.с. всегда хранится здесь)
 - mount -a (смонтировать всё)
11. Мощность файловой системы
 - df
 - du -s * (показывает итоговую сумму медиафайлов, пожирающих пространства от df)
12. ОПАСНО
 - fsck (инструмент проверки файловой системы)
 - e2fsck -fy /dev/disk_drive (очистить журнал в файловой системе ext3 или ext4)
13. Область подкачки
 - free
14. ОПАСНО. Использование раздела в качестве области подкачки 
 - убедиться, что раздел пуст
 - mkswap device (помещает в раздел сигнатуру области подкачки)
 - swapon dev (зарегистрировать область с помощью ядра)
 - /dev/sda5 none swap sw 0 0 (пример такой записи, в которой в качестве раздела подкачки
использовано устройство /dev/sda5)
15. Использование файла в качестве области подкачки
 - dd if=/dev/zero of=swap_file bs=1024k count=num_mb
 - mkswap swap_file
 - swapon swap_file
 16. Вывод дескрипторов каталогов
  ls -i


# Parameters

## Параметры монтирования
* -t -- задает тип файловой системы
* -r -- монтирование в режиме "только для чтения"
* -n -- гарантирует, что команда mount не будет пытаться обновить базу данных монтирования

## Длинные параметры монтирования
mount -t vfat /dev/hda1 /dos -o ro,conv=auto

* exec, noexec -- включает или отключает исполнение команд над файловой системой;
* suid, nosuid -- включает или отключает команды setuid (установка идентификатора пользователя);
* ro -- монтирует файловую систему в режиме «только чтение» (подобно короткому параметру -r);
* rw -- монтирует файловую систему в режиме «чтение-запись»;
* conv=rule (для файловых систем на основе FAT) — конвертирует содержащиеся в файлах символы перевода строки, в зависимости от атрибута rule, который может принимать значения binary, text или auto.