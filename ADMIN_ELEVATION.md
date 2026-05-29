# Admin Elevation Configuration for Setup

## Overview
The ObjektinisUzdavinys v3.0 installer automatically requires and elevates to Administrator privileges.

## Implementation Methods

### 1. Batch Installer (install.bat)
```batch
REM Check for admin rights
net session >nul 2>&1
if %errorlevel% neq 0 (
	echo ERROR: This script requires administrator privileges.
	echo Please run this script as Administrator.
	pause
	exit /b 1
)
```
**How it works**: Checks if script is running with admin rights. If not, shows error and exits.

### 2. NSIS Installer Script
```nsis
RequestExecutionLevel admin
```
**How it works**: NSIS directive automatically elevates installer to admin. When user runs setup.exe, UAC prompt appears asking for permission.

### 3. Manifest File (setup.exe.manifest)
- Located: `installer/setup.exe.manifest`
- Specifies: `requestedExecutionLevel level="requireAdministrator"`
- Used for: Compiled .exe files to request admin at runtime

## User Experience

### Step-by-Step Admin Elevation

1. **User downloads**: `ObjektinisUzdavinys_v3.0_Setup.exe`

2. **User double-clicks**: setup.exe

3. **Windows detects**: Manifest requests admin rights

4. **UAC Prompt appears**:
   ```
   User Account Control

   Do you want to allow this app to make changes to your device?

   ObjektinisUzdavinys.Setup v3.0
   Verified publisher: Ditas Simoliunas

   [ No ]  [ Yes ]
   ```

5. **User clicks "Yes"**: Installer runs with admin privileges

6. **Installation continues**:
   - Creates `C:\Program Files\VU\Ditas-Simoliunas\`
   - Copies files
   - Creates shortcuts
   - Modifies registry

## Uninstall with Admin Rights

The uninstall script (uninstall.bat) also checks for admin rights:

```batch
net session >nul 2>&1
if %errorlevel% neq 0 (
	echo ERROR: Uninstall requires administrator privileges.
	pause
	exit /b 1
)
```

Users will see UAC prompt when:
- Running `uninstall.bat` directly
- Or through Windows "Add/Remove Programs"

## Registry Modifications (Requires Admin)

The installer modifies:
```
HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Uninstall\
```

This registry path requires admin rights to modify.

## Windows Compatibility

### Supported Versions
- Windows 7 SP1+ ✓
- Windows 8 / 8.1 ✓
- Windows 10 ✓ (Most tested)
- Windows 11 ✓

### UAC Behavior
- **Standard Users**: See UAC prompt
- **Administrators**: Installation proceeds (no prompt if UAC disabled)
- **Windows Server**: Similar to Windows 10/11

## Security Considerations

1. **Admin Requirement Justification**:
   - `C:\Program Files\` folder requires admin to write
   - Registry modification requires admin
   - UAC is a Windows security feature

2. **Manifest Security**:
   - Manifest file embedded in .exe
   - Specifies exact privilege level needed
   - Cannot be bypassed or modified after compilation

3. **No Hidden Admin Escalation**:
   - All elevation is transparent to user
   - User must explicitly approve in UAC dialog
   - No silent elevation without consent

## Testing Admin Elevation

### Test 1: Standard User
1. Create test Windows account (non-admin)
2. Log in as that user
3. Try to run setup.exe
4. **Expected**: UAC prompt appears

### Test 2: Administrator Account  
1. Log in as admin
2. Run setup.exe
3. **Expected**: UAC prompt still appears (unless UAC disabled)

### Test 3: UAC Disabled
1. Disable UAC on system
2. Run setup.exe as admin
3. **Expected**: Installer runs without prompt (but is admin)

## Troubleshooting

### "Access Denied" During Installation
**Cause**: User doesn't have admin rights or UAC blocked
**Solution**: 
- Right-click setup.exe
- Select "Run as Administrator"
- Or: Ensure user account is admin

### "The installer was not properly elevated"
**Cause**: Manifest issue or Windows policy
**Solution**:
- Recompile installer with correct manifest
- Check Group Policy on domain machines
- Try different Windows version

### Uninstall Fails
**Cause**: Uninstall script not elevated
**Solution**:
- Open Command Prompt as Administrator
- Navigate to install directory
- Run: `uninstall.bat`

## Technical Details

### Batch File Admin Check
```batch
net session >nul 2>&1
```
- `net session`: Tries to connect to \\computername\IPC$ (requires admin)
- `>nul 2>&1`: Redirects output to null (silent)
- `%errorlevel% neq 0`: Checks if command failed (not admin)

### NSIS Admin Elevation
```nsis
RequestExecutionLevel admin
```
- Options: `user`, `admin`, `highest`
- `admin`: Requires admin, shows UAC prompt

### Manifest requestedExecutionLevel
- `asInvoker`: No elevation
- `requireAdministrator`: Requires admin (shows UAC)
- `highestAvailable`: Runs as highest level available

---

**Version**: 3.0
**Date**: May 29, 2026
**Status**: ✓ Admin elevation implemented and documented
