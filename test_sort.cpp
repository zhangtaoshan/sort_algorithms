#include <vector>
#include <iostream>
#include <sys/time.h>
#include <queue>
#include <iomanip>
#include <algorithm>

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
    static void printVec(const vector<int> v, string name = "");

    // 选择排序，每次从待排序列中选择最小的值
    vector<int> selectSort(const vector<int> nums);

    // 堆排序，调用优先队列
    vector<int> heapSort(const vector<int> nums);

    // 冒泡排序，每次两两比较后将最大数值放到后面的有序序列中
    vector<int> bubbleSort(const vector<int> nums);

    // 快速排序，每次选定第一个元素为基准后使用前后双指针比较和基准元素的大小
    vector<int> quickSort(const vector<int> nums);

    // 直接插入排序，每次在待排序列中选择最小的元素
    vector<int> insertSort(const vector<int> nums);

    // 希尔排序，定义一个增量并逐渐缩小
    vector<int> shellSort(const vector<int> nums);

    // 归并排序，两两归并后逐渐增大区间
    vector<int> mergeSort(const vector<int> nums);

    // 计数排序，统计比当前元素小的元素个数，最好理解的时间复杂度为O(n^2)，空间复杂度为O(n)
    vector<int> countSort1(const vector<int> nums);

    // 计数排序，时间复杂度为O(n)，空间复杂度为O(n)
    vector<int> countSort2(const vector<int> nums);
};


// 打印vector
static void printVec(const vector<int> v, string name = "")
{
    std::cout << std::setw(11) << name << ": ";
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}


// 选择排序
vector<int> MySort::selectSort(const vector<int> nums)
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
vector<int> MySort::heapSort(const vector<int> nums)
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
vector<int> MySort::bubbleSort(const vector<int> nums)
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
static void helperQuickSort(vector<int>& nums, int l, int r)
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
        helperQuickSort(nums, l, i - 1);
        helperQuickSort(nums, i + 1, r);
    }
}

vector<int> MySort::quickSort(const vector<int> nums)
{
    // 存放结果
    vector<int> ans(nums);

    // 调用辅助函数，使用左闭右开区间
    helperQuickSort(ans, 0, n - 1);

    // 返回结果
    return ans;
}


// 直接插入排序
vector<int> MySort::insertSort(const vector<int> nums)
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


// 希尔排序
vector<int> MySort::shellSort(const vector<int> nums)
{
    // 存放结果
    vector<int> ans(nums);

    // 假设初始增量为5，每次衰减2
    for (int delta = 5; delta > 0; delta -= 2)
    {
        // 遍历一个增量的大小
        for (int i = 0; i < delta; ++i)
        {
            // 根据增量大小选取数组元素
            for (int j = i + delta; j < n; ++j)
            {
                // 对子序列使用直接插入排序，暂存当前元素
                int temp = ans[j];

                // 前一个元素的索引
                int k = j - delta;

                // 向前遍历找到插入位置
                while (k >= 0 && temp < ans[k])
                {
                    // 向后移动赋值
                    ans[k + delta] = ans[k];

                    // 索引移动
                    k -= delta;
                }

                // 将temp放到k+delta位置处
                ans[k + delta] = temp;
            }
        }
    }

    // 返回结果
    return ans;
}


// 归并排序
void dfsMergeSort(vector<int>& nums, int l, int m, int r)
{
    // 归并好[l,m]和[m+1,r]区间内的元素到一个数组中
    vector<int> t(r - l + 1);

    // 指针
    int i = l, j = m + 1, k = 0;

    // 循环
    while (i <= m && j <= r)
    {
        if (nums[i] < nums[j])
        {
            t[k++] = nums[i++];
        }
        else 
        {
            t[k++] = nums[j++];
        }
    }

    // 如果其中一个区间不为空
    while (i <= m)
    {
        t[k++] = nums[i++];
    }
    while (j <= r)
    {
        t[k++] = nums[j++];
    }

    // 赋值给输入数组
    for (int i = 0; i < r - l + 1; ++i)
    {
        nums[l + i] = t[i];
    }

    // t清空
    t.clear();
}

void helperMergeSort(vector<int>& nums, int l, int r)
{
    // 递归出口
    if (l >= r)
    {
        return;
    }

    // 取中间索引
    int m = l + (r - l) / 2;

    // 递归地归并左半区间和右半区间
    helperMergeSort(nums, l, m);
    helperMergeSort(nums, m + 1, r);

    // 后序遍历调用递归函数
    dfsMergeSort(nums, l, m, r);
}

vector<int> MySort::mergeSort(const vector<int> nums)
{
    // 存放结果
    vector<int> ans(nums);

    // 递归调用
    helperMergeSort(ans, 0, n - 1);

    // 返回结果
    return ans;
}


// 计数排序
vector<int> MySort::countSort1(const vector<int> nums)
{
    // 存放结果
    vector<int> ans(nums);

    // 将所有元素填充为-1方便后面去重
    std::fill(ans.begin(), ans.end(), -1);

    // 计数变量
    int count = 0;

    for (int i = 0; i < n; ++i)
    {
        // 重新计数
        count = 0;

        // 寻找比nums[i]小的元素个数
        for (int j = 0; j < n; ++j)
        {
            if (nums[j] < nums[i])
            {
                ++count;
            }
        }

        // 去重
        while (ans[count] != -1)
        {
            ++count;
        }

        // 根据count值将nums[j]放到count处
        ans[count] = nums[i];
    }

    // 返回结果
    return ans;
}


// 计数排序
vector<int> MySort::countSort2(const vector<int> nums)
{
    // 存放结果
    vector<int> ans(nums);

    // 计算数组的最大值和最小值
    int max_value = *max_element(ans.begin(), ans.end());
    int min_value = *min_element(ans.begin(), ans.end());

    // 偏移，如果原数组中不存在负数，则偏移为0
    int offset = 0;

    // 如果最小值小于零，则需要计算偏移，如-1应该放在位置0处
    if (min_value < 0)
    {
        offset = 0 - min_value;
    }

    // 计数数组
    vector<int> count(max_value + offset + 1, 0);

    // 统计个数的时候加上偏移
    for (int i = 0; i < n; ++i)
    {
        ++count[ans[i] + offset];
    }    

    // 结果索引
    int index = 0;

    // 根据计数数组还原数组
    for (int i = 0; i < max_value + offset + 1; ++i)
    {
        while (count[i] > 0)
        {
            // 还原数组时需要偏移
            ans[index++] = i - offset;

            // 当前计数减1，如果有重复元素，则会进行下一次循环
            --count[i];
        }
        
    }
    
    // 返回结果
    return ans;
}


int main(int argc, char** argv)
{
    // 输入数组
    vector<int> input = { 2, 7, -1, 5, 9, 8, 6, 8, -3 };

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

    // 希尔排序
    vector<int> ans_shell_sort = mySort.shellSort(input);
    printVec(ans_shell_sort, "希尔排序");

    // 归并排序
    vector<int> ans_merge_sort = mySort.mergeSort(input);
    printVec(ans_merge_sort, "归并排序");

    // 计数排序
    vector<int> ans_count_sort1 = mySort.countSort1(input);
    printVec(ans_count_sort1, "计数排序");

    // 计数排序
    vector<int> ans_count_sort2 = mySort.countSort2(input);
    printVec(ans_count_sort2, "计数排序");

    return 0;
}
