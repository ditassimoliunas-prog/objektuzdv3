#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include "header_files/Studentas.h"
#include "header_files/Vector.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;

int testai_praletii = 0;
int testai_nepraletii = 0;

void printTestHeader(const string& testName) {
    cout << "\n" << string(60, '=') << endl;
    cout << "TEST: " << testName << endl;
    cout << string(60, '=') << endl;
}

void testPassed(const string& info) {
    cout << "[PRIIMTAS] " << info << endl;
    testai_praletii++;
}

void testFailed(const string& info) {
    cout << "[NEPRIIMTAS] " << info << endl;
    testai_nepraletii++;
}

// TEST #1: Default konstruktorius
void test_default_constructor() {
    printTestHeader("Default Konstruktorius");

    Studentas s;

    assert(s.getVardas() == "A");
    testPassed("Vardas inicijuotas i 'A'");

    assert(s.getPavarde() == "BB");
    testPassed("Pavarde inicijuota i 'BB'");

    assert(s.getEgz() == 0);
    testPassed("Egzaminas inicijuotas i 0");

    assert(s.getRez() == 0.0);
    testPassed("Rezultatas inicijuotas i 0.0");

    assert(s.getMed() == 0.0);
    testPassed("Mediana inicijuota i 0.0");

    assert(s.isPazEmpty());
    testPassed("Pazymiai sarasas tucias");
}

// TEST #2: Parametrizuotas konstruktorius
void test_parametrized_constructor() {
    printTestHeader("Parametrizuotas Konstruktorius");

    Studentas s("Jonas", "Jonaitis", 95);

    assert(s.getVardas() == "Jonas");
    testPassed("Vardas teisingai priskirtas");

    assert(s.getPavarde() == "Jonaitis");
    testPassed("Pavarde teisingai priskirta");

    assert(s.getEgz() == 95);
    testPassed("Egzaminas teisingai priskirtas");
}

// TEST #3: Copy konstruktorius
void test_copy_constructor() {
    printTestHeader("Copy Konstruktorius");

    Studentas s1("Petras", "Petrauskas", 85);
    s1.addPaz(8);
    s1.addPaz(9);
    s1.addPaz(10);

    // Kuriam kopija
    Studentas s2 = s1;

    assert(s2.getVardas() == s1.getVardas());
    testPassed("Kopijoje vardas sutampa");

    assert(s2.getPavarde() == s1.getPavarde());
    testPassed("Kopijoje pavarde sutampa");

    assert(s2.getEgz() == s1.getEgz());
    testPassed("Kopijoje egzaminas sutampa");

    assert(s2.getPaz().size() == s1.getPaz().size());
    testPassed("Kopijoje pazymiu kiekis sutampa");

    assert(s2.getPaz()[0] == s1.getPaz()[0]);
    testPassed("Kopijoje pazymiu vertes sutampa");

    // Tikriname, kad tai skirtingi objektai (deep copy)
    Studentas s3 = s1;
    s3.addPaz(100);
    assert(s1.getPaz().size() != s3.getPaz().size());
    testPassed("Deep copy veikia - modifikacija nepaveikia originalo");
}

// TEST #4: Copy assignment operator
void test_copy_assignment() {
    printTestHeader("Copy Assignment Operatorius");

    Studentas s1("Marta", "Martine", 92);
    s1.addPaz(7);
    s1.addPaz(8);
    s1.addPaz(9);

    Studentas s2;
    s2 = s1;

    assert(s2.getVardas() == "Marta");
    testPassed("Priskyrimo metu vardas is naujo priskirtas");

    assert(s2.getPavarde() == "Martine");
    testPassed("Priskyrimo metu pavarde is naujo priskirta");

    assert(s2.getPaz().size() == 3);
    testPassed("Priskyrimo metu pazymiai is naujo priskirti");

    // Self-assignment check
    s2 = s2;
    assert(s2.getVardas() == "Marta");
    testPassed("Self-assignment saugiai veikia");
}

// TEST #5: Move konstruktorius
void test_move_constructor() {
    printTestHeader("Move Konstruktorius");

    Studentas s1("Laima", "Laima", 88);
    s1.addPaz(6);
    s1.addPaz(7);
    s1.addPaz(8);

    // Move konstruktorius
    Studentas s2 = std::move(s1);

    assert(s2.getVardas() == "Laima");
    testPassed("Move konstruktorius - vardas is naujo priskirtas");

    assert(s2.getPaz().size() == 3);
    testPassed("Move konstruktorius - pazymiai is naujo priskirti");

    // s1 turetu tureti tuscius pazymius
    assert(s1.isPazEmpty());
    testPassed("Move konstruktorius - saltinis istustintas");
}

