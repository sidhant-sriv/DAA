#include <bits/stdc++.h>

using namespace std;

// Function to find the longest common subsequence
string lcs(const string& X, const string& Y) {
    int m = X.size();
    int n = Y.size();

    // Create a 2D array to store the lengths of LCS
    vector<vector<int>> L(m + 1, vector<int>(n + 1));

    // Fill the 2D array in a bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                L[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    // Read the substring out from the 2D array
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs.push_back(X[i - 1]);
            i--;
            j--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Reverse the LCS string
    reverse(lcs.begin(), lcs.end());

    return lcs;
}

int main() {
    string X = "AGGTAB";
    string Y = "GXTXAYB";

    string lcs_str = lcs(X, Y);

    cout << "Longest Common Subsequence: " << lcs_str << endl;

    return 0;
}