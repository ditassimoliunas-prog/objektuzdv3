## v3.0 relisas: Custom Vector<T> Konteineris

### Vector<T> Spartos Palyginimas su std::vector

#### push_back() Operacijos Spartos Testas

| Elementų skaičius | std::vector (s) | Vector<int> (s) |
|-------------------|-----------------|-----------------|
| 1000              | 0.04200 s       | 0.04292 s       |
| 10000             | 0.24998 s       | 0.31445 s       |
| 100000            | 2.31416 s       | 2.91781 s       |
| 1000000           | 23.71250 s      | 28.25032 s      |

#### Testas: std::vector vs Vector<int> push_back()

---

### Vector<T> API Naudojimo Pavyzdžiai

#### 1. Pagrindinės Operacijos - push_back() ir pop_back()

```cpp
#include "Vector.h"

Vector<int> v;

// push_back() - pridėjimas į galą
v.push_back(10);
v.push_back(20);
v.push_back(30);

std::cout << "Dydis: " << v.size() << "\n";  // Išveda: 3

// pop_back() - šalinimas iš galo
v.pop_back();  // Šalina 30

// Prieiga prie elementų
std::cout << "Pirmas: " << v[0] << "\n";      // Išveda: 10
std::cout << "Paskutnis: " << v.back() << "\n";  // Išveda: 20
```

#### 2. Konstruktoriai ir Inicijalizacija

```cpp
// Default konstruktorius
Vector<double> v1;

// Konstruktorius su dydžiu
Vector<int> v2(5);  // 5 int elementų, reikšmės 0

// Konstruktorius su dydžiu ir reikšme
Vector<std::string> v3(3, "Sveiki");  // 3 "Sveiki" eilutės

// Copy konstruktorius
Vector<int> v4 = v1;  // Deep copy

// Move konstruktorius
Vector<int> v5 = std::move(v2);  // Ištekliai perkelti iš v2 į v5
```

#### 3. Reservavimas ir Dydžio Valdymas

```cpp
Vector<int> v;
v.reserve(100);  // Išankstinis atmintis rezervavimas

std::cout << "Talpa: " << v.capacity() << "\n";  // Išveda: 100
std::cout << "Dydis: " << v.size() << "\n";      // Išveda: 0

// Nustatyti konkretų dydį
v.resize(50);  // Dabar dydis = 50, nauji elementai = 0

// Sumažinti iš dalies nereikalingą atmintį
v.shrink_to_fit();  // capacity() == size()
```

#### 4. Iteratoriai ir Iteravimas

```cpp
Vector<int> v = {1, 2, 3, 4, 5};

// Range-based for ciklas
for (int elem : v) {
    std::cout << elem << " ";  // Išveda: 1 2 3 4 5
}

// Tiesioginis iteratoriaus naudojimas
for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";
}

// Atgaline tvarka
for (auto it = v.rbegin(); it != v.rend(); ++it) {
    std::cout << *it << " ";  // Išveda: 5 4 3 2 1
}
```

#### 5. insert() ir erase() Operacijos

```cpp
Vector<int> v = {1, 2, 3, 5};

// Dėjimas į konkrečią padėtį
auto it = v.begin() + 3;
v.insert(it, 4);  // Dabar: {1, 2, 3, 4, 5}

// Šalinimas iš konkrečios padėties
v.erase(v.begin() + 1);  // Šalina 2, dabar: {1, 3, 4, 5}

// Šalinimas diapazono
v.erase(v.begin() + 1, v.begin() + 3);  // Šalina {3, 4}, dabar: {1, 5}
```

#### 6. assign() - Perkėlimas iš Iteratoriaus Diapazono

```cpp
Vector<int> v1;
std::vector<int> std_v = {10, 20, 30, 40};

// Assign iš std::vector iteratorių
v1.assign(std_v.begin(), std_v.end());
// Dabar v1 = {10, 20, 30, 40}

// Arba iš kito Vector<int>
Vector<int> v2;
v2.assign(v1.begin(), v1.end());
// Dabar v2 = {10, 20, 30, 40}
```

