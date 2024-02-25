@echo off
rem MYCOPY.BAT копирует произвольное число файлов
rem в каталог.
rem Используется следующий синтаксис:
rem mycopy dir файл1 файл2 ...
set todir=%1
:getfile
shift
if "%1"=="" goto end
copy %1 %todir%
goto getfile
:end
set todir=
echo Program's finished