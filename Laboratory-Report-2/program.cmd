@echo off

if "%1" == "" (
  echo Paths aren't set
  goto :EOF
)

:loop
if "%1" == "" goto end
del /S "%1\*.tmp" > protocol.txt
shift
goto :loop
:end

goto :EOF