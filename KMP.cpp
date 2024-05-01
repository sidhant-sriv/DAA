#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to build the lps (longest proper prefix which is also a suffix) array
void buildLPS(const string& pattern, vector<int>& lps) {
    int patternLen = pattern.size();
    int len = 0;

    lps[0] = 0;
    int i = 1;

    while (i < patternLen) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to perform the KMP string matching
void kmpSearch(const string& text, const string& pattern) {
    int textLen = text.size();
    int patternLen = pattern.size();

    vector<int> lps(patternLen, 0);
    buildLPS(pattern, lps);

    int i = 0;
    int j = 0;

    while (i < textLen) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == patternLen) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < textLen && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABAB";
    kmpSearch(text, pattern);
    return 0;
}