// #include <iostream>
// using namespace std;

// // Driver Code
// int main()
// {
//     int x{ 10 };
//     char y{ 'M' };

//     const int* i = &x;
//     const char* j = &y;

//     // Value of x and y can be altered,
//     // they are not constant variables
//     x = 9;
//     y = 'A';

//     // Change of constant values because,
//     // i and j are pointing to const-int
//     // & const-char type value
//     x = 12;
// int kc = 8;
//     cout << *i << " " << *j;
//     i = &kc;
//     cout << *i << " " << *j;

// }


// C++ program to demonstrate the
// above concept
// #include <iostream>
// using namespace std;

// // Driver Code
// int main()
// {
//     // x and z non-const var
//     int x = 5;
//     int z = 6;

//     // y and p non-const var
//     char y = 'A';
//     char p = 'C';

//     // const pointer(i) pointing
//     // to the var x's location
//     int* const i = &x;

//     // const pointer(j) pointing
//     // to the var y's location
//     char* const j = &y;

//     // The values that is stored at the memory location can
//     // modified even if we modify it through the pointer
//     // itself No CTE error
//     *i = 10;
//     *j = 'D';

//     // CTE because pointer variable
//     // is const type so the address
//     // pointed by the pointer variables
//     // can't be changed
//     // i = &z;
//     // j = &p;

//     cout << *i << " and " << *j << endl;
//     x = 12;
//     cout << *i << " and " << j;

//     return 0;
// }

// #include <iostream>
// using namespace std;
// const int foo() {const int y = 5; cout<<&y<<endl; return y;}
// int main()
// {
//     int y = foo();
//     cout<<&y<<endl;
//     y= 7;
//     cout<<y<<endl;
// }

// #include <bits/stdc++.h>
// using namespace std;
 
// // A Functor
// class increment
// {
// private:
//     int num;
// public:
//     increment(int n) : num(n) {  }
 
//     // This operator overloading enables calling
//     // operator function () on objects of increment
//     // int operator () (int arr_num) const {
//     //     return num + arr_num;
//     // }
// };

// class compare{
//     public:
//         bool operator() (int a, int b)
//         {
//             return b  >a;
//         }
// };
 
// // Driver code
// int main()
// {
//    vector<int> arr = {5,4,6,7};
//    sort(arr.begin(), arr.end(), greater<int>());
//    for(auto x: arr)
//    {
//         cout<<x<<", ";
//    }
//    cout<<endl;

// }


// #include <iostream>
// #include <vector>
// using namespace std;

// // Class Test
// class Test {
    

// public:
//     // Constructor
//     Test(int v = 0) { value = v; }
    
//     // We get compiler error if we
//     // add a line like "value = 100;"
//     // in this function.
//     int getValue() const {return value;  }

//     // a nonconst function trying to modify value
//     void setValue(int val) { value = val; }
//     int value;
// };

// // Driver Code
// int main()
// {
//     // Object of the class T
//     // Test t(20);

//     // // non-const object invoking const function, no error
//     // cout<<&t<<endl;
//     // cout << t.getValue() << endl;

//     // // const object
//     const Test t_const(10);
//     cout<<&t_const<<endl;
//     // const object invoking const function, no error
//     cout << t_const.getValue() << endl;

//     // // const object invoking non-const function, CTE
//     // t_const.setValue(15);

//     // // // non-const object invoking non-const function, no
//     // // // error
//     // // t.setValue(12);

//     // // cout << t.getValue() << endl;
//     // const vector<int> v = {1,2,3};
//     // v[0] = 4;
//     // v.push_back(4);

//     return 0;
// }

#include <iostream>
using namespace std;

const int foo(int& y)
{
    y--;
    return y;
}

int main()
{
    int x = 9;
    const int z = 10;
    cout << foo(x) << '\n' << foo(z);

    return 0;
}