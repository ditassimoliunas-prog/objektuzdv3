cmake_minimum_required(VERSION 3.10)

# Projekto pavadinimas
project(ObjektinisUzdavinys)

# Nustatome C++ versiją
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Nustatome perspėjimus pagal naudojamą kompiliatorių
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")
endif()

# Nurodome kur ieškoti header failų (.h)
include_directories(header_files)

# Visi išeitiniai (source) .cpp failai išskyrus patį main
set(SOURCES 
    objekt1uzd.cpp 
    extra_cpp/duomenu_valdymas.cpp 
    extra_cpp/input.cpp 
    extra_cpp/mat_funkcijos.cpp 
    extra_cpp/menu.cpp 
    extra_cpp/output.cpp 
    extra_cpp/testavimas.cpp
    extra_cpp/Zmogus.cpp
    extra_cpp/Studentas.cpp
)

# Sukuriame programa.exe (nuolatinis executable - nechange)
add_executable(programa ${SOURCES})

# ===== GOOGLE TEST FRAMEWORK =====
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# Nustatyti Google Test runtime library (jungtis su MDd/MD)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(CMAKE_POLICY_DEFAULT_CMP0091 NEW)
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Release>:>")
endif()

FetchContent_MakeAvailable(googletest)

# ===== TESTŲ PROGRAMA SU GOOGLE TEST =====
enable_testing()

add_executable(test_programa
    test_studentas.cpp
    extra_cpp/Zmogus.cpp
    extra_cpp/Studentas.cpp
    extra_cpp/mat_funkcijos.cpp
)

target_link_libraries(test_programa gtest gtest_main)

# Registruoti testus CTest'e
add_test(NAME StudentasTests COMMAND test_programa)
