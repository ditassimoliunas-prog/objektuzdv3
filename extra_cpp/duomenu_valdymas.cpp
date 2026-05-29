#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <random>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <stdexcept>

#include "../header_files/duomenu_valdymas.h"
#include "../header_files/mat_funkcijos.h"
#include "../header_files/output.h"
#include "../header_files/Vector.h"

using std::cin;
using std::cout;
using std::string;
using std::numeric_limits;
using std::streamsize;
using std::ifstream;
using std::ofstream;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::sort;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::runtime_error;
using std::exception;




// Atsitiktiniu skaiciu generavimas
void generuotiPaz(Vector<Studentas>& grupe) {
    srand(time(0));

    bool testiStudenta = true;

    while (testiStudenta) {
        Studentas A;

        bool vardasGeras = false;
        while (!vardasGeras) {
            cout << "Iveskite varda ir pavarde: ";
            cin >> std::ws; string v, p; cin >> v >> p; A.setVardas(v); A.setPavarde(p);

            if (!arTikRaides(A.getVardas()) || !arTikRaides(A.getPavarde())) {
                cout << "Klaida! Vardas ir pavarde turi buti sudaryti tik is raidziu!\n";
                cin.clear();
            }
            else {
                vardasGeras = true;
            }
        }

        cout << string(80, '-') << "\n";

        // Automatiskai generuojamas atsitiktinis pazymiu kiekis (3-10)
        int n = rand() % 8 + 3;
        A.reservePaz(n); // Atminties rezervacija pazymiams

        // Automatiskai generuojami pazymiai
        cout << "Sugeneruota " << n << " pazymiu: ";
        for (int i = 0; i < n; i++) {
            int temp = generuotiPazymi();
            A.addPaz(temp);
            cout << temp << " ";
        }
        cout << "\n";

        // Automatiskai generuojamas egzaminas
        A.setEgz(generuotiEgzamina());
        cout << "Egzamino ivertinimas: " << A.getEgz() << "\n";
        cout << string(80, '-') << "\n";

        // Vidurkio skaiciavimas
        if (!A.isPazEmpty()) {
            double vid = vidurkis(A.getPaz());
            A.setRez(galutinisBalas(vid, A.getEgz()));
            // Medianos skaiciavimas
            double med = mediana(A.getPaz());
            A.setMed(galutinisBalas(med, A.getEgz()));
        }
        else {
            A.setRez(A.getEgz() * 0.6);
            A.setMed(A.getEgz() * 0.6);
        }

        grupe.push_back(A);

        // Klausimas ar testi
        char atsakymas;
        bool atsakymasTeisingas = false;
        while (!atsakymasTeisingas) {
            cout << "Ar norite generuoti dar viena studenta? (T/N): ";
            cin >> atsakymas;
            if (atsakymas == 'T' || atsakymas == 't') {
                testiStudenta = true;
                atsakymasTeisingas = true;
                cout << string(80, '-') << "\n";
            }
            else if (atsakymas == 'N' || atsakymas == 'n') {
                testiStudenta = false;
                atsakymasTeisingas = true;
            }
            else {
                cout << "Klaida! Iveskite T arba N!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

void generuotiVardIrPav(Vector<Studentas>& grupe) {
    srand(time(0));

    try {
        // Nuskaitome failus
        vector<string> vyruVard, vyruPav, motVard, motPav;
        ifstream vvard("../vpv/vvard.txt");
        ifstream vpav("../vpv/vpav.txt");
        ifstream mvard("../vpv/mvard.txt");
        ifstream mpav("../vpv/mpav.txt");

        // Patikrinimas ar failai atsidare
        if (!vvard.is_open() || !vpav.is_open() || !mvard.is_open() || !mpav.is_open()) {
            throw runtime_error("Nepavyko atidaryti vieno ar daugiau failu su vardais ir pavardemis!");
        }

        // Nuskaitomi visi vardai ir pavardes
        string eilute;
        while (vvard >> eilute) vyruVard.push_back(eilute);
        while (vpav >> eilute) vyruPav.push_back(eilute);
        while (mvard >> eilute) motVard.push_back(eilute);
        while (mpav >> eilute) motPav.push_back(eilute);

        vvard.close();
        vpav.close();
        mvard.close();
        mpav.close();

        // Patikrinama ar failai ne tusti
        if (vyruVard.empty() || vyruPav.empty() || motVard.empty() || motPav.empty()) {
            throw runtime_error("Vienas ar daugiau failu yra tusti!");
        }

    bool testiStudenta = true;

    while (testiStudenta) {
        Studentas A;

        // Atsitiktinai parenka lyti (0 - vyras, 1 - moteris)
        int lytis = rand() % 2;

        // Generuojamas vardas ir pavarde pagal lyti
        if (lytis == 0) {
            int vardIndex = rand() % vyruVard.size();
            int pavIndex = rand() % vyruPav.size();
            A.setVardas(vyruVard[vardIndex]);
            A.setPavarde(vyruPav[pavIndex]);
        }
        else {
            int vardIndex = rand() % motVard.size();
            int pavIndex = rand() % motPav.size();
            A.setVardas(motVard[vardIndex]);
            A.setPavarde(motPav[pavIndex]);
        }

        cout << "Sugeneruotas vardas ir pavarde: " << A.getVardas() << " " << A.getPavarde() << "\n";
        cout << string(80, '-') << "\n";

        // Automatiskai generuojamas atsitiktinis pazymiu kiekis (3-10)
        int n = rand() % 8 + 3;
        A.reservePaz(n); // Atminties rezervacija pazymiams

        // Automatiskai sugeneruojami pazymiai
        cout << "Sugeneruota " << n << " pazymiu: ";
        for (int i = 0; i < n; i++) {
            int temp = generuotiPazymi();
            A.addPaz(temp);
            cout << temp << " ";
        }
        cout << "\n";

        // Automatiskai sugeneruojamas egzaminas
        A.setEgz(generuotiEgzamina());
        cout << "Egzamino ivertinimas: " << A.getEgz() << "\n";
        cout << string(80, '-') << "\n";

        // Vidurkio skaiciavimas
        if (!A.isPazEmpty()) {
            double vid = vidurkis(A.getPaz());
            A.setRez(galutinisBalas(vid, A.getEgz()));
            // Medianos skaiciavimas
            double med = mediana(A.getPaz());
            A.setMed(galutinisBalas(med, A.getEgz()));
        }
        else {
            A.setRez(A.getEgz() * 0.6);
            A.setMed(A.getEgz() * 0.6);
        }

        grupe.push_back(A);

        // Klausimas ar testi
        char atsakymas;
        bool atsakymasTeisingas = false;
        while (!atsakymasTeisingas) {
            cout << "Ar norite generuoti dar viena studenta? (T/N): ";
            cin >> atsakymas;
            if (atsakymas == 'T' || atsakymas == 't') {
                testiStudenta = true;
                atsakymasTeisingas = true;
                cout << string(80, '-') << "\n";
            }
            else if (atsakymas == 'N' || atsakymas == 'n') {
                testiStudenta = false;
                atsakymasTeisingas = true;
            }
            else {
                cout << "Klaida! Iveskite T arba N!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    }
    catch (const runtime_error& e) {
        cout << "Klaida generuojant studentus: " << e.what() << "\n";
    }
    catch (const exception& e) {
        cout << "Netiketa klaida: " << e.what() << "\n";
    }
}

void skaitytiIsFailo(Vector<Studentas>& grupe) {
    try {
        string failoPavadinimas;
        cout << "Iveskite failo pavadinima: ";
        cin >> failoPavadinimas;

        // Pridedamas testuojamas katalogas
        string kelias = "..\\studentai_test\\" + failoPavadinimas;

        ifstream failas(kelias);
        if (!failas.is_open()) {
            throw runtime_error("Nepavyko atidaryti failo: " + kelias);
        }

        // Praleidziama antraste
        string eilute;
        getline(failas, eilute);

        // Skaitomi studentai
        while (failas >> eilute) {
            Studentas A;
            A.setVardas(eilute);
            failas >> A.getPavarde();

            vector<int> paz;
            paz.reserve(15); // Rezervuojama talpa (~15 pazymiu dazniausiai pakanka)
            int sk;
            while (failas >> sk) {
                paz.push_back(sk);
                if (failas.peek() == '\n') break;
            }

            if (!paz.empty()) {
                A.setEgz(paz.back());
                paz.pop_back();
                A.setPaz(paz);
                A.setRez(galutinisBalas(vidurkis(A.getPaz()), A.getEgz()));
                A.setMed(galutinisBalas(mediana(A.getPaz()), A.getEgz()));
                grupe.push_back(A);
            }
            failas.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        failas.close();

        if (grupe.empty()) {
            throw runtime_error("Failas yra tuscias arba neteisingai formatuotas!");
        }

        cout << "Nuskaityta " << grupe.size() << " studentu!\n";

        // Klausiama kur isvesti rezultatus
        if (!grupe.empty()) {
            cout << string(80, '-') << "\n";
            cout << "Pasirinkite isvesties buda:\n";
            cout << "1. Isvesti i terminala\n";
            cout << "2. Irasyti i faila\n";
            int isvestiesPasirinkimas;
            while (!(cin >> isvestiesPasirinkimas) || (isvestiesPasirinkimas != 1 && isvestiesPasirinkimas != 2)) {
                cout << "Klaida! Pasirinkite 1 arba 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (isvestiesPasirinkimas == 1) {
                outputas(grupe);
            }
            else {
                rasytIFaila(grupe);
            }
        }
    }
    catch (const runtime_error& e) {
        cout << "Klaida skaitant is failo: " << e.what() << "\n";
    }
    catch (const exception& e) {
        cout << "Netiketa klaida: " << e.what() << "\n";
    }
}

void rasytIFaila(Vector<Studentas>& grupe) {
    if (grupe.empty()) {
        cout << "Nera studentu duomenu!\n";
        return;
    }

    // Klausiama kaip rusiuoti
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
        sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.getVardas() < b.getVardas();
            });
        break;
    case 2:
        sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.getPavarde() < b.getPavarde();
            });
        break;
    case 3:
        sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.getRez() < b.getRez();
            });
        break;
    case 4:
        sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.getMed() < b.getMed();
            });
        break;
    default:
        cout << "Klaida! Neteisingas pasirinkimas. Rodoma be rusiavimo.\n";
        break;
    }

    // Baigiamas rusiavimo laiko matavimas
    auto pabaiga = high_resolution_clock::now();
    duration<double> trukme = pabaiga - pradzia;

    // Klausiama failo pavadinimo
    string isvestiesFailas;
    cout << string(80, '-') << "\n";
    cout << "Iveskite isvesties failo pavadinima: ";
    cin >> isvestiesFailas;

    // Sukuriamas kelias i testuojama kataloga
    string kelias = "..\\studentai_test\\" + isvestiesFailas;

    ofstream failas(kelias);
    if (!failas.is_open()) {
        cout << "Klaida! Nepavyko sukurti failo: " << kelias << "\n";
        return;
    }

    // Antrastes eilute
    failas << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
        << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)\n";
    failas << string(80, '-') << "\n";

    // Studentu duomenys
    for (const auto& A : grupe) {
        failas << left << setw(20) << A.getVardas() << setw(20) << A.getPavarde()
            << setw(20) << fixed << setprecision(2) << A.getRez()
            << setw(20) << fixed << setprecision(2) << A.getMed() << "\n";
    }

    failas.close();

    cout << string(80, '-') << "\n";
    cout << "Duomenys sekmingai irasyti i faila: " << kelias << "\n";
    cout << "Ivykdymo laikas: " << fixed << setprecision(7) << trukme.count() << " s\n";
}
