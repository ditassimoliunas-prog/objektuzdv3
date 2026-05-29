#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <chrono>

#include "../header_files/output.h"
#include "../header_files/Vector.h"

using std::cin;
using std::cout;
using std::string;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::sort;
using std::fixed;
using std::numeric_limits;
using std::streamsize;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

void outputas(Vector<Studentas>& grupe) {
    if (grupe.empty()) {
        cout << "Nera studentu duomenu!\n";
        return;
    }

    // Klausiame kaip rusiuoti
    cout << string(80, '-') << "\n";
    cout << "Pasirinkite rusiavimo buda:\n";
    cout << "1. Pagal varda (A-Z)\n";
    cout << "2. Pagal pavarde (A-Z)\n";
    cout << "3. Pagal galutini bala (vidurki) - didejimo tvarka\n";
    cout << "4. Pagal galutini bala (mediana) - didejimo tvarka\n";

    int pasirinkimas;
    while (!(cin >> pasirinkimas) || pasirinkimas < 1 || pasirinkimas > 4) {
        cout << "Klaida! Iveskite skaiciu nuo 1 iki 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Pasirinktas rusiavimas: " << pasirinkimas << "\n";

    // Pradedamas rusiavimo laiko matavimas
    auto pradzia = high_resolution_clock::now();

    // Rusiuojama pagal pasirinkima
    switch (pasirinkimas) {
    case 1:
        sort(grupe.begin(), grupe.end(), comparePagalVarda);
        break;
    case 2:
        sort(grupe.begin(), grupe.end(), comparePagalPavarde);
        break;
    case 3:
        sort(grupe.begin(), grupe.end(), comparePagalReza);
        break;
    case 4:
        sort(grupe.begin(), grupe.end(), comparePagalMeda);
        break;
    default:
        cout << "Klaida! Neteisingas pasirinkimas. Rodoma be rusiavimo.\n";
        break;
    }

    // Baigiamas rusiavimo laiko matavimas
    auto pabaiga = high_resolution_clock::now();
    duration<double> trukme = pabaiga - pradzia;

    // Antrastes eilute
    cout << string(80, '-') << "\n";
    cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
        << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)\n";

    // Studentu duomenys
    for (const auto& A : grupe) {
        cout << left << setw(20) << A.getVardas() << setw(20) << A.getPavarde()
            << setw(20) << fixed << setprecision(2) << A.getRez()
            << setw(20) << fixed << setprecision(2) << A.getMed() << "\n";
    }

    cout << string(80, '-') << "\n";
    cout << "Ivykdymo laikas: " << fixed << setprecision(7) << trukme.count() << " s\n";
}
