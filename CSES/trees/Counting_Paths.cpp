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
void dfs(vector<vector<int>> &adj, int node, int parent, vector<int> &dp, vector<int> &parents, int curr_ht)
{
    dp[node] = curr_ht;
    parents[node] = parent;
    for(auto x: adj[node])
    {
        if(x==parent) continue;
        dfs(adj, x, node, dp, parents, curr_ht + 1);
    }
}
void reroot(vector<vector<int>> &adj, vector<int> &answer, vector<int> &subtreesum, int parent, int node, int totsum)
{
    if(parent != -1)
    answer[node] = answer[parent] - subtreesum[node] + totsum - subtreesum[node];
    for(auto x: adj[node])
    {
        if(x == parent) continue;
        reroot(adj, answer, subtreesum, node, x, totsum);
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
int getParent(int node, int length, vector<vector<int>> &ancestor)
{
    int ind = 0;
    int final_node = node;
    while(length)
    {
        if(length%2)
        {
            final_node = ancestor[final_node][ind];
        }
        length/=2;
        ind++;
    }
    return final_node;
}

tuple<int, int, int> getLCA(int a, int b, vector<int> &dp, vector<vector<int>> &ancestor)
{
    int k;
    if(dp[a] < dp[b])
    {
        int temp_b = b;
        b = getParent(temp_b, dp[temp_b] - dp[a],  ancestor);
        k = getParent(temp_b, dp[temp_b] - dp[a] - 1,  ancestor);
    }
    else
    {
        int temp_a = a;
        a = getParent(temp_a, dp[temp_a]- dp[b], ancestor);
        k = getParent(temp_a, dp[temp_a] - dp[b] - 1,  ancestor);
    }
    if(a == b)
    {
        P("here");
        return {a, k, a};
    }
    int max_parent_length = ancestor[0].size() - 1;
    while (max_parent_length > -1)
    {
        if(ancestor[a][max_parent_length] != ancestor[b][max_parent_length])
        {
            a = ancestor[a][max_parent_length];
            b = ancestor[b][max_parent_length];
        }
        max_parent_length--;
    }
    return {a, b, ancestor[a][0]};  
}

void fillans(vector<vector<int>> &adj, int node, int parent, vector<int> &answer, vector<int> &childrensub, vector<int> &pref)
{
    P(node) P(parent) 
    P(answer[parent]);
    P(pref[node]) P(childrensub[parent])
    answer[node] = answer[parent] + childrensub[parent] + pref[node];
    for(auto x: adj[node])
    {
        if(x!=parent)
        {
            fillans(adj, x, node, answer, childrensub, pref);
        }
    }
}
void solve()
{
    int n, q;
    cin>>n>>q;
    vector<vector<int>> adj(n+1);
    vector<int> dp(n+1, 0);
    vector<int> parents(n+1, 0);
    vector<int> sumsubtree(n+1, 0);
    for(int i=0; i<n-1; i++)
    {
        int a, b; cin >> a>> b;
        adj[a].pb(b);adj[b].pb(a);
    }
    dfs(adj, 1, 0, dp, parents, 0);
    // for(auto x: dp)
    // {
    //     cout<<x<<", ";
    // }
    // cout<<endl;
    vector<vector<int>> anc(n + 1, vector<int> (log2(n) + 1, 0)); 
    for(int i = 1; i <= n; i++)
    {
        anc[i][0] = parents[i];
        // cout<<i<<" "<<0<<" "<<anc[i][0]<<endl;
    }
    for(int i = 1; i <= log2(n); i++)
    {
        for(int j = 1; j <= n; j++)
        {
            anc[j][i] = anc[anc[j][i-1]][i-1];
            // cout<<j<<" "<<i<<" "<<anc[j][i]<<endl;
        }
    }
    vector<int> pref(n + 1, 0);
    vector<int> childrensub(n + 1, 0);
    while(q--)
    {
        int a, b;
        cin>>a>>b;
        // P(getLCA(a, b, dp, anc));
        auto tup = getLCA(a, b, dp, anc);
        P(get<0>(tup)) P(get<1>(tup)) P(get<2>(tup))
        if(get<0>(tup) != get<2>(tup)) pref[get<0>(tup)]++;
        if(get<1>(tup) != get<2>(tup)) pref[get<1>(tup)]++;
        pref[get<2>(tup)]++;
        if(a != get<2>(tup)) childrensub[a] -= 1;
        if(b != get<2>(tup)) childrensub[b] -= 1;
        childrensub[get<2>(tup)]--;
    }
    vector<int> answer(n + 1, 0);
    fillans(adj, 1, 0, answer, childrensub, pref);
    for(int i = 1; i<=n ; i++)
    {
        cout<<answer[i]<<" ";
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

