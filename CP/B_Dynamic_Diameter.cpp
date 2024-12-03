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
void dfs(vector<vector<int>> &adj, int node, int parent, vector<int> &dp, int curr_ht)
{
    dp[node] = curr_ht;
    for(auto x: adj[node])
    {
        if(x==parent) continue;
        dfs(adj, x, node, dp, curr_ht + 1);
    }
}
void solve()
{
    int n;
    cin>>n;
    vector<vector<int>> adj(n+1);
    vector<int> dp(n+1, 0);
    for(int i=0; i<n-1; i++)
    {
        int a,b;cin>>a>>b;
        adj[a].pb(b);adj[b].pb(a);
    }
    dfs(adj, 1, -1, dp, 0);
    int max_ht = -1;
    int first_end = 0;
    for(int i = 1; i<=n; i++)
    {
        if(dp[i] > max_ht)
        {
            first_end = i;
            max_ht = dp[i];
        } 
    }
    vector<int> dpa(n+1, 0);
    dfs(adj, first_end, -1, dpa, 0);
    // for(auto x: dpa)
    // {
    //     cout<<x<<", ";
    // }
    // cout<<endl;
    int second_end = std::max_element(dpa.begin(), dpa.end()) - dpa.begin();
    // P(first_end);P(second_end);
    vector<int> dpb(n+1, 0);
    dfs(adj, second_end, -1, dpb, 0);
    int diameter = dpa[second_end];
    for(int i = 1; i<=n;i++)
    {
        if(dpa[i]== diameter || dpb[i] == diameter)
        {
            cout<<diameter+1<<'\n';
        }
        else
        {
            cout<<diameter<<'\n';
        }
    }
    // cout<<max_ht<<'\n';
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
    while(t--)
    {
        solve();
    }
} 

