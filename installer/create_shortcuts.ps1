# ObjektinisUzdavinys v3.0 - Create Shortcuts (PowerShell)
# Usage: powershell -ExecutionPolicy Bypass -File create_shortcuts.ps1

param(
	[string]$InstallDir = "C:\Program Files\VU\Ditas-Simoliunas",
	[bool]$CreateDesktop = $true,
	[bool]$CreateStartMenu = $true
)

# Check for admin rights
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if (-not $isAdmin) {
	Write-Host "ERROR: This script requires administrator privileges!"
	Write-Host "Please run PowerShell as Administrator."
	exit 1
}

# Verify installation directory exists
if (-not (Test-Path $InstallDir)) {
	Write-Host "ERROR: Installation directory not found: $InstallDir"
	exit 1
}

$shell = New-Object -ComObject WScript.Shell

# Create Desktop Shortcut
if ($CreateDesktop) {
	$desktopPath = [Environment]::GetFolderPath('Desktop')
	$shortcutPath = "$desktopPath\ObjektinisUzdavinys v3.0.lnk"

	$shortcut = $shell.CreateShortcut($shortcutPath)
	$shortcut.TargetPath = "$InstallDir\programa.exe"
	$shortcut.WorkingDirectory = $InstallDir
	$shortcut.Description = "ObjektinisUzdavinys v3.0 - Student Management System"
	$shortcut.IconLocation = "$InstallDir\programa.exe,0"
	$shortcut.Save()

	Write-Host "[OK] Desktop shortcut created: $shortcutPath"
}

# Create Start Menu Shortcuts
if ($CreateStartMenu) {
	$startMenuBase = "$env:APPDATA\Microsoft\Windows\Start Menu\Programs"
	$vuMenuPath = "$startMenuBase\VU\Ditas-Simoliunas"

	# Create folders
	if (-not (Test-Path $vuMenuPath)) {
		New-Item -ItemType Directory -Path $vuMenuPath -Force | Out-Null
	}

	# Main program shortcut
	$programShortcut = "$vuMenuPath\ObjektinisUzdavinys v3.0.lnk"
	$shortcut = $shell.CreateShortcut($programShortcut)
	$shortcut.TargetPath = "$InstallDir\programa.exe"
	$shortcut.WorkingDirectory = $InstallDir
	$shortcut.Description = "ObjektinisUzdavinys v3.0 - Student Management System"
	$shortcut.Save()
	Write-Host "[OK] Start Menu shortcut created: $programShortcut"

	# Documentation shortcut
	$docShortcut = "$vuMenuPath\Documentation.lnk"
	$shortcut = $shell.CreateShortcut($docShortcut)
	$shortcut.TargetPath = "$InstallDir\documentation\refman.pdf"
	$shortcut.WorkingDirectory = "$InstallDir\documentation"
	$shortcut.Description = "ObjektinisUzdavinys v3.0 Documentation"
	$shortcut.Save()
	Write-Host "[OK] Documentation shortcut created: $docShortcut"

	# Uninstall shortcut
	$uninstallShortcut = "$vuMenuPath\Uninstall.lnk"
	$shortcut = $shell.CreateShortcut($uninstallShortcut)
	$shortcut.TargetPath = "$InstallDir\uninstall.bat"
	$shortcut.WorkingDirectory = $InstallDir
	$shortcut.Description = "Uninstall ObjektinisUzdavinys v3.0"
	$shortcut.Save()
	Write-Host "[OK] Uninstall shortcut created: $uninstallShortcut"
}

Write-Host ""
Write-Host "============================================================"
Write-Host "Shortcuts created successfully!"
Write-Host "============================================================"
Write-Host ""
Write-Host "Desktop Shortcut:"
Write-Host "  Location: $desktopPath\ObjektinisUzdavinys v3.0.lnk"
Write-Host ""
Write-Host "Start Menu Shortcuts:"
Write-Host "  Location: $vuMenuPath\"
Write-Host "  - ObjektinisUzdavinys v3.0.lnk (Program)"
Write-Host "  - Documentation.lnk (PDF docs)"
Write-Host "  - Uninstall.lnk (Remove program)"
Write-Host ""
