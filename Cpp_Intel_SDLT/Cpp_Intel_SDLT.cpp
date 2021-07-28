// Cpp_Intel_SDLT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// #include <iostream>
#include <stdio.h>
#include <sdlt/sdlt.h>
#include <immintrin.h>

// clock
#include <chrono>
#include <iomanip>

#define N 1024

typedef struct RGBs {
    float r;
    float g;
    float b;
} RGBTy;

SDLT_PRIMITIVE(RGBTy, r, g, b)


int main()
{
    std::chrono::steady_clock::time_point start, end;
    double time_taken;
    
    // Use SDLT to get SOA data layout
    sdlt::soa1d_container<RGBTy> aContainer(N);
    auto a = aContainer.access();

    start = std::chrono::high_resolution_clock::now();
    // use SDLT Data Member Interface to access struct members r, g, and b.
    // achieve unit-stride access after vectorization
    #pragma omp simd
    for (int k = 0; k<N; k++) {
        a[k].r() = k*1.5;
        a[k].g() = k*2.5;
        a[k].b() = k*3.5;
    }

    end = std::chrono::high_resolution_clock::now();
    // std::cout << "c: " << c[0] << " " << c[N - 1] << " \n";

    // Calculating total time taken by the loop. 
    time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 5;
    time_taken *= 1e-9;

    std::cout << "Time taken by loop is : " << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;


    std::cout << "k =" << 10 <<
        ", a[k].r =" << a[10].r() <<
        ", a[k].g =" << a[10].g() <<
        ", a[k].b =" << a[10].b() << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
