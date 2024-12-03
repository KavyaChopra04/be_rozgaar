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

bool isSpruce(vector<vector<int>> &children, int node, int parent)
{
    if(children[node].empty()) return true;
    int num_leaf_children = 0;
    bool isSpruceSubtree = true;
    for(auto neighbour: children[node])
    {
        if(neighbour == parent) continue;
        if(children[neighbour].empty())
        {
            num_leaf_children++;
        }
        else
        {   
            isSpruceSubtree &= isSpruce(children, neighbour, node);
        }
    }
    isSpruceSubtree &= (num_leaf_children >= 3);
    return isSpruceSubtree;
}
void solve()
{
    int n;
    cin>>n;
    vector<vector<int>> children(n+1);
    for(int i=0; i< n- 1; i++)
    {
        int x;cin>>x;
        children[x].push_back(i+2);
    }
    if(isSpruce(children, 1, -1))
    {
        cout<<"Yes";
    }
    else
    {
        cout<<"No";
    }
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

