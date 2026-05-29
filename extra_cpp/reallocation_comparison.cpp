#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>
#include "../header_files/Vector.h"

using namespace std;
using namespace chrono;

void palygintiRealokacijas() {
    cout << "\n" << string(80, '=') << "\n";
    cout << "std::vector vs custom Vector Reallocation Count Test\n";
    cout << "Test: Push 100,000,000 int elements\n";
    cout << string(80, '=') << "\n\n";

    // Test std::vector reallocation count (manual count)
    cout << "Testing std::vector<int>...\n";
    cout.flush();
    auto start_std = high_resolution_clock::now();
    {
        vector<int> v;
        int realloc_count = 0;
        size_t prev_capacity = 0;

        for (long long i = 1; i <= 100000000; ++i) {
            if (v.capacity() > prev_capacity) {
                realloc_count++;
                prev_capacity = v.capacity();
            }
            v.push_back(i);
        }

        auto end_std = high_resolution_clock::now();
        duration<double> duration_std = end_std - start_std;

        cout << "  Final size:         " << v.size() << "\n";
        cout << "  Final capacity:     " << v.capacity() << "\n";
        cout << "  Reallocation count: " << realloc_count << "\n";
        cout << "  Time:               " << fixed << setprecision(3) << duration_std.count() << " s\n\n";
    }

    // Test custom Vector reallocation count
    cout << "Testing custom Vector<int>...\n";
    cout.flush();
    auto start_vec = high_resolution_clock::now();
    {
        Vector<int> v;

        for (long long i = 1; i <= 100000000; ++i) {
            v.push_back(i);
        }

        auto end_vec = high_resolution_clock::now();
        duration<double> duration_vec = end_vec - start_vec;

        cout << "  Final size:         " << v.size() << "\n";
        cout << "  Final capacity:     " << v.capacity() << "\n";
        cout << "  Reallocation count: " << v.get_reallocation_count() << "\n";
        cout << "  Time:               " << fixed << setprecision(3) << duration_vec.count() << " s\n\n";
    }

    cout << string(80, '=') << "\n";
    cout << "ANALYSIS\n";
    cout << string(80, '=') << "\n";
    cout << "\nBoth containers use the same 2x growth strategy.\n";
    cout << "With 100,000,000 elements:\n";
    cout << "- Expected reallocations: ~27 (log2(100M))\n";
    cout << "- Initial capacity: 1\n";
    cout << "- Final capacity: ~134,217,728 (2^27)\n\n";
}
