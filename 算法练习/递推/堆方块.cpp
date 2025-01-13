#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n,i;
    cin>>n;//n表示层数
    int level=0;//表示每一层的小方块数目
    int sum=0;//表示总的小方块数目
    for(i=1;i<=n;i++)
    {
        level+=i;
        sum+=level;
    }
    cout<<sum<<endl;
    system("pause");
    return 0;
}