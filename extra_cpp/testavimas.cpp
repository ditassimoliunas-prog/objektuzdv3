#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <list>
#include <deque>
#include <type_traits>
#include <iterator>  // std::make_move_iterator
#include <filesystem>

#include "../header_files/testavimas.h"
#include "../header_files/mat_funkcijos.h"
#include "../header_files/Vector.h"

namespace fs = std::filesystem;

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::fixed;
using std::setprecision;
using std::left;
using std::setw;
using std::to_string;
using std::move;
using std::list;
using std::deque;

const vector<int> SZ = { 1000, 10000, 100000, 1000000, 10000000 };
const int paz_kiekis = 5;

void ensureDirectoriesExist() {
    try {
        if (!fs::exists("Studentai_test")) {
            fs::create_directory("Studentai_test");
        }
        if (!fs::exists("vargsiukai")) {
            fs::create_directory("vargsiukai");
        }
        if (!fs::exists("kietiakai")) {
            fs::create_directory("kietiakai");
        }
    } catch (const std::exception& e) {
        cout << "Klaida kuriant direktorijas: " << e.what() << "\n";
    }
}

void sukurtiTestavimoFailus() {
    ensureDirectoriesExist();

    int pas;
    cout << "\nPasirinkite, kuri faila norite sukurti:\n";
    cout << "1. 1000 irasu\n";
    cout << "2. 10000 irasu\n";
    cout << "3. 100000 irasu\n";
    cout << "4. 1000000 irasu\n";
    cout << "5. 10000000 irasu\n";
    cout << "6. Visus auksciau isvardintus\n";
    cout << "Jusu pasirinkimas: ";
    cin >> pas;

    vector<int> pasirinkti_SZ;
    if (pas == 1) pasirinkti_SZ = { 1000 };
    else if (pas == 2) pasirinkti_SZ = { 10000 };
    else if (pas == 3) pasirinkti_SZ = { 100000 };
    else if (pas == 4) pasirinkti_SZ = { 1000000 };
    else if (pas == 5) pasirinkti_SZ = { 10000000 };
    else if (pas == 6) pasirinkti_SZ = SZ;
    else {
        cout << "Neteisingas pasirinkimas!\n";
        return;
    }

    srand(static_cast<unsigned>(time(nullptr)));
    cout << "Failu kurimas prasidejo...\n";
    cout << string(80, '-') << "-\n";

    for (int n : pasirinkti_SZ) {
        string fname = "Studentai_test\\studentai_" + to_string(n) + ".txt";

        // Pradedamas matuoti laikas tiems irasams kurti 
        auto start = high_resolution_clock::now();
        
        ofstream out(fname);
        
        // Antraste
        out << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
        for (int i = 1; i <= paz_kiekis; i++) {
            out << setw(8) << ("ND" + to_string(i));
        }
        out << "Egz\n";

        // Tiesiai irasome i faila (be vektoriu pagal uzduoties salyga)
        for (int i = 1; i <= n; i++) {
            out << left << setw(20) << ("Vardas" + to_string(i)) << setw(20) << ("Pavarde" + to_string(i));
            for (int k = 0; k < paz_kiekis; k++) {
                out << setw(8) << (rand() % 10 + 1);
            }
            out << (rand() % 10 + 1) << "\n";
        }
        out.close();

        // Stabdyti laikmati ir isvesti i ekrana laika
        auto end = high_resolution_clock::now();
        duration<double> diff = end - start;
        
        cout << n << " irasu failo sukurimo laikas: " << fixed << setprecision(5) << diff.count() << " s.\n";
    }
}

template <typename Container>
void nuskaitytiDuomenis(const string& fname, Container& grupe) {
    ifstream in(fname);
    string header;
    std::getline(in, header);

    Studentas st;
    st.reservePaz(paz_kiekis);

    while (true) { 
        string v, p; 
        if (!(in >> v >> p)) break; 
        st.setVardas(v); 
        st.setPavarde(p);
        st.clearPaz();
        int pr;
        for (int i = 0; i < paz_kiekis; i++) {
            in >> pr;
            st.addPaz(pr);
        }
        int egz; in >> egz; st.setEgz(egz);
        st.setRez(galutinisBalas(vidurkis(st.getPaz()), st.getEgz()));
        grupe.push_back(st);
    }
    in.close();
}

