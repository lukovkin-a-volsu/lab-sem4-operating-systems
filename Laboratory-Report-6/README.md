# Tasks

ls -l
ls -l /dev
ls -l /sys/devices
ls -l /sys/block
udevadm info --query=all --name=/dev/sda
dd if=/dev/zero of=new_file bs=1024 count=1

<!-- Диски -->
<!-- префикс sd соответствует диску SCSI -- small computer system interface -->
lsscsi

mknod /dev/sda1 b 8 2

sudo /lib/systemd/systemd-udevd

# ls -l

## Первая буква

b -- блочное устройство,
c -- символьное устройство,
p -- устройство канала,
s -- сокет

l for a symbolic link
p for a named pipe
c for a character device
b for a block device
s for a socket
d indicates a directory

## root root

The first "root" represents the owner of the file or directory. In Unix-like operating systems.

The second "root" represents the group ownership of the file or directory.

# sysfs interface

sysfs is a pseudo file system provided by the Linux kernel that exports information about various kernel subsystems, hardware devices, and associated device drivers from the kernel's device model to user space through virtual files.[1] In addition to providing information about various devices and kernel subsystems, exported virtual files are also used for their configuration

# dd

Команда dd копирует данные в блоках фиксированного размера.

bs = 1k -- 1024 byte
bs = 1b -- 512 byte
ibs=size, obs=size -- используется для задавания размеров блока на входе и выходе, применяется если размеры блоков разные, иначе bs
skip=num -- пропускает количество блоков.

# Поиск устройства

- udev
- Поискать в /sys
- Попробовать угадать название на основе команды dmesg (выдает несколько последних сообщений ядра)
- Результат работ mount
- cat /proc/devices чтобы увидеть блочные и символьные устройства, для которых система имеет драйверы

udev -- самый надежный метод, остальные методы, когда он недоступен.
<!-- udevadm info --name=/dev/ttyS1 -->

# lsscsi