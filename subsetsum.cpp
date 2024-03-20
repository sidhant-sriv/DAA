#include <iostream>
#include <vector>

using namespace std;

bool hasSubsetSum(const vector<int> &nums, int target, int index, vector<int> &current)
{
    // Base case: If target is 0, we found a subset that sums to target
    if (target == 0)
    {
        cout << "Subset found: ";
        for (int num : current)
        {
            cout << num << " ";
        }
        cout << endl;
        return true;
    }

    // If we reach the end or the target becomes negative, no solution exists
    if (index >= nums.size() || target < 0)
    {
        return false;
    }

    // Try including the current element
    current.push_back(nums[index]);
    bool included = hasSubsetSum(nums, target - nums[index], index + 1, current);

    // Backtrack: If including the element didn't lead to a solution, try excluding it
    current.pop_back();
    bool excluded = hasSubsetSum(nums, target, index + 1, current);

    // Return true if either including or excluding the element leads to a solution
    return included || excluded;
}

int main()
{
    vector<int> nums = {3, 2, 7, 1};
    int target = 6;
    vector<int> current;

    if (hasSubsetSum(nums, target, 0, current))
    {
        cout << "Subset with sum " << target << " exists." << endl;
    }
    else
    {
        cout << "No subset with sum " << target << " exists." << endl;
    }

    return 0;
}
