#include <bits/stdc++.h>
// #include <optional>
#include <ext/pb_ds/assoc_container.hpp>
#define int long long
#define P(EX) cout << #EX << ": " << EX << endl; 
#define pb push_back
#define vi std::vector<int> v
#define mp make_pair
const int mod=1000000007;
const int inf = 1000000000000000000;
using namespace std;
vector<int> cost(1001);
vector<int> largestFactor(10000001, 1);
int binexp(int a, int b)
{
    int res=1;
    while(b>0)
    {
        if(b&1)
        {
            res=(res*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}
void sieve()
{
	for(int i=1;i<=10000000;i++)
	{
		largestFactor[i]=i;
	}
	for(int i=2;i<=10000000;i++)
	{
		if(largestFactor[i]==i)
		{
			for(int j=i;j<=10000000;j+=i)
			{
				largestFactor[j]=i;
			}
		}
	}
}
int nCr(int n, int r)
{   
    int ans = 1;
    for(int i = r + 1; i <= n; i++)
    {
        ans = (ans * i);
        ans /= (i-r);
    }
    return ans;
}
// vector<vector<int>> nCr;
int nCrmod(int n, int r)
{
    int ans = 1;
    for(int i = r + 1; i <= n; i++)
    {
        ans = (ans * i) % mod;
        ans = (ans * binexp(i-r, mod - 2))%mod;
    }
    return ans%mod;
}
void solve()
{
   int n,k;cin>>n>>k;
   int ind = 2;
   int f0=0, f1=1, f2=1;
//    int it = 100;
   while(true)
   {
    int old_f2 = f2;
    f2 = (f2 + f1)%k;
    f1 = (old_f2)%k;
    f0 = (f1)%k;
    // P(f2); P(f1);
    ind++;
    if(f2 == 0)
    {
        break;
    }
   }
   if(1%k==0)
   {
    ind = 1;
   }
   n = n%mod;
   cout<<(ind*n)%mod<<'\n';
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
    cin>>t;
    // A[0]=1;
    // A[1] = 1;
    // B[1] = 1;
    // for(int i=2;i<=1000000;i++)
    // {    
    //     A[i] = (2*A[i-1] + B[i-1])%mod;
    //     B[i] = (4*B[i-1] + A[i-1])%mod;
    // }
    while(t--)
    {
        solve();
    }
} 

