@echo off
nasm -f win64 asmKernel.asm
gcc -c cfile.c -o cfile.obj -m64
gcc cfile.obj asmKernel.obj -o cfile.exe -m64 -mconsole
cfile.exe
pause