#### 7. emplace_back() - Vietos Konstravimas

```cpp
struct Studentas {
    std::string vardas;
    int vidurkis;

    Studentas(const std::string& v, int m) 
        : vardas(v), vidurkis(m) {}
};

Vector<Studentas> grup;

// emplace_back() - konstravimas tiesiog vektoriuje (be kopijų)
grup.emplace_back("Jonas", 8);
grup.emplace_back("Marija", 9);

std::cout << "Pirmas studentas: " << grup[0].vardas << "\n";
```

#### 8. Palyginimai ir Operatoriai

```cpp
Vector<int> v1 = {1, 2, 3};
Vector<int> v2 = {1, 2, 3};
Vector<int> v3 = {1, 2, 4};

// Lygybės operatorius
if (v1 == v2) {
    std::cout << "v1 ir v2 lygūs\n";  // Spausdina
}

// Nelygumo operatorius
if (v1 != v3) {
    std::cout << "v1 ir v3 nelygūs\n";  // Spausdina
}

// Mažiau nei operatorius
if (v1 < v3) {
    std::cout << "v1 < v3 (leksikografinė sąlyga)\n";
}
```

---

## v2.0 relisas: Unit Testai (Google Test) ir Doxygen Dokumentacija

### Unit Testai (v2.0)

Projektas naudoja **hibridinę test strategiją**:
- **13 testų** (originalūs iš v1.5): `assert()` framework, Rule of Five ir I/O operacijos
- **5 testai** (nauji v2.0): Google Test (`gtest`) framework, Rule of Five semantika
7
#### Rule of Five Metodai - `assert()` Framework (v1.5 pagrindiniai):

