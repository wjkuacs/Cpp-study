/*
题干：Assign Cookies
有一群孩子和一堆饼干，每个孩子有一个饥饿度，每个饼干都有一个大小。每个孩子只能吃
最多一个饼干，且只有饼干的大小大于孩子的饥饿度时，这个孩子才能吃饱。求解最多有多少孩
子可以吃饱。

接下来将会
输入两个数组：一个代表孩子的饥饿度，一个代表饼干的大小。
输出一个数组：代表最多有多少个孩子可以吃饱的数量。
Input:[1,2], [1,2,3]
Output:2
*/

//这个样例中，给到的两个输入是指可以给两个孩子喂[1,2],[1,3],[2,3]这三种组合的任意一种。

/*
这里的贪心策略是给剩余的孩子里饥饿度最小的分配最小的能饱腹的饼干。

我们需要对小孩子饥饿度和饼干大小进行排序（从小到大）
*/
/*
#include <bits/stdc++.h>
#include <vector>

int findContentChildren(std::vector<int>& children,std::vector<int>& cookies){
    sort(children.begin(),children.end());
    sort(cookies.begin(),cookies.end());
    int child = 0,cookie = 0;
    while(child < children.size() && cookie <cookies.size()){
        if(children[child] <= cookies[cookie]){
            ++child;
        }
        ++cookie;
    }
    return child;
}

int main(){
    std::vector<int> children = {1,2};
    std::vector<int> cookies = {1,2,3};
    std::cout << findContentChildren(children,cookies) << std::endl;
}
*/

#include <bits/stdc++.h>
#include <vector>

class CookieAssigner {
private:
    std::vector<int> children_;
    std::vector<int> cookies_;

public:
    CookieAssigner(const std::vector<int>& children, const std::vector<int>& cookies)
        : children_(children), cookies_(cookies) {}
        /*
            这一步是为了初始化成员变量并将参数传递给成员变量，普通写法是
            {
                children_ = children;
                cookies_ = cookies;
            }
        */
    int calculateMaxChildren() {
        std::sort(children_.begin(), children_.end());
        std::sort(cookies_.begin(), cookies_.end());
        
        int child = 0, cookie = 0;
        while(child < children_.size() && cookie < cookies_.size()) {
            if(children_[child] <= cookies_[cookie]) {
                ++child;
            }
            ++cookie;
        }
        return child;
    }
};

int main() {
    std::vector<int> children = {1, 2};
    std::vector<int> cookies = {1, 2, 3};
    
    CookieAssigner assigner(children, cookies);
    std::cout << assigner.calculateMaxChildren() << std::endl;
    
    return 0;
}