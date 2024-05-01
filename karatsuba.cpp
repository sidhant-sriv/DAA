//Karatsuba algorithm for fast multiplication of large numbers in C++
#include <bits/stdc++.h>
using namespace std;

// Function to multiply two numbers
int karatsuba(int a, int b){
    if(a < 10 || b < 10){
        return a*b;
    }

    int size = log10(max(a,b)) + 1;
    int m = size/2;

    int high1 = a/pow(10, m);
    int low1 = a - high1*pow(10, m);
    int high2 = b/pow(10, m);
    int low2 = b - high2*pow(10, m);

    int z0 = karatsuba(low1, low2);
    int z1 = karatsuba((low1+high1), (low2+high2));
    int z2 = karatsuba(high1, high2);

    return z2*pow(10, 2*m) + (z1-z2-z0)*pow(10, m) + z0;
}


int main(){
    int num1 = 1234;
    int num2 = 455678;
    cout << karatsuba(num1, num2) << endl;
    return 0;
}
