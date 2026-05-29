# ObjektinisUzdavinys v3.0 - Installation Directory Structure

## Instaliacijos Kelias
```
C:\Program Files\VU\Ditas-Simoliunas\
```

## Kataaloginė Struktūra Po Diegimo

```
C:\Program Files\VU\Ditas-Simoliunas\
├── programa.exe                         (Pagrindinė programa)
│
├── documentation\
│   ├── README.md                       (Projekto dokumentacija v3.0)
│   ├── refman.pdf                      (Doxygen dokumentacija - 110 puslapių)
│   └── (papildomi dokumentai)
│
├── test_data\
│   ├── Studentai_test_10000.txt        (10,000 studentų duomenys)
│   └── Studentai_test_100000.txt       (100,000 studentų duomenys)
│
├── uninstall.bat                       (Programos iškrovimas)
└── LICENSE                             (Jei reikalinga)
```

## Naudotojo Nuorodos

### Desktop
```
Desktop\
└── ObjektinisUzdavinys v3.0.lnk        (Link į programa.exe)
```

### Start Menu
```
Start Menu\Programs\VU\Ditas-Simoliunas\
├── ObjektinisUzdavinys v3.0.lnk        (Program launcher)
├── Documentation.lnk                   (Opens refman.pdf)
└── Uninstall.lnk                       (Runs uninstall.bat)
```

## Sisteminės Nuorodos (Registry - Windows)

Programa registruoja savo egzistenciją:
```
HKLM\Software\Microsoft\Windows\CurrentVersion\Uninstall\ObjektinisUzdavinys
├── DisplayName = "ObjektinisUzdavinys v3.0"
├── DisplayVersion = "3.0"
├── UninstallString = "C:\Program Files\VU\Ditas-Simoliunas\uninstall.exe"
└── Publisher = "Ditas Simoliunas"
```

Tai būtina tam, kad programa atsirastų **Control Panel → Add/Remove Programs**

## Diegimo Etapai

1. **Direktorijų Kūrimas**
   - Sukuriama: `C:\Program Files\VU\Ditas-Simoliunas`
   - Sukuriama: `C:\Program Files\VU\Ditas-Simoliunas\documentation`
   - Sukuriama: `C:\Program Files\VU\Ditas-Simoliunas\test_data`

2. **Failų Kopijimas**
   - programa.exe → instaliacijos aplankas
   - README.md → documentation\
   - refman.pdf → documentation\
   - Studentai_test_10000.txt → test_data\
   - Studentai_test_100000.txt → test_data\

3. **Nuorodų Kūrimas**
   - Desktop shortcut (programa.exe)
   - Start Menu group (VU)
   - Start Menu shortcuts (Program, Docs, Uninstall)

4. **Admin Elevation**
   - Setup.exe/install.bat reikalauja Admin teisių
   - Uninstall.bat taip pat reikalauja Admin teisių

5. **Registry Įrašai**
   - Add/Remove Programs registracija
   - Uninstall šaltinio nustatymas

## Naiškavimas (Uninstall)

Iškrovimas panaikins:
1. ✓ Visus failay iš `C:\Program Files\VU\Ditas-Simoliunas\`
2. ✓ Desktop shortcut
3. ✓ Start Menu shortcuts ir folderius
4. ✓ Registry įrašus

## Kompatibilumas

### Suportamos OS
- Windows 7 SP1+
- Windows 8 / 8.1
- Windows 10 (labiausiai testuota)
- Windows 11

### Reikalavimai
- Administrator teisės diegimui
- ~100 MB laisvos vietos
- .NET Framework 4.0+ (jei C++ runtime priklausomybės reikalingos)

## Aplinkos Kintamieji

Programa naudoja šias aplinkos kintamuosius (iš kur ji randa test failus):

- `%USERPROFILE%` - Vartotojo home aplankas (Desktop, Documents)
- `%PROGRAMFILES%` - Standartinis C:\Program Files kelias
- `%APPDATA%` - Start Menu ir Roaming datos aplankas

## Atvirų Failų Keliai Po Diegimo

Naudotojas gali pasiekti:

1. **Test failai**: 
   ```
   C:\Program Files\VU\Ditas-Simoliunas\test_data\Studentai_test_10000.txt
   C:\Program Files\VU\Ditas-Simoliunas\test_data\Studentai_test_100000.txt
   ```

2. **Dokumentacija**:
   ```
   C:\Program Files\VU\Ditas-Simoliunas\documentation\README.md
   C:\Program Files\VU\Ditas-Simoliunas\documentation\refman.pdf
   ```

3. **Programos paleidimas**:
   ```
   C:\Program Files\VU\Ditas-Simoliunas\programa.exe
   ```

4. **Iškrovimas**:
   ```
   C:\Program Files\VU\Ditas-Simoliunas\uninstall.bat
   ```

## Saugumas ir Teisės

- **Administrator teisės**: Reikalingos diegimui ir iškrovimui
- **User teisės**: Pakankamos programos paleidimui
- **File Permissions**: Standartinės Windows file ACLs
- **Registry Permissions**: HKLM (requires admin) diegimui

---

**Version**: 3.0  
**Author**: Ditas Simoliunas  
**Date**: 2026-05-29
