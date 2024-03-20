/* Following program is a C++ implementation of Rabin Karp
Algorithm given in the CLRS book */
#include <bits/stdc++.h>
using namespace std;
const int d = 256;
void search(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (i = 0; i <= N - M; i++)
    {

        if (p == t)
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    break;
                }
            }

            if (j == M)
                cout << "Pattern found at index " << i << endl;
        }

        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q; // calculating the hash value of next window

            if (t < 0)
                t = (t + q);
        }
    }
}

/* Driver code */
int main()
{
    char txt[] = "hi my name is sidhant";
    char pat[] = "sid";

    int q = 13;

    search(pat, txt, q);
    return 0;
}

// What is the purpose of h
// Answer: h is used to calculate the hash value of the next window. It is used to remove the leftmost digit and add the rightmost digit to the hash value. It is calculated as (d^(M-1))%q where M is the length of the pattern and d is the number of characters in the input alphabet. It is used to calculate the hash value of the next window in O(1) time.