// TEST #6: Move assignment operatorius
void test_move_assignment() {
    printTestHeader("Move Assignment Operatorius");

    Studentas s1("Ruta", "Rute", 90);
    s1.addPaz(5);
    s1.addPaz(6);
    s1.addPaz(7);

    Studentas s2;
    s2 = std::move(s1);

    assert(s2.getVardas() == "Ruta");
    testPassed("Move assignment - vardas is naujo priskirtas");

    assert(s2.getPaz().size() == 3);
    testPassed("Move assignment - pazymiai is naujo priskirti");

    assert(s1.isPazEmpty());
    testPassed("Move assignment - saltinis istustintas");

    // Self-move assignment check
    s2 = std::move(s2);
    assert(s2.getVardas() == "Ruta");
    testPassed("Move assignment self-assignment saugiai veikia");
}

// TEST #7: Destruktorius - RAII principas
void test_destructor() {
    printTestHeader("Destruktorius - RAII Principas");

    {
        Studentas s("Vidmantas", "Vidmante", 87);
        s.addPaz(9);
        s.addPaz(10);
        s.addPaz(8);

        assert(s.getPaz().size() == 3);
        testPassed("Destruktoriaus testas - objektas sukurtas");
    } // Cia is automatiskai kvieciamas destruktorius

    testPassed("Destruktor veikia be problemu (nera memory leaks)");
}

// TEST #8: Isvesties operatorius (operator<<)
void test_output_operator() {
    printTestHeader("Isvesties Operatorius (operator<<)");

    Studentas s("Darius", "Darius", 93);
    s.addPaz(9);
    s.addPaz(10);
    s.addPaz(9);

    stringstream ss;
    ss << s;
    string output = ss.str();

    assert(output.find("Vardas: Darius") != string::npos);
    testPassed("Isvestis - vardas rastas");

    assert(output.find("Pavarde: Darius") != string::npos);
    testPassed("Isvestis - pavarde rastas");

    assert(output.find("Egzaminas: 93") != string::npos);
    testPassed("Isvestis - egzaminas rastas");

    cout << "Isvesties pavyzdys: " << endl;
    cout << "  " << s << endl;
}

// TEST #9: Ivesties operatorius (operator>>)
void test_input_operator() {
    printTestHeader("Ivesties Operatorius (operator>>)");

    stringstream ss;
    ss << "Vaidas Vaidauskas 10 10 10 10 10 100";

    Studentas s;
    ss >> s;

    assert(s.getVardas() == "Vaidas");
    testPassed("Ivestis - vardas nuskaitytas");

    assert(s.getPavarde() == "Vaidauskas");
    testPassed("Ivestis - pavarde nuskaityta");

    assert(s.getEgz() == 100);
    testPassed("Ivestis - egzaminas nuskaitytas");

    assert(s.getPaz().size() == 5);
    testPassed("Ivestis - pazymiai nuskaityti");

    assert(s.getPaz()[0] == 10);
    testPassed("Ivestis - pazymio reiksme teisingai nuskaityta");
}

// TEST #10: I/O operatoriai kartu (Round-trip test)
void test_io_roundtrip() {
    printTestHeader("I/O Round-Trip Testas");

    Studentas s1("Kristina", "Kristina", 96);
    s1.addPaz(8);
    s1.addPaz(9);
    s1.addPaz(10);
    s1.addPaz(9);
    s1.addPaz(8);

    stringstream ss;
    ss << s1.getVardas() << " " << s1.getPavarde();
    for (int paz : s1.getPaz()) {
        ss << " " << paz;
    }
    ss << " " << s1.getEgz();

    Studentas s2;
    ss >> s2;

    assert(s2.getVardas() == s1.getVardas());
    testPassed("Round-trip - vardas saugai issaugotas ir nuskaitytas");

    assert(s2.getPavarde() == s1.getPavarde());
    testPassed("Round-trip - pavarde saugai issaugotas ir nuskaitytas");

    assert(s2.getPaz() == s1.getPaz());
    testPassed("Round-trip - pazymiai saugai issaugoti ir nuskaityti");
}