template <typename Container>
double tirtiKonteineri(int n, const string& fname, int strat) {
    auto total_start = high_resolution_clock::now();

    // 1. Duomenu nuskaitymas is failo
    auto start = high_resolution_clock::now();

    Container grupe;
    if constexpr (std::is_same_v<Container, vector<Studentas>>) {
        try {
            grupe.reserve(n); // list neturi reserve() funkcijos
        } catch (const std::exception& e) {
            cout << "Nepakanka atminties rezervuoti " << n << " elementu!\n";
            return 0.0;
        }
    }

    nuskaitytiDuomenis(fname, grupe);

    auto end = high_resolution_clock::now();
    duration<double> ms_read = end - start;
    cout << n << " Irasu failo nuskaitymo laikas: " << fixed << setprecision(5) << ms_read.count() << " s.\n";

    // 2. Rusiavimas
    start = high_resolution_clock::now();
    if constexpr (std::is_same_v<Container, list<Studentas>>) {
        grupe.sort([](const Studentas& a, const Studentas& b) {
            return a.getRez() < b.getRez();
        });
    } else {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.getRez() < b.getRez();
        });
    }
    end = high_resolution_clock::now();
    duration<double> ms_sort = end - start;
    cout << n << " Irasu rusiavimas didejimo tvarka: " << fixed << setprecision(5) << ms_sort.count() << " s.\n";

    // 3. Skirstymas i dvi grupes
    start = high_resolution_clock::now();
    Container vargsiukai;
    Container kietiakai;

    if (strat == 1) {
        if constexpr (std::is_same_v<Container, vector<Studentas>>) {
            vargsiukai.reserve(n / 2 + 100);
            kietiakai.reserve(n / 2 + 100);
        }

        for (auto& s : grupe) {
            if (s.getRez() < 5.0) {
                vargsiukai.push_back(move(s));
            }
            else {
                kietiakai.push_back(move(s));
            }
        }
        Container().swap(grupe); // Isvalome pradini konteineri
    }
    else if (strat == 2) {
        if constexpr (std::is_same_v<Container, vector<Studentas>>) {
            // Sukrupuojame vektoriu vietoje (O(N) laikas): 
            auto splitPoint = std::partition(grupe.begin(), grupe.end(), [](const Studentas& s) {
                return s.getRez() >= 5.0; // Salyga kietiakams
            });

            // Iš anksto rezervuojame atminties vargšiukams (nebutina, bet dar labiau pagreitina)
            vargsiukai.reserve(std::distance(splitPoint, grupe.end()));

            // NAUDOJAME MOVE: Perkeliame vargšiukus iš pagrindinio vektoriaus galo i naujaji.
            vargsiukai.insert(vargsiukai.end(), 
                              std::make_move_iterator(splitPoint), 
                              std::make_move_iterator(grupe.end()));

            // Ištriname perkeltus elementus iš originalaus vektoriaus.
            grupe.erase(splitPoint, grupe.end());
            kietiakai = move(grupe); // Like grupeje yra kietiakai
        }
        else {
            auto it = grupe.begin();
            while (it != grupe.end()) {
                if (it->getRez() < 5.0) {
                    vargsiukai.push_back(move(*it));
                    it = grupe.erase(it); // vector/deque atveju tai leta, list atveju - greita
                }
                else {
                    ++it;
                }
            }
            kietiakai = move(grupe); // Like grupeje yra kietiakai
        }
    }
    else if (strat == 3) {
        if constexpr (std::is_same_v<Container, list<Studentas>>) {
            // list atveju efektyviausia yra iškirpti elementus per splice + remove_if ar pagal salyga
            auto it = std::partition(grupe.begin(), grupe.end(), [](const Studentas& s) {
                return s.getRez() < 5.0; // Vargšiukaikeliauja i pati prieki
            });
            // Iškerpame vargšiukus iš grupes tiesiai i vargšiuku list be memory re-allocation
            vargsiukai.splice(vargsiukai.begin(), grupe, grupe.begin(), it);
            kietiakai = move(grupe);
        }
        else {
            // std::vector ir std::deque atveju efektyviausa naudoti std::partition in-place
            if constexpr (std::is_same_v<Container, vector<Studentas>>) {
                vargsiukai.reserve(n / 2 + 100);
            }
            auto it = std::stable_partition(grupe.begin(), grupe.end(), [](const Studentas& s) {
                return s.getRez() < 5.0;
            });

            // Iteruojam per pradžia kur atsidure vargšiukai po stable_partition pakeitimu
            vargsiukai.insert(vargsiukai.end(), std::make_move_iterator(grupe.begin()), std::make_move_iterator(it));
            // Kas liko originalioj grupej iteruojame i kietiakius (nuo it iki end)
            kietiakai.insert(kietiakai.end(), std::make_move_iterator(it), std::make_move_iterator(grupe.end()));

            Container().swap(grupe); // Sunaikinam originala
        }
    }

    end = high_resolution_clock::now();
    duration<double> ms_split = end - start;
    cout << n << " Irasu dalijimo laikas (" << strat << "-a strategija): " << fixed << setprecision(5) << ms_split.count() << " s.\n";

    // 4.1 Irasome vargsiukus i faila
    start = high_resolution_clock::now();
    ofstream outV("vargsiukai\\vargsiukai_" + to_string(n) + ".txt");
    outV << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << "Galutinis (Vid.)\n";
    for (const auto& s : vargsiukai) {
        outV << left << setw(20) << s.getVardas() << setw(20) << s.getPavarde() << fixed << setprecision(2) << s.getRez() << "\n";
    }
    outV.close();
    Container().swap(vargsiukai); // Islaisviname RAM perrasydami!
    end = high_resolution_clock::now();
    duration<double> ms_write_v = end - start;
    cout << n << " Irasu 'vargsiuku' irasymo laikas: " << fixed << setprecision(5) << ms_write_v.count() << " s.\n";

    // 4.2 Irasome kietiakius i faila
    start = high_resolution_clock::now();
    ofstream outK("kietiakai\\kietiakai_" + to_string(n) + ".txt");
    outK << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << "Galutinis (Vid.)\n";
    for (const auto& s : kietiakai) {
        outK << left << setw(20) << s.getVardas() << setw(20) << s.getPavarde() << fixed << setprecision(2) << s.getRez() << "\n";
    }
    outK.close();
    Container().swap(kietiakai); // Islaisviname ir kietiakius!
    end = high_resolution_clock::now();
    duration<double> ms_write_k = end - start;
    cout << n << " Irasu 'kietiaku' irasymo laikas: " << fixed << setprecision(5) << ms_write_k.count() << " s.\n";

    // Bendras laikas
    auto total_end = high_resolution_clock::now();
    duration<double> ms_total = total_end - total_start;
    return ms_total.count();
}

