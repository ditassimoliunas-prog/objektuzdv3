; ObjektinisUzdavinys v3.0 Setup Script (NSIS)
; Author: Ditas Simoliunas
; Version: 3.0

!include "MUI2.nsh"
!include "x64.nsh"

; Name and file
Name "ObjektinisUzdavinys v3.0"
OutFile "ObjektinisUzdavinys_v3.0_Setup.exe"
InstallDir "$PROGRAMFILES\VU\Ditas-Simoliunas"

; Request admin rights
RequestExecutionLevel admin

; MUI Settings
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Lithuanian"

; Installer sections
Section "Install"
  SetOutPath "$INSTDIR"

  ; Copy main executable (HIDDEN - ne desktop shortcut)
  File "..\out\build\x64-Debug\programa.exe"

  ; Copy documentation
  SetOutPath "$INSTDIR\documentation"
  File "..\README.md"
  File "..\refman.pdf"

  ; Copy test data files from Studentai_test folder
  SetOutPath "$INSTDIR\Studentai_test"
  File "..\Studentai_test\studentai_10000.txt"
  File "..\Studentai_test\studentai_100000.txt"

  ; Create desktop shortcut
  CreateShortcut "$DESKTOP\ObjektinisUzdavinys v3.0.lnk" "$INSTDIR\programa.exe" "" "$INSTDIR\programa.exe" 0

  ; Create Start Menu shortcut
  CreateDirectory "$SMPROGRAMS\VU\Ditas-Simoliunas"
  CreateShortcut "$SMPROGRAMS\VU\Ditas-Simoliunas\ObjektinisUzdavinys v3.0.lnk" "$INSTDIR\programa.exe" "" "$INSTDIR\programa.exe" 0
  CreateShortcut "$SMPROGRAMS\VU\Ditas-Simoliunas\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\VU\Ditas-Simoliunas\Documentation.lnk" "$INSTDIR\documentation\refman.pdf" "" "$INSTDIR\documentation\refman.pdf" 0

  ; Ensure only one desktop shortcut exists (remove any auto-generated ones)
  Delete "$DESKTOP\programa.lnk"
  Delete "$DESKTOP\Studento_Programa.lnk"

  ; Write uninstaller
  WriteUninstaller "$INSTDIR\uninstall.exe"

  ; Write registry for Add/Remove Programs
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ObjektinisUzdavinys" "DisplayName" "ObjektinisUzdavinys v3.0"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ObjektinisUzdavinys" "UninstallString" "$INSTDIR\uninstall.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ObjektinisUzdavinys" "DisplayVersion" "3.0"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ObjektinisUzdavinys" "Publisher" "Ditas Simoliunas"

  MessageBox MB_OK "Installation complete!$\n$\nProgram installed to:$\n$INSTDIR$\n$\nShortcuts created on Desktop and Start Menu."
SectionEnd

; Uninstaller section
Section "Uninstall"
  ; Remove executable and documentation
  Delete "$INSTDIR\programa.exe"
  Delete "$INSTDIR\README.md"
  Delete "$INSTDIR\documentation\refman.pdf"

  ; Remove test data
  Delete "$INSTDIR\test_data\Studentai_test_10000.txt"
  Delete "$INSTDIR\test_data\Studentai_test_100000.txt"

  ; Remove directories
  RMDir "$INSTDIR\documentation"
  RMDir "$INSTDIR\test_data"
  RMDir "$INSTDIR"

  ; Remove shortcuts
  Delete "$DESKTOP\ObjektinisUzdavinys v3.0.lnk"
  Delete "$SMPROGRAMS\VU\Ditas-Simoliunas\ObjektinisUzdavinys v3.0.lnk"
  Delete "$SMPROGRAMS\VU\Ditas-Simoliunas\Uninstall.lnk"
  Delete "$SMPROGRAMS\VU\Ditas-Simoliunas\Documentation.lnk"
  RMDir "$SMPROGRAMS\VU\Ditas-Simoliunas"
  RMDir "$SMPROGRAMS\VU"

  ; Remove registry entries
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ObjektinisUzdavinys"

  MessageBox MB_OK "Uninstall complete!"
SectionEnd
