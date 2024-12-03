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
struct cusComp{
bool operator()(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b) const
{
    if(a.first != b.first)
    {
        return a.first < b.first;
    }
    return a.second.first > b.second.first;
}
};

void solve()
{
    int n;
    cin>>n;
    vector<int> v(n + 1);
    vector<int> sums(n + 1);
    for(int i = 0; i < n; i++){
        cin>>v[i+1];
        sums[i+1] = sums[i] + v[i+1];
    }
    vector<int> prefsum(n + 1);
    vector<int> counts(n + 1);
    for(int i = 1; i <= n; i++)
    {
        counts[i] = counts[i-1] + (n - i + 1);
    }
    for(auto x: sums)
    {
        cout<<x<<", ";
    }
    cout<<endl;

    for(auto x: counts)
    {
        cout<<x<<", ";
    }
    cout<<endl;
    for(int i = 0; i < n; i++)
    {
        prefsum[i + 1] = prefsum[i] + sums[i + 1];
    }
    for(auto x: prefsum)
    {
        cout<<x<<", ";
    }
    cout<<endl;
    vector<int> allsums(n+1);
    for(int i = 0; i < n; i++)
    {
        allsums[i + 1] = allsums[i] + prefsum[n] - prefsum[i] - ((n - i)*sums[i]);
    }
    for(auto x: allsums)
    {
        cout<<x<<", ";
    }
    cout<<endl;
    int q; cin>>q;
    while(q--)
    {
        int l, r;
        cin>>l>>r;
        // P(l);
        // P(r);
        auto it1 = lower_bound(counts.begin(), counts.end(), l);
        auto it2 = lower_bound(counts.begin(), counts.end(), r);
        int ans = 0;
        if(*it2 != r)
        {
            it2--;
        }
        if(it1 > it2)
        {
            //S(k,a) + S(k, a+1) +  .... S(k, b) = S(1, a) + ... S(1, b) - (b-a+1)*S(1, k)
            int k = it2 - counts.begin();
            int a = k + (l - *it2);
            int b = k + (r - *it2);
            // P(k);
            // P(a);
            // P(b);
            ans = prefsum[b] - prefsum[a-1] - (b + 1 - a)*sums[k];
        }
        else
        {
            //S(k, )
                    P(*it1);
        P(*it2);
            if(*it1 != l) {it1--;};
            int l_val = it1 - counts.begin();
            int a =  l_val + (l - *it1);
            ans += prefsum[n] - prefsum[a - 1] - (n + 1 - a)*sums[l_val];
            if(r_val != *it2)
            {
                int r_val  = it2  - counts.begin();
                int b = r_val + (r - *it2);
                ans += prefsum[b] - b*sums[r_val];
            }
            
            ans += allsums[r_val - 1] - allsums[l_val];
        }
        cout<<ans<<'\n';
    }


    
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
    // cin>>t;
    while(t--)
    {
        solve();
    }
} 

