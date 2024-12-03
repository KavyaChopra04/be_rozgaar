#include <bits/stdc++.h>
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
            res*=a;
        }
        a*=a;
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
int bipartite(int node, vector<bool> &vis, vector<vector<int>> &edges, vector<int> &color, int currcolor)
{
	//cout<<"currenty at node "<<node<<'\n';
	vis[node]=true;
	int retval=0;
	color[node]=currcolor;
	for(auto x: edges[node])
	{
		if(!vis[x])
		{
			retval = min(retval, bipartite(x, vis, edges, color, 1-currcolor));
		}
		else
		{
			if(color[x] == currcolor)
			{
				return -1;
			}
		}
	}
	return retval;
}
int n, l;
vector<vector<int>> adj;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}
void dfs(int node, vector<int> &vis, vector<vector<int>> &edges, stack<int> &s, int it, bool &checkCycle)
{
	//cout<<"it is "<<it<<" node is "<<node<<'\n';
	vis[node]=it;
	for(auto x: edges[node])
	{
		if(vis[x]==-1)
		{
			dfs(x, vis, edges, s, it, checkCycle);
		}
		else if(vis[x]==it)
		{
			//cout<<"cycle at node "<<x<<" negihbour of "<<node<<'\n';
			checkCycle=true;
			return;
		}

	}
	vis[node]=0;
	s.push(node);
}
pair<int, int> cycleDFS(int node, vector<bool> &vis, vector<vector<int>> &edges, vector<int> &parent)
{
	pair<int, int> p = mp(-1, -1);
	vis[node]=true;
	for(auto x: edges[node])
	{
		if(!vis[x])
		{
			parent[x] = node;

			pair<int, int> p1 = cycleDFS(x, vis, edges, parent);
			if(p1.first+p1.second!=-2)
			{
				return p1;
			}
			
		}
		else if(x!=parent[node])
		{
			return mp(x, node);
		}
	}
	return p;
}
pair<int, int> cycleDirectedDFS(int node, vector<int> &vis, vector<vector<int>> &edges, vector<int> &parent, int it)
{
	pair<int, int> p = mp(-1, -1);
	vis[node]=it;
	//cout<<"at node "<<node<<endl;

	for(auto x: edges[node])
	{
		//cout<<x<<" is a child of "<<node<<endl;
		if(vis[x]==-1)
		{
			//cout<<"child of "<<node<<" is "<<x<<'\n';
			parent[x] = node;
			pair<int, int> p1 = cycleDirectedDFS(x, vis, edges, parent, it);
			if(p1.first+p1.second!=-2)
			{
				return p1;
			}
		}
		else if(vis[x]==it)
		{
			return mp(x, node);
		}
	}
	vis[node]=0;
	return p;
}
pair<int, int> cycleCheckBfs(int node, vector<bool> &vis, vector<vector<int>> &edges, vector<int> &parent)
{
	queue<int> q;
	q.push(node);
	vis[node]=true;
	while(!q.empty())
	{
		int f = q.front();
		q.pop();
		cout<<"popped node "<<f<<endl;
		for(auto x: edges[f])
		{

			if(!vis[x])
			{
				q.push(x);
				parent[x]=f;
				cout<<"setting parent of "<<x<<" to "<<f<<endl;
				vis[x]=true;
			}
			else
			{
				if(vis[x] && parent[f]!=x)
				{
					return mp(x, f);
				}
			}
		}
	}
	return mp(-1, -1);
}

