@echo off

set param=%1

if /I not "%param%"=="Debug" (if /I not "%param%"=="Release" set param=Release)

echo copy %1
xcopy include ..\Install\include\  /Y /S /I
copy ..\Bin\x64_%param%\*.lib ..\Install\ /Y
copy ..\Bin\x64_%param%\*.dll ..\Install\ /Y
