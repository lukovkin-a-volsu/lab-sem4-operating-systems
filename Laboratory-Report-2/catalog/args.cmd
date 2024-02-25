@echo off
:loop
if "%1" EQU "" goto :EOF
echo %1
shift
goto :loop