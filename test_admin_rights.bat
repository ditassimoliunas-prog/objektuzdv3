@echo off
REM Test script to verify admin rights are working
REM This will attempt to run programa.exe and should trigger UAC if admin rights are required

setlocal enabledelayedexpansion

echo ============================================================
echo Testing ObjektinisUzdavinys with Admin Rights
echo ============================================================
echo.
echo This test will run programa.exe, which should automatically
echo request administrator privileges through Windows UAC.
echo.
echo If you see a UAC prompt, the admin rights are working!
echo.
pause

REM Run the program
"out\build\x64-Debug\programa.exe"

echo.
echo Test completed.
pause
