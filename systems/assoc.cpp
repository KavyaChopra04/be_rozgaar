#include <iostream>
#pragma pack(1)
// #define int long long
#define f(a,b) a + b
inline int fun(int* ptr)
{
    *ptr = 5;
    return 0;
}
signed main()
{
    int x = 11;
    // int* y = &x;
    // int z = 12  + x + fun(y);

    int arr[4] = {1,2,3,4};
    int* p  = &x;
    std::cout<<sizeof(p)<<std::endl;
    int* q = &x;
    // f("bac",3);
    std::cout<<p<<std::endl;
    std::cout<<p[0]<<std::endl;
    std::cout<<p[1]<<std::endl;
    std::cout<<p[2]<<std::endl;
    std::cout<<p[3]<<std::endl;
    std::cout<<p[4]<<std::endl;
    std::cout<<p[5]<<std::endl;
}