void topSort(int node, vector<bool> &vis, vector<vector<int>> &edges, vector<pair<int, int>> &deptime, int &time)
{
	vis[node]=true;
	int st = time;
	time++;
	for(auto x: edges[node])
	{
		if(!vis[x])
		{
			topSort(x, vis, edges, deptime, time);
			time++;
		}
	}
	deptime[node] = mp(time, st);
}
vector<int> tsHelper(vector<pair<int, int>> &deptime)
{
	vector<int> corrorder;
	vector<pair<int, int>> nodetime;
	for(int i=1;i<deptime.size();i++)
	{
		nodetime.pb(mp(deptime[i].second,i));
	}
	sort(nodetime.begin(), nodetime.end());
	for(auto x: nodetime)
	{
		corrorder.pb(x.second);
	}
	reverse(corrorder.begin(), corrorder.end());
	return corrorder;
}
void cycleCheckDFS(int node, vector<bool> &vis, vector<vector<int>> &edges, vector<int> &parent)
{

}
void dijkstra(int source, vector<int> &distances, int nodes, vector<vector<pair<int, int>>> &edges, vector<bool> &vis)
{
	priority_queue<pair<int, int>> q;
	distances[source]=0;
	q.push(mp(0, source));
	int vissum=0;
	while(!q.empty())
	{
		pair<int, int> p=q.top();
		q.pop();
		if(vis[p.second])
		{
			continue;
		}
		vis[p.second]=true;
		//cout<<"node at top is "<<p.second<<endl;
		for(auto x: edges[p.second])
		{
			if(!vis[x.first] && (distances[x.first] > distances[p.second] + x.second))
			{
				distances[x.first]=distances[p.second] + x.second;
				q.push(mp(-1*distances[x.first], x.first));
			}
		}
		
	}
}

void floydwarshall(vector<vector<int>> &distances, vector<vector<pair<int, int>>> &edges, int nodes)
{
	for(int i=1;i<=nodes;i++)
	{
		distances[i][i]=0;
	}
	for(int i=1;i<=nodes;i++)
	{
		for(auto x: edges[i])
		{
			distances[i][x.first] = min(distances[i][x.first] , x.second);
		}
	}
	for(int k=1;k<=nodes;k++)
	{
		for(int j=1;j<=nodes;j++)
		{
			for(int i=1; i<=nodes;i++)
			{
				distances[j][i] = min(distances[j][i], distances[j][k] + distances[k][i]);
			}
		}
	}
}
void bfs(int node, vector<bool> &vis, vector<vector<int>> &edges, vector<int> &parent)
{
	queue<int> q;
	q.push(node);
	vis[node]=true;
	while(!q.empty())
	{
		int f = q.front();
		q.pop();
		for(auto x: edges[f])
		{
			if(!vis[x])
			{
				q.push(x);
				parent[x]=f;
				vis[x]=true;
			}
		}
	}
}
bool mergeCheck(vector<int> &a, vector<int> &b,vector<int> &v)
{
    int i=0,j=0,k=0;
    int n = a.size();
    vector<int> c(2*n);
    while (i<n && j<n)
    {
        if(a[i] < b[j])
        {
            c[k] = a[i];
            i++;
        }
        else{
            c[k] = b[j];
            j++;
        }
        k++;
    }
    while(i<n)
    {
        c[k++] = a[i++];
    }
    while (j<n)
    {
        c[k++] = b[j++];
    }
    //cout<<endl;
    for(int i=0; i<2*n; i++)   
    {
        if(c[i]!=v[i])
        {
            //cout<<c[i]<<" "<<v[i]<<endl;
            return false;
        }
    } 
    return true;
}
vector<tuple<int, int, int>> get_neighbours(int x, int y, int n, int m, vector<vector<int>> &r_nw, vector<vector<int>> &l_nw, vector<vector<int>> &d_nw, vector<vector<int>> &u_nw)
{
    vector<tuple<int, int, int>> neighbours;
    if(x > 0)
    {
        neighbours.push_back(make_tuple(x-1, y, u_nw[x][y]));
    }
    if(x < n - 1)
    {
        neighbours.push_back(make_tuple(x+1, y, d_nw[x][y]));
    }
    if(y > 0)
    {
        neighbours.push_back(make_tuple(x, y-1, l_nw[x][y]));
    }
    if(y < m - 1)
    {
        neighbours.push_back(make_tuple(x, y + 1, r_nw[x][y]));
    }
    return neighbours;
}
struct intdef
{
    int i = inf;
    intdef() :i(inf){}
    intdef(int i) :i(i){}
};