| Testas | Metodas | Framework | Aprašas |
|--------|---------|-----------|---------|
| 1 | Default konstruktorius | `assert()` | Numatytosios reikšmės (A, BB, 0, 0.0) |
| 2 | Parametrizuotas konstruktorius | `assert()` | Duomenų inicializavimas |
| 3 | **Copy konstruktorius** (Rule of Five #1) | `assert()` | Deep copy operacija |
| 4 | **Copy assignment** (Rule of Five #2) | `assert()` | Duomenų kopijavimas ir self-assignment |
| 5 | **Move konstruktorius** (Rule of Five #3) | `assert()` | Išteklių perėmimas, šaltinis tuščias |
| 6 | **Move assignment** (Rule of Five #4) | `assert()` | Laikino objekto išteklių perėmimas |
| 7 | **Destruktorius** (Rule of Five #5) | `assert()` | Tinkamas išteklių atlaisvinimas (RAII) |
| 8 | I/O Round-trip | `assert()` | Išvestis ir įvedimas (operator<< / operator>>) |
| 9-10 | Getters/Setters, vektoriaus ops | `assert()` | Duomenų prieiga ir pažymių operacijos |

#### Papildomi Google Test Testai (v2.0):

| Testas | Pavadinimas | Framework | Aprašas |
|--------|-------------|-----------|---------|
| 14 | `StudentasVectorTest.PushBackCopySemantics` | Google Test | Copy semantika su vektoriumi |
| 15 | `StudentasVectorTest.PushBackMoveSemantics` | Google Test | Move semantika su vektoriumi |
| 16 | `StudentasDeepCopyTest.IndependentCopies` | Google Test | Deep copy nepriklausomumas |
| 17 | `StudentasSelfAssignmentTest.CopySafetyCheck` | Google Test | Self-assignment saugumas |
| 18 | `StudentasOperatorTest.AssignmentChaining` | Google Test | Assignment operator chaining |

### Testų Vykdymas

**Automatinis vykdymas (rekomenduojama):**
```bash
# Linux/macOS
./build.sh test

# Windows
powershell -ExecutionPolicy Bypass -File .\diegimas.ps1 -Stage "test"
```

**Tiesiogas vykdymas:**
```bash
# Linux/macOS
cd build
./test_programa

# Windows
cd out\build\x64-Debug
.\test_programa.exe
```

**Tikėtini Rezultatai:**
```
============================================================
  STUDENTAS KLASES VISOS METODU TESTAI (v1.5)
  + GOOGLE TEST PAPILDYMAS (v2.0)
============================================================

[PRIIMTAS] Default konstruktorius testai...
...
Priimti testai: 50
Nepriimti testai: 0

VISI TESTAI PRIIMTI!

============================================================
Vykdomme GOOGLE TEST testai...
============================================================

[==========] Running 5 tests from 4 test suites.
[  PASSED  ] 5 tests.
```
### Doxygen Dokumentacija (v2.0 nauja!)

Visa dokumentacija sugeneruojama iš source kodo Doxygen komentarų.

**Sugeneruoti/atnaujinti dokumentaciją:**
```bash
# Automatinis būdas (rekomenduojama)
./build.sh docs          # Linux/macOS
diegimas.ps1 -Stage docs # Windows

# Arba tiesiogas doxygen kvietimas
doxygen Doxyfile
```

**Dokumentacijos Rezultatai:**
- `dokumentacija/html/index.html` - Interaktyvi HTML dokumentacija (naršom nuorodose)
- `dokumentacija/latex/refman.pdf` - Kompiliuota PDF dokumentacija (52 psl.)

**Atidarytite dokumentaciją:**
- HTML: Atidaryti `dokumentacija/html/index.html` naršyklėje
- PDF: Atidaryti `dokumentacija/latex/refman.pdf` PDF skaitykloje

---

## Diegimo Instrukcija

### Sistemos Reikalavimai

| Reikalavimas | Versija | Pastaba |
|--------------|---------|---------|
| CMake | ≥ 3.10 | Build sistema |
| C++ Kompiliatorius | C++17 | MSVC / GCC / Clang |
| Google Test | v1.14.0 | Automatiškai parsiunčiama |
| Doxygen | naujausias | Dokumentacijai (parsisiuntimas: https://www.doxygen.nl/download.html) |
| TeX Live / LaTeX | 2024+ | PDF generavimui (parsisiuntimas: https://www.tug.org/texlive/) |

### 1. Klonuojame repoziciją

```bash
git clone https://github.com/ditassimoliunas-prog/objektuzdv1.git
cd objektuzdv1
git checkout v2.0
```

### 2. Automatinis diegimas (rekomenduojama)

**Linux/macOS (su bash):**
```bash
chmod +x build.sh
./build.sh all
```

**Windows (su PowerShell):**
```powershell
Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process
powershell -File .\diegimas.ps1 -Stage all
```

**macOS (su Makefile):**
```bash
make all
```

### 3. Rankinis diegimas žingsniai

#### Schritt 2a: Konfigūruojame CMake

**Linux/macOS:**
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
```

**Windows (MSVC/Ninja):**
```powershell
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 ..
```

#### Schritt 2b: Kompiliuojame

**Linux/macOS:**
```bash
cmake --build . --config Release
```

**Windows:**
```powershell
cmake --build . --config Release
```

#### Schritt 2c: Vykdome testus

```bash
# Linux/macOS
./test_programa

# Windows
.\Release\test_programa.exe
```

#### Schritt 2d: Sugeneruojame dokumentaciją

```bash
cd ..
doxygen Doxyfile
```

### 4. Patikrinimas

Po diegimo turėtumėte matyti:
- ✅ `build/` direktorijoje kompiliuoti failai
- ✅ `test_programa` išvykdomas su 55 praejetais testais (50 assert + 5 gtest)
- ✅ `dokumentacija/html/index.html` - atidaryti naršyklėje
- ✅ `dokumentacija/latex/refman.pdf` - PDF dokumentacija

---

## Naudojimosi Instrukcija

### Pagrindinės Programos Paleidimas

**Linux/macOS:**
```bash
./build/programa
```

**Windows:**
```powershell
.\build\Release\programa.exe
```

### Programos Meniu

Paleidus pagrindinę programą, galima rinktis iš šių opcijų:

| Opciją | Veikimas |
|--------|----------|
| 1 | Rankininis įvedimas (vardas, pavardė, 5 pažymiai, egzaminas) |
| 2 | Generuoti tik pažymius |
| 3 | Generuoti visus duomenis automatiškai |
| 4 | Nuskaityti iš failo |
| 5 | Sukurti testavimo failus |
| 6 | Atlikti spartos analizę |
| 7 | Baigti darbą |

### Build Sumos Komandos

**Linux/macOS (build.sh):**
```bash
./build.sh build       # Kompiliuoti
./build.sh test        # Vykdyti testus
./build.sh docs        # Sugeneruoti dokumentaciją
./build.sh run         # Paleisti programą
./build.sh clean       # Valyti build failus
./build.sh help        # Pagalba
```

**Windows (diegimas.ps1):**
```powershell
powershell -File .\diegimas.ps1 -Stage build  # Kompiliuoti
powershell -File .\diegimas.ps1 -Stage test   # Vykdyti testus
powershell -File .\diegimas.ps1 -Stage docs   # Sugeneruoti dokumentaciją
powershell -File .\diegimas.ps1 -Stage run    # Paleisti programą
powershell -File .\diegimas.ps1 -Stage clean  # Valyti build failus
```

**macOS (Makefile):**
```bash
make build             # Kompiliuoti
make test              # Vykdyti testus
make docs              # Sugeneruoti dokumentaciją
make run               # Paleisti programą
make clean             # Valyti build failus
make info              # Pagalba
```

## Projekto Failų Struktūra

```
objektuzdv1/
├── CMakeLists.txt              # CMake build konfigūracija (v2.0: Google Test FetchContent)
├── Doxyfile                    # Doxygen konfigūracija (v2.0: HTML + PDF)
├── Makefile                    # Unix-style build helper (v2.0: build/test/docs/run/clean)
├── build.sh                    # Linux/macOS build script (v2.0: automatinis diegimas)
├── diegimas.ps1                # Windows PowerShell script (v2.0: automatinis diegimas)
├── README.md                   # Šis failas (v2.0: atnaujintas)
├── .gitignore                  # Git taisyklės (v2.0: dokumentacija jau versijuota)
│
├── header_files/               # Klasių aprašymai (interface)
│   ├── Zmogus.h               # Abstrakti bazė
│   ├── Studentas.h            # Studentas klasė (Rule of Five)
│   ├── mat_funkcijos.h
│   ├── menu.h
│   └── ...
│
├── extra_cpp/                  # Implementacijos
│   ├── Zmogus.cpp             # Bazės klasės implementacija
│   ├── Studentas.cpp          # Studentas klasės implementacija
│   ├── mat_funkcijos.cpp
│   ├── menu.cpp
│   └── ...
│
├── objekt1uzd.cpp             # Pagrindinė programa (main)
├── test_studentas.cpp         # Unit testai (v2.0: 13x assert + 5x Google Test)
│
├── dokumentacija/             # Sugeneruota Doxygen dokumentacija (v2.0: versijuota!)
│   ├── html/
│   │   └── index.html         # HTML dokumentacijos pradžia
│   ├── latex/
│   │   ├── refman.tex
│   │   ├── refman.pdf         # PDF dokumentacija (52 psl.)
│   │   └── ...
│   └── ...
│
├── out/build/x64-Debug/       # Visual Studio build output (git ignored)
├── build/                      # CMake build direktorija (git ignored)
│   ├── test_programa          # Kompiliuotas testas
│   ├── programa               # Kompiliuota pagrindinė programa
│   └── CMakeFiles/
│
└── .git/                       # Git repositorija

---

## Klaidų Sprendimas

### Klaida: "CMake not found"
```bash
# CMake instaliacija
# Windows: https://cmake.org/download/ (arba choco install cmake)
# Linux: sudo apt install cmake
# macOS: brew install cmake
```

### Klaida: "C++ compiler not found"
```bash
# Kompiliatoriaus instaliacija
# Windows: Instaliuoti Visual Studio Build Tools arba Visual Studio Community
# Linux: sudo apt install build-essential g++
# macOS: xcode-select --install
```

### Klaida: "Doxygen not found"
```bash
# Doxygen parsisiuntimas ir instaliacija
# https://www.doxygen.nl/download.html
# macOS: brew install doxygen
# Tada pridėti doxygen į PATH arba naudoti pilną path: /usr/local/bin/doxygen
```

### Klaida: "pdflatex not found"
```bash
# TeX Live parsisiuntimas (PDF generavimui)
# Windows: https://www.tug.org/texlive/ (instaliuoti texlive-full)
# Linux: sudo apt install texlive-latex-base texlive-latex-extra
# macOS: brew install basictex
# Po instaliavimo, pdflatex turėtų būti automatiškai PATH'e
```

### Klaida: "Google Test linking errors"
```bash
# Paprastai išsprendžiama automatiškai FetchContent'u CMake'e
# Jei problema lieka:
# 1. Išvalykite build direktorijų: rm -rf build/
# 2. Iš naujo sukonfigūruokite: cmake -B build -S .
# 3. Perrankinkite: cmake --build build --config Debug
```

### Klaida: "test_programa.exe not found"
```bash
# Patikrinkite, ar build sėkminga:
cd build
ls -la  # Linux/macOS
dir     # Windows
# Jei failas nėra, perrankinkite: cmake --build . --config Release
```

### Dėl Build Problemų

Jei naudojate Visual Studio Code arba kitą IDE ir kyla problemos:

1. Išvalykite CMake cache: `rm -rf build` (arba `rmdir /s build` Windows)
2. Iš naujo sukonfigūruokite projektą: `cmake -B build -S . -G "Visual Studio 17 2022"`
3. Perrankinkite: `cmake --build build --config Release`

---

## Release Istorija

### v2.0 (Dabartinis)
- ✅ Integruotas Google Test framework (5 papildomi testai)
- ✅ Doxygen dokumentacija (HTML + PDF)
- ✅ CMake optimizuotas su FetchContent
- ✅ Automatiniai build scripti (build.sh, diegimas.ps1, Makefile)
- ✅ Visos Rule of Five metodai su `assert()` testais
- ✅ Dokumentacija versijuota į git repository

### v1.5
- Originalūs 13 `assert()` testai (Rule of Five + I/O)
- Bazė klasė Zmogus su Studentas derivacija
- Pagrindinė meniu programa

---

## Pagalba ir Suportas

Jei kyla klausimų:

1. **Patikrinkite dokumentaciją:** `dokumentacija/html/index.html`
2. **Perskaityti README sekcijas** - greitasis startas aukščiau
3. **Vykdyti testus** - tai parodo, ar viskas veikia: `./test_programa`
4. **Kontaktuoti autorių** arba [Parašyti Issue](https://github.com/ditassimoliunas-prog/objektuzdv1/issues)

---

## Autoriaus Informacija

**Projekto Pavadinimas:** objektuzdv1 (Objektinio Programavimo Užduotis 1)
**Versija:** v2.0
**Sukurta:** 2024-2026
**Licenzija:** MIT
**GitHub:** https://github.com/ditassimoliunas-prog/objektuzdv1

---
Assert Rule of five testai:

<img width="424" height="722" alt="Screenshot 2026-05-24 171304" src="https://github.com/user-attachments/assets/378556d4-baec-41be-ba2b-20b1401cf511" />
<img width="835" height="689" alt="Screenshot 2026-05-24 171330" src="https://github.com/user-attachments/assets/8f343a65-4895-40bf-aa0c-5da988354cf1" />
<img width="459" height="383" alt="Screenshot 2026-05-24 171440" src="https://github.com/user-attachments/assets/452b239b-0c8e-47ff-bfcb-115a8902081d" />

Google.test testai:

<img width="560" height="484" alt="image" src="https://github.com/user-attachments/assets/dc899571-b8e1-4d06-9222-77ec201fe551" />







