#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Recursive function to calculate the minimum number of scalar multiplications needed
int matrixChainOrder(vector<int>& dims, int i, int j) {
    if (i == j)
        return 0;

    int minCost = INT_MAX;

    // Place parenthesis at different positions, split and recurse
    for (int k = i; k < j; ++k) {
        int cost = matrixChainOrder(dims, i, k) +
                   matrixChainOrder(dims, k + 1, j) +
                   dims[i - 1] * dims[k] * dims[j];
        if (cost < minCost)
            minCost = cost;
    }

    return minCost;
}

int main() {
    vector<int> dims = {10, 30, 5, 60}; // Matrix dimensions: 10x30, 30x5, 5x60
    int minCost = matrixChainOrder(dims, 1, dims.size() - 1);
    cout << "Minimum number of scalar multiplications: " << minCost << endl;
    return 0;
}
