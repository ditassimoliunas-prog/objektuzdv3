@echo off
REM ObjektinisUzdavinys v3.0 - Simple Batch Installer
REM This script installs the program to: C:\Program Files\VU\Ditas-Simoliunas

setlocal enabledelayedexpansion

REM Check for admin rights
net session >nul 2>&1
if %errorlevel% neq 0 (
	echo ERROR: This script requires administrator privileges.
	echo Please run this script as Administrator.
	pause
	exit /b 1
)

set INSTALL_DIR=C:\Program Files\VU\Ditas-Simoliunas

echo.
echo ============================================================
echo  ObjektinisUzdavinys v3.0 Installation
echo ============================================================
echo.
echo Installation directory: %INSTALL_DIR%
echo.

REM Create directories
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"
if not exist "%INSTALL_DIR%\documentation" mkdir "%INSTALL_DIR%\documentation"
if not exist "%INSTALL_DIR%\test_data" mkdir "%INSTALL_DIR%\test_data"

echo [1/5] Creating directories... OK

REM Copy executable
if exist "build\Release\programa.exe" (
	copy /y "build\Release\programa.exe" "%INSTALL_DIR%\" >nul
	echo [2/5] Copying programa.exe... OK
) else (
	echo ERROR: programa.exe not found in build\Release\
	pause
	exit /b 1
)

REM Copy documentation
if exist "README.md" copy /y "README.md" "%INSTALL_DIR%\documentation\" >nul
if exist "dokumentacija\latex\refman.pdf" copy /y "dokumentacija\latex\refman.pdf" "%INSTALL_DIR%\documentation\" >nul
echo [3/5] Copying documentation... OK

REM Copy test data files
if exist "Studentai_test_10000.txt" copy /y "Studentai_test_10000.txt" "%INSTALL_DIR%\test_data\" >nul
if exist "Studentai_test_100000.txt" copy /y "Studentai_test_100000.txt" "%INSTALL_DIR%\test_data\" >nul
echo [4/5] Copying test data files... OK

REM Create shortcuts (using PowerShell)
powershell -NoProfile -Command ^
  "$shell = New-Object -ComObject WScript.Shell; " ^
  "$shortcut = $shell.CreateShortcut('%USERPROFILE%\Desktop\ObjektinisUzdavinys v3.0.lnk'); " ^
  "$shortcut.TargetPath = '%INSTALL_DIR%\programa.exe'; " ^
  "$shortcut.WorkingDirectory = '%INSTALL_DIR%'; " ^
  "$shortcut.Save()" 2>nul

REM Create Start Menu folders
set "START_MENU=%USERPROFILE%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs"
if not exist "%START_MENU%\VU\Ditas-Simoliunas" mkdir "%START_MENU%\VU\Ditas-Simoliunas"

REM Create Start Menu shortcuts
powershell -NoProfile -Command ^
  "$shell = New-Object -ComObject WScript.Shell; " ^
  "$shortcut = $shell.CreateShortcut('%START_MENU%\VU\Ditas-Simoliunas\ObjektinisUzdavinys v3.0.lnk'); " ^
  "$shortcut.TargetPath = '%INSTALL_DIR%\programa.exe'; " ^
  "$shortcut.WorkingDirectory = '%INSTALL_DIR%'; " ^
  "$shortcut.Save()" 2>nul

echo [5/5] Creating shortcuts... OK

REM Create uninstaller batch script
echo @echo off > "%INSTALL_DIR%\uninstall.bat"
echo setlocal enabledelayedexpansion >> "%INSTALL_DIR%\uninstall.bat"
echo net session >nul 2>&1 >> "%INSTALL_DIR%\uninstall.bat"
echo if %%errorlevel%% neq 0 ( >> "%INSTALL_DIR%\uninstall.bat"
echo     echo ERROR: Uninstall requires administrator privileges. >> "%INSTALL_DIR%\uninstall.bat"
echo     pause >> "%INSTALL_DIR%\uninstall.bat"
echo     exit /b 1 >> "%INSTALL_DIR%\uninstall.bat"
echo ) >> "%INSTALL_DIR%\uninstall.bat"
echo. >> "%INSTALL_DIR%\uninstall.bat"
echo rmdir /s /q "%INSTALL_DIR%" >> "%INSTALL_DIR%\uninstall.bat"
echo del "%%USERPROFILE%%\Desktop\ObjektinisUzdavinys v3.0.lnk" >> "%INSTALL_DIR%\uninstall.bat"
echo del "%%USERPROFILE%%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\VU\Ditas-Simoliunas\ObjektinisUzdavinys v3.0.lnk" >> "%INSTALL_DIR%\uninstall.bat"
echo rmdir /q "%%USERPROFILE%%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\VU\Ditas-Simoliunas" >> "%INSTALL_DIR%\uninstall.bat"
echo rmdir /q "%%USERPROFILE%%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\VU" >> "%INSTALL_DIR%\uninstall.bat"
echo. >> "%INSTALL_DIR%\uninstall.bat"
echo echo Uninstall complete! >> "%INSTALL_DIR%\uninstall.bat"
echo pause >> "%INSTALL_DIR%\uninstall.bat"

echo.
echo ============================================================
echo Installation complete!
echo ============================================================
echo.
echo Installation directory: %INSTALL_DIR%
echo.
echo Shortcuts created:
echo  - Desktop: ObjektinisUzdavinys v3.0
echo  - Start Menu: VU ^> Ditas-Simoliunas ^> ObjektinisUzdavinys v3.0
echo.
echo To uninstall, run: %INSTALL_DIR%\uninstall.bat
echo.
pause
