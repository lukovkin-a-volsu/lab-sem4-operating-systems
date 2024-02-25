@echo off
rem main program

echo main %0
pause

echo %0
echo %1
echo %2
echo %3
echo %4
echo %5
echo %6
echo %7
echo %8
echo %9
echo end
shift /0
shift /0
echo %9

call package

echo end main

@REM REM Used to disable echo of command entry and current working directory
@REM @echo off

@REM REM Displaying the full path (absolute Path) of this file
@REM echo %~f0

@REM REM Displaying the timestamp of creation of this file
@REM echo %~t0