// TEST #11: Modifikavimas po kopijavimo
void test_modification_after_copy() {
    printTestHeader("Modifikavimas po kopijavimo");

    Studentas s1("Elena", "Elene", 85);
    s1.addPaz(7);
    s1.addPaz(8);

    Studentas s2 = s1;

    s2.setEgz(95);
    assert(s1.getEgz() == 85 && s2.getEgz() == 95);
    testPassed("Egzamino modifikacija - originalas nepaveiktas");

    s2.addPaz(9);
    assert(s1.getPaz().size() == 2 && s2.getPaz().size() == 3);
    testPassed("Pazymio pridejimas - originalas nepaveiktas");
}

// TEST #12: Getter/Setter operaciju konsekvencija
void test_getters_setters() {
    printTestHeader("Getters/Setters Konsekvencija");

    Studentas s;

    s.setVardas("Tomas");
    assert(s.getVardas() == "Tomas");
    testPassed("Vardas setter/getter veikia");

    s.setPavarde("Tomas");
    assert(s.getPavarde() == "Tomas");
    testPassed("Pavarde setter/getter veikia");

    s.setEgz(100);
    assert(s.getEgz() == 100);
    testPassed("Egzaminas setter/getter veikia");

    s.setRez(90.5);
    assert(s.getRez() == 90.5);
    testPassed("Rezultatas setter/getter veikia");

    s.setMed(88.0);
    assert(s.getMed() == 88.0);
    testPassed("Mediana setter/getter veikia");
}

// TEST #13: Vector operacijos su pazymiais
void test_paz_operations() {
    printTestHeader("Vector Operacijos su Pazymiais");

    Studentas s;

    assert(s.isPazEmpty());
    testPassed("isPazEmpty() grazina true tusciam sarasui");

    s.addPaz(10);
    s.addPaz(9);
    assert(!s.isPazEmpty());
    testPassed("isPazEmpty() grazina false ne tusciam sarasui");

    assert(s.getPaz().size() == 2);
    testPassed("Pazymiai pridedami teisingai");

    s.clearPaz();
    assert(s.isPazEmpty());
    testPassed("clearPaz() isvalo pazymius");
}

// ========== PAPILDOMI GOOGLE TEST TESTAI (v2.0) ==========

// TEST #14: Vektoriaus su Studentais operacijos
TEST(StudentasVectorTest, PushBackCopySemantics) {
    vector<Studentas> students;

    Studentas s1("Audra", "Audre", 91);
    s1.addPaz(9);
    s1.addPaz(8);

    students.push_back(s1);  // Copy semantika

    EXPECT_EQ(students.size(), 1);
    EXPECT_EQ(students[0].getVardas(), "Audra");
    EXPECT_EQ(students[0].getPaz().size(), 2);
}

// TEST #15: Move semantika su vektoriumi
TEST(StudentasVectorTest, PushBackMoveSemantics) {
    vector<Studentas> students;

    Studentas s1("Giedra", "Giedre", 88);
    s1.addPaz(8);

    students.push_back(std::move(s1));  // Move semantika

    EXPECT_EQ(students.size(), 1);
    EXPECT_TRUE(s1.isPazEmpty());  // Originalas turi būti tuščias
    EXPECT_EQ(students[0].getVardas(), "Giedra");
}

// TEST #16: Deep copy - independenti duplikacija
TEST(StudentasDeepCopyTest, IndependentCopies) {
    Studentas original("Laimas", "Laimas", 92);
    original.addPaz(9);
    original.addPaz(10);

    Studentas copy1 = original;
    Studentas copy2 = original;

    // Modifikuojame copy1
    copy1.setEgz(100);
    copy1.addPaz(8);

    // Patikrinti, kad originalas ir copy2 nepakeisti
    EXPECT_EQ(original.getEgz(), 92);
    EXPECT_EQ(original.getPaz().size(), 2);
    EXPECT_EQ(copy2.getEgz(), 92);
    EXPECT_EQ(copy2.getPaz().size(), 2);
    EXPECT_EQ(copy1.getEgz(), 100);
    EXPECT_EQ(copy1.getPaz().size(), 3);
}

// TEST #17: Self-assignment saugumas
TEST(StudentasSelfAssignmentTest, CopySafetyCheck) {
    Studentas s("Monika", "Monika", 95);
    s.addPaz(10);
    s.addPaz(9);

    // Self-assignment - turi būti saugus
    s = s;

    EXPECT_EQ(s.getVardas(), "Monika");
    EXPECT_EQ(s.getEgz(), 95);
    EXPECT_EQ(s.getPaz().size(), 2);
}

