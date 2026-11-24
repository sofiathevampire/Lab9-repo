@echo off
ECHO Building...
cmake -S . -B build >NUL
cmake --build build
IF %ERRORLEVEL% NEQ 0 (
    ECHO Build failed.
    EXIT /B 1
)

SET EXE=build\lab9.exe

ECHO Test 1 - encrypt a string, print to console
%EXE% abcd1234 -s "Test data to be encrypted"

ECHO Test 2 - encrypt a text file
%EXE% abcd1234 -f "inputFile.txt"

ECHO Test 3 - same as Test 2, positional key after the flag
%EXE% -f "inputFile.txt" abcd1234

ECHO Test 4 - same as Test 2, long flag form
%EXE% abcd1234 --file "inputFile.txt"

ECHO Test 5 - same as Test 2, explicit mode
%EXE% abcd1234 -f "inputFile.txt" -m en

ECHO Test 6 - encrypt inputFile.txt to a .bin file
%EXE% abcd1234 -f "inputFile.txt" -m en --output "encrypted.bin"

ECHO Test 7 - decrypt the .bin file created above, print to console
%EXE% abcd1234 -f "encrypted.bin" -m de --output print

ECHO Test 8 - decrypt the .bin file created above, write to a .txt file
%EXE% abcd1234 -f "encrypted.bin" -m de --output "decrypted.txt"

ECHO Test 9 - wrong key should fail cleanly, not crash
%EXE% wrongkey -f "encrypted.bin" -m de
