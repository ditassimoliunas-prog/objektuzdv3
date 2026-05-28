#pragma once

#include <iostream>
#include <string>
#include "Vector.h"
#include "Zmogus.h"

using std::string;

// Išvestinė klasė iš Zmogus - aprašo studentą
// Paveldi žmogaus duomenis (vardas, pavardė) iš Zmogus klasės
// Turi papildomus duomenis: pažymius, egzamino rezultatą ir galutinius rezultatus
// Implementuoja Rule of Five
class Studentas : public Zmogus {
private:
    Vector<int> paz_;
    int egz_;
    double rez_;
    double med_;

    // Privatas helperis skaičiavimams
    void paskaiciuotiGalutinius();

    // Implementacija abstraktaus metodo iš Zmogus
    virtual void paskaiciuoti() override;

public:
    // Numatytasis konstruktorius
    Studentas() : Zmogus("A", "BB"), egz_(0), rez_(0.0), med_(0.0) {}

    // Parametrizuotas konstruktorius
    Studentas(string v, string p, int e) : Zmogus(v, p), egz_(e), rez_(0.0), med_(0.0) {}

    // Konstruktorius su nuskaitymu is srauto
    Studentas(std::istream& is);

    // Rule of Five

    // Destruktorius
    ~Studentas();

    // Copy konstruktorius
    Studentas(const Studentas& other);

    // Copy assignment operator
    Studentas& operator=(const Studentas& other);

    // Move konstruktorius
    Studentas(Studentas&& other) noexcept;

    // Move assignment operator
    Studentas& operator=(Studentas&& other) noexcept;

    // Getters
    inline const Vector<int>& getPaz() const { return paz_; }
    inline Vector<int>& getPaz() { return paz_; }
    inline int getEgz() const { return egz_; }
    inline double getRez() const { return rez_; }
    inline double getMed() const { return med_; }

    // Setters
    inline void setEgz(int e) { egz_ = e; }
    inline void setRez(double r) { rez_ = r; }
    inline void setMed(double m) { med_ = m; }

    // Darbas su pažymiais
    inline void addPaz(int p) { paz_.push_back(p); }
    inline void clearPaz() { paz_.clear(); }
    inline void reservePaz(size_t n) { paz_.reserve(n); }
    inline bool isPazEmpty() const { return paz_.empty(); }
    inline void setPaz(const Vector<int>& p) { paz_ = p; }

    // Skaitymas ir skaičiavimas
    std::istream& readStudent(std::istream& is);

    // Implementacija abstraktaus metodo iš Zmogus
    virtual string getInfo() const override;

    // I/O operatoriai
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
    friend std::istream& operator>>(std::istream& is, Studentas& s);
};

// Ne klasės narės, bet su klase tiesiogiai susijusios lyginimo funkcijos
bool comparePagalVarda(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalReza(const Studentas& a, const Studentas& b);
bool comparePagalMeda(const Studentas& a, const Studentas& b);