// TEST #18: Operatoriaus lankstumo - chaining
TEST(StudentasOperatorTest, AssignmentChaining) {
    Studentas s1("Vincas", "Vincas", 92);
    Studentas s2("Petras", "Petrauskas", 88);
    Studentas s3;

    // Assignment chaining: (s3 = s2) = s1;
    // Step 1: s3 = s2 grąžina s3 referencę, s3 becomes "Petras"
    // Step 2: (s3 referencija) = s1 priskyrimo s1 reikšmę s3
    (s3 = s2) = s1;

    EXPECT_EQ(s3.getVardas(), "Vincas");  // s3 final value is Vincas
    EXPECT_EQ(s2.getVardas(), "Petras");  // s2 remains Petras
    EXPECT_EQ(s1.getVardas(), "Vincas");  // s1 remains Vincas
}

// ========== ORIGINAL MAIN (su backward compatibility) ==========
int main(int argc, char** argv) {
    // Google Test inicializacija
    ::testing::InitGoogleTest(&argc, argv);

    // Originalūs testai (v1.5)
    cout << "\n" << string(60, '*') << endl;
    cout << "  STUDENTAS KLASES VISOS METODU TESTAI (v1.5)" << endl;
    cout << "  + GOOGLE TEST PAPILDYMAS (v2.0)" << endl;
    cout << string(60, '*') << endl;

    try {
        test_default_constructor();
        test_parametrized_constructor();
        test_copy_constructor();
        test_copy_assignment();
        test_move_constructor();
        test_move_assignment();
        test_destructor();
        test_output_operator();
        test_input_operator();
        test_io_roundtrip();
        test_modification_after_copy();
        test_getters_setters();
        test_paz_operations();

        cout << "\n" << string(60, '*') << endl;
        cout << "TESTO REZULTATAI:" << endl;
        cout << "Priimti testai: " << testai_praletii << endl;
        cout << "Nepriimti testai: " << testai_nepraletii << endl;
        cout << string(60, '*') << endl;

        if (testai_nepraletii == 0) {
            cout << "\nVISI TESTAI PRIIMTI!" << endl;
        } else {
            cout << "\nKai kurie testai nepraejo!" << endl;
            return 1;
        }
    }
    catch (const std::exception& e) {
        cout << "Kritine klaida: " << e.what() << endl;
        return 1;
    }

    cout << "\n" << string(60, '*') << endl;
    cout << "Vykdomme GOOGLE TEST testai..." << endl;
    cout << string(60, '*') << "\n" << endl;

    // Vykdyti Google Test testus
    return RUN_ALL_TESTS();
}

// ============================================
// VECTOR GTEST TESTAI
// ============================================

class VectorTest : public ::testing::Test {
protected:
    Vector<int> v;
};

// Test 1: Default konstruktorius
TEST_F(VectorTest, DefaultConstructor) {
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
    EXPECT_TRUE(v.empty());
}

// Test 2: Parametrizuotas konstruktorius su size
TEST_F(VectorTest, ConstructorWithCapacity) {
    Vector<int> v2(10);
    EXPECT_EQ(v2.size(), 0);
    EXPECT_EQ(v2.capacity(), 10);
}

// Test 3: Parametrizuotas konstruktorius su size ir value
TEST_F(VectorTest, ConstructorWithSizeAndValue) {
    Vector<int> v2(5, 42);
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2.capacity(), 5);
    EXPECT_EQ(v2[0], 42);
    EXPECT_EQ(v2[4], 42);
}

// Test 4: push_back()
TEST_F(VectorTest, PushBack) {
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

// Test 5: front() ir back()
TEST_F(VectorTest, FrontAndBack) {
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    EXPECT_EQ(v.front(), 10);
    EXPECT_EQ(v.back(), 30);
}

// Test 6: pop_back()
TEST_F(VectorTest, PopBack) {
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back(), 20);
}

// Test 7: at() su bounds checking
TEST_F(VectorTest, AtWithBoundsChecking) {
    v.push_back(10);
    v.push_back(20);
    EXPECT_EQ(v.at(0), 10);
    EXPECT_EQ(v.at(1), 20);
    EXPECT_THROW(v.at(2), std::out_of_range);
}

