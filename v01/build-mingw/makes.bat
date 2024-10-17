@echo off
setlocal enabledelayedexpansion
setlocal enableextensions
cls

set MAKE_CMD=%1
set MAKE_ARGS=
shift /1

:args_loop
if not "%1" == "" (
	set MAKE_ARGS=%MAKE_ARGS% %1
	shift /1
	goto :args_loop
)

make -f commands.mak %MAKE_CMD% "ARGS=%MAKE_ARGS%"

endlocal
