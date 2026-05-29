#include <iostream>
#include <limits>

#include "../header_files/input.h"
#include "../header_files/mat_funkcijos.h"
#include "../header_files/Vector.h"

using std::cin;
using std::cout;
using std::string;
using std::numeric_limits;
using std::streamsize;

void inputas(Vector<Studentas>& grupe) {
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
        cout << "Iveskite semestro ivertinimus (0-10). Iveskite -1 kad baigtumete: \n";
        A.reservePaz(15); // Rezervuojama vieta pazymiams (sumazina atminties reallokacijas)
        int temp;
        while (true) {
            cout << "Iveskite pazymi (arba -1 kad baigtumete): ";
            if (!(cin >> temp)) {
                cout << "Klaida! Iveskite skaiciu!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (temp == -1) {
                break;
            }
            else if (temp < 0 || temp > 10) {
                cout << "Klaida! Pazymys turi buti nuo 0 iki 10!\n";
            }
            else {
                A.addPaz(temp);
            }
        }

        cout << string(80, '-') << "\n";

        bool egzaminasTeisingas = false;
        while (!egzaminasTeisingas) {
            cout << "Iveskite egzamina (0-10): ";
            int e; if (!(cin >> e)) {
                cout << "Klaida! Iveskite skaiciu!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (e < 0 || e > 10) {
                cout << "Klaida! Egzaminas turi buti nuo 0 iki 10!\n";
            }
            else {
                A.setEgz(e); egzaminasTeisingas = true;
            }
        }
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
        A.clearPaz();

        // Klausimas ar testi rankini generavima
        char atsakymas;
        bool atsakymasTeisingas = false;
        while (!atsakymasTeisingas) {
            cout << "Ar norite ivesti dar viena studenta? (T/N): ";
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

