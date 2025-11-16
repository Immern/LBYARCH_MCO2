@echo off
nasm -f win64 asmhello.asm
gcc -c Test.c -o Test.obj -m64
gcc Test.obj asmhello.obj -o Test.exe -m64 -mconsole
Test.exe
pause