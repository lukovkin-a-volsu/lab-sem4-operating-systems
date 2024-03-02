@echo off

echo.
if "%1"=="" (
  echo paths aren't set
  goto :EOF
)

if exist protocol.txt del protocol.txt

:loop
if "%1"=="" goto end
echo %1 is cleaning..
echo Y | del /S /P "%1\*.tmp" >> protocol.txt
shift
goto loop
:end