// Test 8: operator[]
TEST_F(VectorTest, OperatorBrackets) {
    v.push_back(10);
    v.push_back(20);
    v[0] = 100;
    v[1] = 200;
    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v[1], 200);
}

// Test 9: clear()
TEST_F(VectorTest, Clear) {
    v.push_back(10);
    v.push_back(20);
    v.clear();
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.empty());
}

// Test 10: reserve()
TEST_F(VectorTest, Reserve) {
    v.reserve(100);
    EXPECT_GE(v.capacity(), 100);
    EXPECT_EQ(v.size(), 0);
}

// Test 11: shrink_to_fit()
TEST_F(VectorTest, ShrinkToFit) {
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), v.size());
}

// Test 12: resize()
TEST_F(VectorTest, Resize) {
    v.push_back(10);
    v.push_back(20);
    v.resize(5);
    EXPECT_EQ(v.size(), 5);

    v.resize(2);
    EXPECT_EQ(v.size(), 2);
}

// Test 13: resize() su value
TEST_F(VectorTest, ResizeWithValue) {
    v.resize(3, 42);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v[1], 42);
    EXPECT_EQ(v[2], 42);
}

// Test 14: swap()
TEST_F(VectorTest, Swap) {
    Vector<int> v2;
    v.push_back(10);
    v.push_back(20);
    v2.push_back(100);

    v.swap(v2);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], 10);
}

// Test 15: operator== ir operator!=
TEST_F(VectorTest, ComparisonOperators) {
    Vector<int> v2;
    v.push_back(10);
    v.push_back(20);
    v2.push_back(10);
    v2.push_back(20);

    EXPECT_TRUE(v == v2);
    EXPECT_FALSE(v != v2);

    v2.push_back(30);
    EXPECT_FALSE(v == v2);
    EXPECT_TRUE(v != v2);
}

// Test 16: operator< ir operator>
TEST_F(VectorTest, LessGreaterOperators) {
    Vector<int> v2;
    v.push_back(10);
    v.push_back(20);
    v2.push_back(10);
    v2.push_back(30);

    EXPECT_TRUE(v < v2);
    EXPECT_TRUE(v2 > v);
    EXPECT_FALSE(v > v2);
}

// Test 17: begin() ir end() iteratoriai
TEST_F(VectorTest, BeginEndIterators) {
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 60);
}

// Test 18: assign()
TEST_F(VectorTest, Assign) {
    v.assign(5, 42);
    EXPECT_EQ(v.size(), 5);
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], 42);
    }
}

// Test 19: insert()
TEST_F(VectorTest, Insert) {
    v.push_back(10);
    v.push_back(30);
    v.insert(v.begin() + 1, 20);

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

// Test 20: erase()
TEST_F(VectorTest, Erase) {
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    v.erase(v.begin() + 1);

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 30);
}

// Test 21: emplace_back()
TEST_F(VectorTest, EmplaceBack) {
    v.emplace_back(42);
    v.emplace_back(99);

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v[1], 99);
}

// Test 22: Copy konstruktorius
TEST_F(VectorTest, CopyConstructor) {
    v.push_back(10);
    v.push_back(20);

    Vector<int> v2 = v;
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], 10);

    v2[0] = 100;
    EXPECT_EQ(v[0], 10);  // Original nepakeistas
}

// Test 23: Move konstruktorius
TEST_F(VectorTest, MoveConstructor) {
    v.push_back(10);
    v.push_back(20);

    Vector<int> v2 = std::move(v);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v.size(), 0);  // Original tuščias
}

// Test 24: Copy assignment
TEST_F(VectorTest, CopyAssignment) {
    v.push_back(10);
    v.push_back(20);

    Vector<int> v2;
    v2 = v;
    EXPECT_EQ(v2.size(), 2);
    v2[0] = 100;
    EXPECT_EQ(v[0], 10);  // Original nepakeistas
}

// Test 25: Move assignment
TEST_F(VectorTest, MoveAssignment) {
    v.push_back(10);
    v.push_back(20);

    Vector<int> v2;
    v2 = std::move(v);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v.size(), 0);  // Original tuščias
}

// Test 26: max_size()
TEST_F(VectorTest, MaxSize) {
    EXPECT_GT(v.max_size(), 0);
}

// Test 27: data()
TEST_F(VectorTest, Data) {
    v.push_back(10);
    v.push_back(20);

    int* ptr = v.data();
    EXPECT_EQ(ptr[0], 10);
    EXPECT_EQ(ptr[1], 20);
}

