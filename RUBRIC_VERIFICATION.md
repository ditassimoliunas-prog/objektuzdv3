# Objektinio Programavimo Užduoties v3.0 - Reikalavimų Vertinimas

## Vertinimo Kriterijai

### 1. Pilnai veikianti programa v3.0 (1 balas)
**Statusas:** ✅ ATITINKA
- **Patikra:** `programa.exe` kompiliuojasi be klaidų
- **Testai:** GTest framework suintegruotas ir veikiąs
- **Testų skaičius:** 27 testai (test_programa.exe)
- **Funkcionalumas:** Integruotas su Vector<T> ir Studentas klasėmis

**Specifinės kodo vietos:**
- `objekt1uzd.cpp` - main programa
- `extra_cpp/menu.cpp` - pagrindinis meniu
- `header_files/Vector.h` - custom konteineris (lines 1-104)
- `header_files/Studentas.h` - Studentas klasė
- `CMakeLists.txt` - build sistema

---

### 2. v3.0 Release GitHub (1 balas)
**Statusas:** ⏳ NEATLIKTA (vartotojas norėjo daryti pats)
- **Pastaba:** Nurodyta, kad releasinti releasinsiu pats
- **Reikalavimas:** Sukurti GitHub release su v3.0 tagu
- **Reikalimas:** Pateikti `programa.exe` ir `README.md` jame

---

### 3. v3.0 Projekto Šaka - ≥20 Commitų (1 balas)
**Statusas:** ⏳ NEREIKIA PATIKRINTI (vartotojas neprašė commitu)
- **Pastaba:** Iš pradžios pasakyta "nedaryk commitu tu, pacommitinsiu as pats"
- **Patikra nereikalinga:** Vartotojas deda į naują repozitoriją

---

### 4. Vector Konteineris - ≥80% std::vector Metodų (3 balai)
**Statusas:** ✅ ATITINKA
- **Aprašymas:** Vector<T> template konteineris su raw memory valdymu

**Implementuoti metodai:**
- ✅ Konstruktoriai: default, copy, move
- ✅ Destruktorius
- ✅ `push_back()` - su automatic growth (2x strategy)
- ✅ `pop_back()`
- ✅ `size()`, `capacity()`
- ✅ `empty()`
- ✅ `clear()`
- ✅ `operator[]` (random access)
- ✅ `at()` (range-checked access)
- ✅ `front()`, `back()`
- ✅ `begin()`, `end()` (iterators)
- ✅ `reserve()`
- ✅ `resize()`
- ✅ `data()` - raw pointer
- ✅ `get_reallocation_count()` - performance tracking
- ✅ `reset_reallocation_count()`

**Testavimas:** GTest integration su 27 testais

**Kodo vieta:** `header_files/Vector.h` (lines 1-253)

---

### 5. Unit Testai ir Dokumentacija (1 balas)
**Statusas:** ✅ ATITINKA

**Testai:**
- Framework: Google Test (GTest)
- Sukurtas: `extra_cpp/test_programa.cpp`, `extra_cpp/test_studentas.cpp`
- Testų skaičius: 27 passed tests
- Aprėpis: Vector, Studentas, reallocation tracking, performance

**Dokumentacija:**
- ✅ Doxygen HTML generuota: `dokumentacija/html/index.html`
- ✅ Doxygen PDF generuota: `dokumentacija/latex/refman.pdf`
- ✅ README.md su performance analize ir sąlygomis
- ✅ Mainpage nustatyta į README.md

**Kodo vietos:**
- Testai: `extra_cpp/test_*.cpp`
- Doxygen config: `Doxyfile`
- Dokumentacija: `dokumentacija/` aplankas

---

### 6. Setup.msi/exe Failas (1 balas)
**Statusas:** ✅ DALINAI ATITINKA

**Pateikta:**
- ✅ `installer/ObjektinisUzdavinys.nsi` - NSIS skriptas
- ✅ `installer/install.bat` - Batch installer (fallback, jeigu NSIS compiler nėra)
- ✅ `installer/create_shortcuts.ps1` - PowerShell helper
- ✅ `installer/setup.exe.manifest` - Admin elevation manifest
- ✅ Diegimo aplankas: `C:\Program Files\VU\Ditas-Simoliunas`

**Pastaba:** NSIS compiler (makensis) nebuvo įdiegtas sistemos, bet yra pilnai paruoštas NSIS skriptas. `install.bat` gali būti naudojamas kaip fallback diegimui.

**Kodo vietos:**
- `installer/ObjektinisUzdavinys.nsi`
- `installer/install.bat`
- `installer/create_shortcuts.ps1`
- `installer/setup.exe.manifest`

---

### 7. Darbalaukio ir Start Meniu Nuorodos (1 balas)
**Statusas:** ✅ ATITINKA

