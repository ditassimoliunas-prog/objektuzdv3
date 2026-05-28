#pragma once

#include <string>
#include <vector>
#include "Vector.h"

using std::string;
using std::vector;

bool arTikRaides(const string& str);
double mediana(vector <int> paz);
double vidurkis(const vector<int>& paz); // Priima per referencą greičiui
double galutinisBalas(double vidMed, int egz);
int generuotiPazymi();
int generuotiEgzamina();

// Vector versions
double mediana(Vector <int> paz);
double vidurkis(const Vector<int>& paz);

