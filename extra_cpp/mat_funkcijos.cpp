#include "../header_files/mat_funkcijos.h"
#include <algorithm>
#include <cctype>
#include <ctime>

using std::sort;

// Funkcija patikrinti ar vardas/pavarde turi tik raides, neleidzia jokiu simboliu
bool arTikRaides(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

// Medianos funkcija
double mediana(vector <int> paz) {
    if (paz.empty()) return 0.0;

    vector <int> temp = paz;
    sort(temp.begin(), temp.end());
    int n = temp.size();
    if (n % 2 == 0) {
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
    else {
        return temp[n / 2];
    }
}

// Vidurkio skaiciavimas is pazymiu vektoriaus
double vidurkis(const vector<int>& paz) {
    if (paz.empty()) return 0.0;
    int sum = 0;
    for (int p : paz) {
        sum += p;
    }
    return sum * 1.0 / paz.size();
}

// Galutinio balo skaiciavimas pagal vidurki/mediana ir egzamina
double galutinisBalas(double vidMed, int egz) {
    return vidMed * 0.4 + egz * 0.6;
}

// Generuoti atsitiktini pazymi nuo 0 iki 10
int generuotiPazymi() {
    return rand() % 11;
}

// Generuoti atsitiktini egzamina nuo 0 iki 10
int generuotiEgzamina() {
    return rand() % 11;
}

// Vector versions
double mediana(Vector <int> paz) {
    if (paz.empty()) return 0.0;

    Vector <int> temp = paz;
    sort(temp.begin(), temp.end());
    int n = temp.size();
    if (n % 2 == 0) {
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
    else {
        return temp[n / 2];
    }
}

// Vidurkio skaiciavimas is Vector pazymiu
double vidurkis(const Vector<int>& paz) {
    if (paz.empty()) return 0.0;
    int sum = 0;
    for (int p : paz) {
        sum += p;
    }
    return sum * 1.0 / paz.size();
}
