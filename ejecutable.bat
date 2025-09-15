@echo off
cd C:\Scripts\SRC
gcc -o cifrado cifrado.c
move ".\cifrado.exe" "C:\Scripts\BIN"
pause