void solve()
{
    int n,k;cin>>n>>k;
    vector<int> arr(n+1, 0);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i+1];
    }
    vector<int> hot(k+1);
    vector<int> cold(k+1);
    for(int i=0;i<k;i++)
    {
        cin>>cold[i+1];
    }
    for(int i=0;i<k;i++)
    {
        cin>>hot[i+1];
    }
    // map<pair<int, int>, intdef> dp;
    // dp[make_pair(arr[1], 0)] = intdef(cold[arr[1]]);
    // dp[make_pair(0, arr[1])] = intdef(cold[arr[1]]);
    // for(int i=2;i<=n;i++)
    // {
    //     map<pair<int, int>, intdef> newdp;
    //     for(auto x: dp)
    //     {
    //         if(x.first.first == arr[i] || x.first.second == arr[i])
    //         {
    //             newdp[x.first] = intdef(min(newdp[x.first].i, dp[x.first].i+hot[arr[i]]));
    //         }
    //         else
    //         {
    //             newdp[make_pair(x.first.first, arr[i])] = intdef(min(newdp[make_pair(x.first.first, arr[i])].i, dp[x.first].i+cold[arr[i]]));
    //             newdp[make_pair(arr[i], x.first.second)] = intdef(min(newdp[make_pair(arr[i], x.first.second)].i, dp[x.first].i+cold[arr[i]]));
    //         }
    //     }
    //     dp = newdp;
    // }
    // int ans = inf;
    // for(auto x: dp)
    // {
    //     ans = min(ans, x.second.i);
    // }
    // cout<<ans<<'\n';
    vector<int> dp_x(k+1, inf);
    vector<int> dp_y(k+1, inf);
    dp_x[0] = cold[arr[1]];
    dp_y[0] = cold[arr[1]];
    for(int i=2;i<=n;i++)
    {
        vector<int> newdp_x(k+1, inf);
        vector<int> newdp_y(k+1, inf);
        int min_x =  inf;
        int min_y = inf;
        bool alwaysHot = false;
        if(arr[i]==arr[i-1])
        {
            alwaysHot = true;
        }
        for(int j=0;j<=k;j++)
        {
            if(j==arr[i])
            {
                newdp_y[arr[i-1]] =min(dp_x[j] + hot[arr[i]], newdp_y[arr[i-1]]);
                newdp_x[arr[i-1]] =min(dp_y[j] + hot[arr[i]], newdp_x[arr[i-1]]);
            }
            else
            {
                if(!alwaysHot)
                {
                    newdp_y[j] = min(newdp_y[j],dp_y[j] + cold[arr[i]]);
                    newdp_x[j] = min(newdp_x[j],dp_x[j] + cold[arr[i]]);
                }
                else
                {
                    newdp_y[j] = min(newdp_y[j],dp_y[j] + hot[arr[i]]);
                    newdp_x[j] = min(newdp_x[j],dp_x[j] + hot[arr[i]]);
                }
                min_x = min(min_x, dp_x[j]);
                min_y = min(min_y, dp_y[j]);
            }
        }
        if(!alwaysHot)
        {
            newdp_x[arr[i-1]] = min(newdp_x[arr[i-1]], min_x + cold[arr[i]]);
            newdp_y[arr[i-1]] = min(newdp_y[arr[i-1]], min_y + cold[arr[i]]);
        }
        else
        {
            newdp_x[arr[i-1]] = min(newdp_x[arr[i-1]], min_x + hot[arr[i]]);
            newdp_y[arr[i-1]] = min(newdp_y[arr[i-1]], min_y + hot[arr[i]]);
        }
        dp_x = newdp_x;
        dp_y = newdp_y;
    }
    int ans = inf;
    for(auto x: dp_x)
    {
        ans = min(ans, x);
    }
    for(auto x: dp_y)
    {
        ans = min(ans, x);
    }
    cout<<ans<<'\n';
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
    cin>>t;
    while(t--)
    {
        solve();
    }
} 

