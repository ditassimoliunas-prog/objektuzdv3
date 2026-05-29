#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

#include "../header_files/menu.h"
#include "../header_files/studentas.h"
#include "../header_files/input.h"
#include "../header_files/output.h"
#include "../header_files/duomenu_valdymas.h"
#include "../header_files/testavimas.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::invalid_argument;
using std::exception;

void menu() {
    vector<Studentas>grupe;
    int pas; // Pasirinkimas
    bool testi = true;

    while (testi) {
        cout << string(80, '-') << "\n";
        cout << "Studentu Rezultatu skaiciavimo aplikacija\n";
        cout << string(80, '-') << "\n";
        cout << "1. Ivesti duomenis ranka\n";
        cout << "2. Generuoti tik pazymius\n";
        cout << "3. Generuoti studentu vardus, pavardes ir pazymius\n";
        cout << "4. Nuskaityti duomenis is failo\n";
        cout << "5. Sukurti testavimo failus (1000 - 10000000 irasu)\n";
        cout << "6. Atlikti spartos analize (nuskaitymas, rusiavimas, dalijimas, isvedimas)\n";
        cout << "7. Baigti darba\n";
        cout << "Jusu pasirinkimas: ";

        try {
            if (!(cin >> pas)) {
                throw invalid_argument("Neteisingas ivedimas! Iveskite skaiciu.");
            }
        }
        catch (const invalid_argument& e) {
            cout << "Klaida: " << e.what() << "\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        // Pasirinkimo isvestis
        switch (pas) {
        case 1:
            try {
                cout << "1. Ivesti duomenis ranka\n";
                inputas(grupe);
                outputas(grupe);
                grupe.clear();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant 1 funkcija: " << e.what() << "\n";
                grupe.clear();
            }
            break;
        case 2:
            try {
                cout << "2. Generuoti tik pazymius\n";
                generuotiPaz(grupe);
                outputas(grupe);
                grupe.clear();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant 2 funkcija: " << e.what() << "\n";
                grupe.clear();
            }
            break;
        case 3:
            try {
                cout << "3. Generuoti studentu vardus, pavardes ir pazymius\n";
                generuotiVardIrPav(grupe);
                outputas(grupe);
                grupe.clear();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant 3 funkcija: " << e.what() << "\n";
                grupe.clear();
            }
            break;
        case 4:
            try {
                cout << "4. Nuskaityti duomenis is failo\n";
                skaitytiIsFailo(grupe);
                outputas(grupe);
                grupe.clear();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant 4 funkcija: " << e.what() << "\n";
                grupe.clear();
            }
            break;
        case 5:
            try {
                cout << "5. Sukurti testavimo failus (1000 - 10000000 irasu)\n";
                sukurtiTestavimoFailus();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant 5 funkcija: " << e.what() << "\n";
            }
            break;
        case 6:
            try {
                cout << "6. Atlikti spartos analize (nuskaitymas, rusiavimas, dalijimas, isvedimas)\n";
                atliktiSpartosAnalize();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant 6 funkcija: " << e.what() << "\n";
            }
            break;
        case 7:
            cout << "Programa baigia darba. Iki pasimatymo!\n";
            testi = false;
            break;
        default:
            cout << "Neteisingas pasirinkimas! Pasirinkite nuo 1 iki 7.\n";
            break;
        }
    }
}