void atliktiSpartosAnalize() {
    ensureDirectoriesExist();

    int pas, kont, strat, test_kartai;
    cout << "\nPasirinkite, su kuriuo failu norite atlikti spartos analize:\n";
    cout << "1. 1000 irasu failas\n";
    cout << "2. 10000 irasu failas\n";
    cout << "3. 100000 irasu failas\n";
    cout << "4. 1000000 irasu failas\n";
    cout << "5. 10000000 irasu failas\n";
    cout << "6. Visi failai is eiles\n";
    cout << "Jusu pasirinkimas: ";
    cin >> pas;

    vector<int> pasirinkti_SZ;
    if (pas == 1) pasirinkti_SZ = { 1000 };
    else if (pas == 2) pasirinkti_SZ = { 10000 };
    else if (pas == 3) pasirinkti_SZ = { 100000 };
    else if (pas == 4) pasirinkti_SZ = { 1000000 };
    else if (pas == 5) pasirinkti_SZ = { 10000000 };
    else if (pas == 6) pasirinkti_SZ = SZ;
    else {
        cout << "Neteisingas pasirinkimas!\n";
        return;
    }

    cout << "\nPasirinkite konteinerio tipa testavimui:\n";
    cout << "1. std::vector\n";
    cout << "2. std::list\n";
    cout << "3. std::deque\n";
    cout << "4. Vector (custom)\n";
    cout << "Jusu pasirinkimas: ";
    cin >> kont;

    cout << "\nPasirinkite testavimo strategija:\n";
    cout << "1. 1 strategija (Sukurti 2 naujus konteinerius)\n";
    cout << "2. 2 strategija (Sukurti 1 nauja konteineri, trinti is pagrindinio)\n";
    cout << "3. 3 strategija (Optimizuoti algoritmu metodai)\n";
    cout << "Jusu pasirinkimas: ";
    cin >> strat;

    cout << "\nIveskite, kiek kartu norite pakartoti testavima (laiku vidurkiui): ";
    cin >> test_kartai;

    cout << "\nPradedama spartos analize pagal nurodytus zingsnius...\n";

    for (int n : pasirinkti_SZ) {
        string fname = "Studentai_test\\studentai_" + to_string(n) + ".txt";

        // Tikrinimas ar failas atsidaro nenaudojant filesystem
        ifstream patikrinimas(fname);
        if (!patikrinimas.good()) {
            cout << "Failo " << fname << " nera. Praleidziama.\n";
            continue;
        }
        patikrinimas.close();

        cout << string(80, '-') << "\n";
        cout << n << " Irasu spartos analize\n";
        cout << string(80, '-') << "\n";

        double visas_laikas = 0.0;

        for (int i = 0; i < test_kartai; i++) {
            cout << "\nTESTO NUMERIS: " << i + 1 << "\n";
            if (kont == 1) visas_laikas += tirtiKonteineri<vector<Studentas>>(n, fname, strat);
            else if (kont == 2) visas_laikas += tirtiKonteineri<list<Studentas>>(n, fname, strat);
            else if (kont == 3) visas_laikas += tirtiKonteineri<deque<Studentas>>(n, fname, strat);
            else if (kont == 4) visas_laikas += tirtiKonteineri<Vector<Studentas>>(n, fname, strat);
            else {
                cout << "Neteisingas konteinerio tipas!\n";
                return;
            }
        }
        cout << "\n========================================\n";
        cout << "Vidutinis viso testo (nuskaitymas+dalijimas+isvedimas) laikas po " << test_kartai << " bandymu:\n";
        cout << fixed << setprecision(5) << visas_laikas / test_kartai << " s.\n";
        cout << "========================================\n\n";
    }
}

