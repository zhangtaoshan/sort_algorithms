#include <vector>
#include <iostream>
#include <sys/time.h>
#include <queue>
#include <iomanip>

using std::string;
using std::vector;


class MySort 
{
public:
    // 数组长度
    int n = -1;

public:
    // 构造函数
    MySort(int _n) : n(_n) {};

    // 打印vector
    static void printVec(vector<int> v, string name = "");

    // 选择排序，每次从待排序列中选择最小的值
    vector<int> selectSort(vector<int> nums);

    // 堆排序，调用优先队列
    vector<int> heapSort(vector<int> nums);

    // 冒泡排序，每次两两比较后将最大数值放到后面的有序序列中
    vector<int> bubbleSort(vector<int> nums);

    // 快速排序，每次选定第一个元素为基准后使用前后双指针比较和基准元素的大小
    vector<int> quickSort(vector<int> nums);

    // 直接插入排序，每次在待排序列中选择最小的元素
    vector<int> insertSort(vector<int> nums);
};


// 打印vector
static void printVec(vector<int> v, string name = "")
{
    std::cout << std::setw(11) << name << ": ";
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}


// 选择排序
vector<int> MySort::selectSort(vector<int> nums)
{
    // 存放结果
    vector<int> ans(nums);

    for (int i = 0; i < n - 1; ++i)
    {
        // 假设当前元素为待排序列的最小值
        int k = i;
        for (int j = i + 1; j < n; ++j)
        {
            // 如果存在更小元素
            if (ans[j] < ans[k])
            {
                // 更新索引
                k = j;
            }
        }
        // 交换
        std::swap(ans[i], ans[k]);
    }

    // 返回结果
    return ans;
}


// 堆排序
vector<int> MySort::heapSort(vector<int> nums)
{
    // 存放结果
    vector<int> ans;

    // 定义小顶堆
    std::priority_queue<int, vector<int>, std::greater<int>> q;

    // 压入堆中
    for (int i = 0; i < n; ++i)
    {
        q.push(nums[i]);
    }
    
    // 弹出堆中元素
    while (!q.empty())
    {
        ans.push_back(q.top());
        q.pop();
    }

    // 返回结果
    return ans;
}


// 冒泡排序
vector<int> MySort::bubbleSort(vector<int> nums)
{
    // 存放结果
    vector<int> ans(nums);

    for (int i = n - 1; i > 0; --i)
    {
        // 如果一趟排序中序列没有发生变化，则返回false
        int flag = false;

        for (int j = 0; j < i; ++j)
        {
            if (ans[j] > ans[j + 1])
            {
                std::swap(ans[j], ans[j + 1]);
                flag = true;
            }
        }
        // 提前返回
        if (flag == false)
        {
            break;
        }
    }

    // 返回结果
    return ans;
}


// 快速排序
static void helper(vector<int>& nums, int l, int r)
{
    if (l < r)
    {
        // 双指针
        int i = l, j = r;

        // 选取第一个元素为基准
        int landmark = nums[l];

        while (i < j)
        {
            // 不断移动右指针
            while (i < j && nums[j] > landmark)
            {
                --j;
            }

            // 移动一步左指针
            if (i < j)
            {
                nums[i] = nums[j];
                ++i;
            }

            // 不断移动左指针
            while (i < j && nums[i] < landmark)
            {
                ++i;
            }

            // 移动一步右指针
            if (i < j)
            {
                nums[j] = nums[i];
                --j;
            }
        }
        // 基准元素归位
        nums[i] = landmark;
        
        // 递归调用
        helper(nums, l, i - 1);
        helper(nums, i + 1, r);
    }
}
vector<int> MySort::quickSort(vector<int> nums)
{
    // 存放结果
    vector<int> ans(nums);

    // 调用辅助函数，使用左闭右开区间
    helper(ans, 0, n - 1);

    // 返回结果
    return ans;
}


// 直接插入排序
vector<int> MySort::insertSort(vector<int> nums)
{
    // 存放结果
    vector<int> ans(nums);

    for (int i = 1; i < n; ++i)
    {
        // 暂存当前元素
        int temp = ans[i];

        // 向前遍历，找到temp的插入位置
        int j = i - 1;
        while (j >= 0 && temp < ans[j])
        {
            // 不断向后移动元素
            ans[j + 1] = ans[j];
            --j;
        }

        // temp应插入位置j处
        ans[j + 1] = temp;
    }

    // 返回结果
    return ans;
}

int main(int argc, char** argv)
{
    // 输入数组
    vector<int> input = { 2, 7, 1, 5, 9, 8, 6 };

    // 初始化
    MySort mySort(input.size());

    // 选择排序
    vector<int> ans_select_sort = mySort.selectSort(input);
    printVec(ans_select_sort, "选择排序");

    // 堆排序
    vector<int> ans_heap_sort = mySort.heapSort(input);
    printVec(ans_heap_sort, "堆排序");

    // 冒泡排序
    vector<int> ans_bubble_sort = mySort.bubbleSort(input);
    printVec(ans_bubble_sort, "冒泡排序");

    // 快速排序
    vector<int> ans_quick_sort = mySort.quickSort(input);
    printVec(ans_quick_sort, "快速排序");

    // 直接插入排序
    vector<int> ans_insert_sort = mySort.insertSort(input);
    printVec(ans_insert_sort, "插入排序");

    return 0;
}
