@echo off
if exist "../" (
  for /D /R %%f in ("../*") do echo %%f
) else (
    echo the catalog doesn't exist.
)