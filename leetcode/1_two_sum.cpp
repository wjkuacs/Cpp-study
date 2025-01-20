# include <iostream>
# include <vector>
# include <unordered_map>

class Solution {
public:
    // 声明一个twoSum 函数，接受一个整数数组和目标值，并返回整数数组下标的向量
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // 创建一个哈希表，用于存储数组元素及其下标
        std::unordered_map<int,int> hashMap;

        //遍历数组当中的每一个元素
        for (int i=0;i <nums.size();i++)
        {
            // 计算目标值与当前值的差，即需要的另一半值
            int complement = target - nums[i];

            // 在哈希表当中查找另外一个值
            if (hashMap.find(complement) != hashMap.end())
            {
                // 找到目标值，返回对应的两个下标
                return {hashMap[complement],i};
            }

            // 将当前值及其下标存入哈希表当中
            hashMap[nums[i]] = i;
        }

        // 如果没有找到，则返回一个空向量
        return {};
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {2,7,11,15};    // 初始化一个数组
    int target = 9; // 设置目标值
    std::vector<int> result = solution.twoSum(nums,target); // 调用 twoSum 函数

    // 输出结果
    if (!result.empty())
    {
        std::cout << "Indices:" << result[0] << "," << result[1] <<std::endl;
    }
    else
    {
        std::cout <<"No solution found." <<std::endl;
    }
    system("pause");
    return 0;
}
