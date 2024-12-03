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
    int n,m;
    cin>>n>>m;
    vector<int> v(m+ 1,0);
    for(int i = 0; i<= m;i+= 2)
    {  
        v[i] = (nCrmod(m, m/2-i/2) * (i + 1))%mod;
        v[i] = (v[i] * binexp((i/2) + m/2 + 1, mod - 2))%mod;
    }
    if(n==1)
    {
        cout<<v[0]<<'\n';
        return;
    }
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    // dp[2] = v;
    for(int i=0;i<=m;i+=2)
    {
        dp[2][i] = (v[i])%mod;
    }
    // for(auto x: v)
    // {
    //     cout<<x<<", ";
    // }
    // cout<<endl;
    
    for(int i = 3; i <= n; i++)
    {
        for(int j = 0; j <= m; j+=2)
        {
            dp[i][j] = 0;
            for(int k = 0; k <= j; k += 2)
            {
                dp[i][j] = (dp[i][j] + (1*((dp[i-1][j-k]*v[k])%mod)%mod))%mod;
            }
        }
    }
    // if(n>=3){
    // for(auto x: dp[3])
    // {
    //     cout<<x<<", ";
    // }
    // }
    // cout<<endl;
    int finans = 0;
    for(int i = 0; i <= m; i+=2)
    {
        finans = (finans + (dp[n][i] *v[i])%mod)%mod;
    }
    cout<<finans<<'\n';

}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
    // cin>>t;
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