void PadalintiStudentusZabioGreiciu(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiukai) {
    
    // 1. Sukrupuojame vektoriu vietoje (O(N) laikas): 
    // Visi, kuriu balas >= 5.0 atsiduria priekyje, o < 5.0 - gale.
    // Jei jums BUTINA išlaikyti jau esama eiliškuma (pvz., abecelini), 
    // vietoj 'std::partition' naudokite 'std::stable_partition'.
    auto splitPoint = std::partition(studentai.begin(), studentai.end(), [](const Studentas& s) {
        return s.getRez() >= 5.0; // Pakeista is galutinis i rez
    });

    // 2. Iš anksto rezervuojame atminties vargšiukams (nebutina, bet dar labiau pagreitina)
    vargsiukai.reserve(std::distance(splitPoint, studentai.end()));

    // 3. NAUDOJAME MOVE: Perkeliame vargšiukus iš pagrindinio vektoriaus galo i naujaji.
    // std::make_move_iterator užtikrina, kad tekstai ir kiti duomenys nebutu kopijuojami iš naujo.
    vargsiukai.insert(vargsiukai.end(), 
                      std::make_move_iterator(splitPoint), 
                      std::make_move_iterator(studentai.end()));

    // 4. Ištriname perkeltus elementus iš originalaus vektoriaus.
    // Kadangi triname IŠ GALO, jokio duomenu stumdymo nebelieka - operacija ivyksta per O(1).
    studentai.erase(splitPoint, studentai.end());
}
