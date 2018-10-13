@echo off
if "%EGCC_BAT%" == "YES" GOTO END
set EGCC_BAT=YES

rem library enviroment vars
set GCCDIR=C:\programs\progs\mingw-x86-sjlj-8
path=%path%;%GCCDIR%\bin

rem compiler flags
set OFLAGS=-fdiagnostics-color=never -m32 -march=prescott -mtune=generic -Os -fomit-frame-pointer -fno-exceptions -fno-asynchronous-unwind-tables -Wno-narrowing -ffunction-sections -Wno-pointer-arith  -fno-strict-overflow -fno-builtin-strlen -Wno-multichar -fno-math-errno -g
set OCCFLG=%OFLAGS% -fno-rtti -std=gnu++1z -Wno-invalid-offsetof -Wno-literal-suffix -Wno-pmf-conversions -fno-sized-deallocation 
set PUSH_ARG=-mno-accumulate-outgoing-args  -mno-stack-arg-probe -mpreferred-stack-boundary=3
set WFLAGS=-DUNICODE -D_UNICODE -DASSERT_NOWIDE -D_WIN32_WINNT=0x0502 -D_WIN32_IE=0x0603

rem combined compiler flags
set CFLAGS=%OFLAGS% %WFLAGS%
set CCFLAGS=%OCCFLG% %WFLAGS%
set CFLAGS2=%CFLAGS% %PUSH_ARG%
set CCFLAGS2=%CCFLAGS% %PUSH_ARG%

rem linker flags
set LFLAGS=-s -Wl,-gc-sections

:END
@echo on
