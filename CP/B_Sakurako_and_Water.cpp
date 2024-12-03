#include <bits/stdc++.h>
// #include <optional>
#include <ext/pb_ds/assoc_container.hpp>
#define int long long
#define P(EX) cout << #EX << ": " << EX << endl; 
#define pb push_back
#define vi std::vector<int> v
#define mp make_pair
const int mod=998244353;
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
   int n;cin>>n;
   int ans = 0;
//    cout<<"new\n";
   vector<vector<int>> v(n, vector<int>(n, 0));
   for(int i=0;i<n;i++)
   {
    for(int j=0;j<n;j++)
    {
        cin>>v[i][j];
    }
   }
   for(int i = 0; i< n; i++)
   {
    int la = 0;
    int diff = i;
    for(int j = i; j < n; j++)
    {
        if(v[j][j-diff] < 0)
        {
            la = max(la, abs(v[j][j-diff]));
        }
    }
    // P(i); P(la);
    ans+=la;
   }
//    cout<<ans<<": "<<'\n';
   for(int j = 0; j< n; j++)
   {
    int la = 0;
    int diff = j;
    for(int i = j; i < n; i++)
    {
        if(v[i-diff][i] < 0)
        {
            la = max(la, abs(v[i-diff][i]));
        }
    }
    // P(j); P(la);
    ans+=la;
   }
//    cout<<ans<<": "<<'\n';
   int la = 0;
   for(int i=0;i<n;i++)
   {
    if(v[i][i] < 0)
    {
        la = max(la, abs(v[i][i]));
    }
   }
   ans -= la;
   cout<<ans<<'\n';
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

