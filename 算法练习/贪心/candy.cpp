/*
一群孩子站成一排，每一个孩子有自己的评分。现在需要给这些孩子发糖果，规则是如果一个孩子的评分比自己身旁的一个孩子要高，那么这个孩子就必须得到比身旁孩子更多的糖果；所有孩子至少要有一个糖果。求解最少需要多少个糖果。

接下来我们将会给出一个输入和一个输出
输入：的是一个数组，表示对孩子的评分
输出：最少的糖果数量

Input:[1,0,2]
Output:5

这里我们的策略是：采取两次遍历的策略，首先我们先初始化糖果分配数组为[1,1,1]，然后先从左边向右遍历，如果右边的比左边高，就给右边的更新为左边的糖果数+1，然后再从右向左遍历，如果左边的比右边高，就给左边的更新为右边的糖果数+1，最后返回糖果数组的和即可。
*/

#include <bits/stdc++.h>
#include <vector>


//传入一个数组序列ratings,表示孩子的评分
int candy(std::vector<int>& ratings){
    int size = ratings.size();   //获取我们的小朋友数目，以此确定遍历次数

    //如果只有一个或者两个小朋友，那么直接返回小朋友数目即可
    if(size < 2){
        return size;
    }
    std::vector<int> num(size,1);   //初始化糖果分配数组为[1,1,1]
    //从左向右遍历
    for(int i = 1; i < size; ++i){
        if(ratings[i] > ratings[i - 1]){
            num[i] = num[i - 1] + 1;
        }
    }
    //从右向左遍历
    for(int i = size - 1; i > 0; --i){
        if(ratings[i] < ratings[i - 1]){
            num[i - 1] = std::max(num[i - 1],num[i] + 1);
        }
    }
    return std::accumulate(num.begin(),num.end(),0);    //很方便的求和
}

int main(){
    std::vector<int> ratings = {1};
    std::cout << candy(ratings) << std::endl;
}