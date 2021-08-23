#include <vector>
#include <map>

using namespace std;

namespace array_algorithm {

    /// <summary>
    ///     https://leetcode-cn.com/problems/two-sum/
    /// </summary>
    /// <param name="nums"></param>
    /// <param name="target"></param>
    /// <returns></returns>
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result(2, -1);
        map<int, int> numsMap;

        for (int i = 0; i < nums.size(); i++)
        {
            int other = target - nums[i];
            if (numsMap.count(other) > 0)
            {
                result[0] = numsMap[other];
                result[1] = i;
                break;
            }
            numsMap[nums[i]] = i;
        }
        return result;
    }

}