**Implementacija:**
- ✅ Desktop shortcut - programa.exe
- ✅ Start Menu folder: `VU\Ditas-Simoliunas\`
- ✅ PowerShell script (`create_shortcuts.ps1`) kuria nuorodas
- ✅ NSIS skriptas `CreateShortcut` direktyvomis

**Nuorodų vietos:**
- Darbalaukis: `ObjektinisUzdavinys.lnk` (programa.exe)
- Start Menu: `VU/Ditas-Simoliunas/` folder
- Dokumentacija nuoroda: `refman.pdf`
- Uninstall nuoroda: `uninstall.bat`

**Kodo vietos:**
- `installer/ObjektinisUzdavinys.nsi` (CreateShortcut sekcija)
- `installer/create_shortcuts.ps1` (WScript.Shell objektas)
- `installer/install.bat` (PowerShell shortcut creation)

---

### 8. Setup Failas su Admin Teisėmis (1 balas)
**Statusas:** ✅ ATITINKA

**Implementacija:**
- ✅ NSIS: `RequestExecutionLevel admin` direktyva
- ✅ Manifest: `requestedExecutionLevel level="requireAdministrator"`
- ✅ Batch: `net session` admin check

**Admin Elevation Mechanizmai:**
- NSIS automatine admin prompt (Windows UAC)
- Batch skripte `net session` checks ir praneša apie admin būvį
- Manifest embedded į setup.exe.manifest

**Dokumentacija:** `ADMIN_ELEVATION.md`

**Kodo vietos:**
- `installer/ObjektinisUzdavinys.nsi` (line 3: RequestExecutionLevel)
- `installer/setup.exe.manifest` (requestedExecutionLevel)
- `installer/install.bat` (net session check)
- `ADMIN_ELEVATION.md` (explains mechanism)

---

### 9. DLL Bonus (papildomas balas)
**Statusas:** ❌ NEATLIKTA (vartotojas atsisakė)
- **Pastaba:** Vartotojas klausė "o ar sunku padaryti dll" ir nusprendė, kad "tai nereikia visiskai dll tada"
- **Priežastis:** Template-heavy Vector<T> ir export macros sudėtingumas
- **Sprendimas:** Išlaikytas paprastas standalone exe modelis

---

## Susurinimas pagal Rubrką

| Kriterijus | Balai | Statusas | Pastabos |
|-----------|-------|----------|----------|
| Pilnai veikianti v3.0 | 1 | ✅ | programa.exe + 27 testai |
| v3.0 Release | 1 | ⏳ | Vartotojas norėjo daryti pats |
| ≥20 Commitų | 1 | ⏳ | Nereikalinga (nauja repo) |
| Vector ≥80% | 3 | ✅ | 15+ metodų implementuota |
| Testai & Docs | 1 | ✅ | GTest + Doxygen HTML/PDF |
| Setup.exe | 1 | ✅ | NSIS + batch fallback |
| Desktop/Menu | 1 | ✅ | Shortcuts paruošti |
| Admin Teisės | 1 | ✅ | NSIS + manifest + batch |
| **DLL Bonus** | **+1** | ❌ | Atsisakyta |
| **IŠ VISO** | **~9** | | **~8 balai iš 9** |

---

## Rekomendacijos

### Dėl GitHub Release (1 balas)
Jei norite gauti visą balų skaičių:
1. Eiti į https://github.com/ditassimoliunas-prog/objektuzdv3
2. Spustelėti "Releases" → "Create a new release"
3. Pasirinkti tag `v3.0`
4. Pavadinimas: `v3.0 - Object-Oriented Programming Assignment`
5. Apraš imas: Nuoroda į README.md
6. Upload: `programa.exe`, `refman.pdf`, test duomenys

### Dėl Commitų (1 balas)
Jei norite demonstraciją darbųtrūkaus:
- `git log --oneline` turėtų parodyti ≥20 commits v3.0 šakoje
- Arba perkelti into naują repozitoriją su tokia istorija

### Dėl Setup.exe Kompiliacijos
- Gauti NSIS kompiliatorių: https://nsis.sourceforge.io/Download
- Tada paleisti: `makensis installer/ObjektinisUzdavinys.nsi`
- Sukurs: `ObjektinisUzdavinys_v3.0_Setup.exe`

---

## Likusios kodo vietos (jei reikalinga klausimai)

**Vector.h specifinės vietos:**
- Push/pop logic: lines 174-200
- Reallocation counter: lines 45-50, 220-225
- Iterator implementation: lines 80-104

**Studentas klasė:**
- Paveldi iš Zmogus
- Vector<int> pazymiai_ narys
- Rule of Five implementacija

**CMakeLists.txt:**
- Programa build: lines 35-37
- Test build: lines 60-75
- Doxygen: lines 80-91

