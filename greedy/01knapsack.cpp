#include <bits/stdc++.h>
using namespace std;

int knapsack(vector<int> &weight, vector<int> &cost, int capacity)
{
    int n = weight.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= capacity; ++j)
        {
            if (weight[i - 1] > j)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(cost[i - 1] + dp[i - 1][j - weight[i - 1]], dp[i - 1][j]);
            }
        }
    }

    return dp[n][capacity];
}

int main()
{
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {10, 7, 14, 8};
    int capacity = 7;

    int max_value = knapsack(weights, values, capacity);
    cout << "Maximum value that can be obtained: " << max_value << endl;

    return 0;
}