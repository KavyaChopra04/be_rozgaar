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
void dfs(vector<vector<pair<int, int>>> &adj, int node, int parent, vector<int> &dp, vector<pair<int, int>> &parents, int curr_ht)
{
    dp[node] = curr_ht;
    parents[node] = {parent, INT_MAX};
    for(auto x: adj[node])
    {
        if(x.first==parent) {parents[node] = x; continue;};
        dfs(adj, x.first, node, dp, parents, curr_ht + 1);
    }
}

int log2(int n)
{
    int ans = 0;
    while(n)
    {
        ans++;n/=2;
    }
    return ans;
}

pair<int, int>  getParent(int node, int length, vector<vector<pair<int, int>>> &ancestor)
{
    // std::cout<<"getting "<<length<<" parent of node "<<node<<endl;
    int ind = 0;
    int final_node = node;
    int edge_val = INT64_MAX;
    while(length)
    {
        if(length%2)
        {
            edge_val = min(edge_val, ancestor[final_node][ind].second);
            final_node = ancestor[final_node][ind].first;
        }
        length/=2;
        ind++;
    }
    // std::cout<<"getting edge val as "<<edge_val<<" and final node as  "<<final_node<<endl;
    // int ind = 0;
    return {final_node, edge_val};
}

pair<int, int> getLCA(int a, int b, vector<int> &dp, vector<vector<pair<int, int>>> &ancestor)
{
    int edge_val = INT64_MAX;
    if(dp[a] < dp[b])
    {
        auto p = getParent(b, dp[b] - dp[a],  ancestor);
        b = p.first;
        edge_val = min(edge_val, p.second);
    }
    else
    {
        auto p = getParent(a, dp[a]- dp[b], ancestor);
        a = p.first;
        edge_val = min(edge_val, p.second);
    }
    if(a == b)
    {
        return {a, edge_val};
    }
    int max_parent_length = ancestor[0].size() - 1;
    while (max_parent_length > -1)
    {
        if(ancestor[a][max_parent_length].first != ancestor[b][max_parent_length].first)
        {
            edge_val = min(ancestor[b][max_parent_length].second, min(edge_val, ancestor[a][max_parent_length].second));
            a = ancestor[a][max_parent_length].first;
            b = ancestor[b][max_parent_length].first;
        }
        max_parent_length--;
    }
    return {ancestor[a][0].first, min(edge_val, min(ancestor[a][0].second, ancestor[b][0].second))};  
}
void solve()
{
    int n, m;
    cin>>n>>m;
    vector<vector<pair<int,int>>> adj(n+1);
    vector<int> dp(n+1, 0);
    vector<pair<int, int>> parents(n+1, {0,INT64_MAX});
    for(int i=0; i<m; i++)
    {
        int a,b,w;cin>>a>>b>>w;
        adj[a].pb({b, w});adj[b].pb({a, w});
    }
    dfs(adj, 1, 0, dp, parents, 0);
    // for(auto x: parents)
    // {
    //     cout<<x<<", ";
    // }
    // cout<<endl;
    vector<vector<pair<int, int>>> anc(n + 1, vector<pair<int, int>> (log2(n) + 1, {0, INT64_MAX})); 
    for(int i = 1; i <= n; i++)
    {
        anc[i][0] = parents[i];
        // cout<<i<<" "<<0<<" "<<anc[i][0].first<<" "<<anc[i][0].second<<endl;
    }
    for(int i = 1; i <= log2(n); i++)
    {
        for(int j = 1; j <= n; j++)
        {
            anc[j][i].first = anc[anc[j][i-1].first][i-1].first;
            anc[j][i].second = min(anc[j][i-1].second, anc[anc[j][i-1].first][i-1].second);
            // cout<<j<<" "<<i<<" "<<anc[j][i].first<<" "<<anc[j][i].second<<endl;
        }
    }
    int q; cin>>q;
    while(q--)
    {
        int a, b;
        cin>>a>>b;
        pair<int, int> lcanode = getLCA(a, b, dp, anc);
        std::cout<<lcanode.second<<'\n';
    }

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

