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
int isSquare(int r, int g, int n, int k)
{
    int lo=n-1,hi=r;
    while(lo<hi)
    {
        int mid = lo + (hi-lo+1)/2;
        //cout<<hi<<" "<<lo<<" "<<mid<<endl;
        if(mid%g!=0 && mid/g+ k==mid)
        {
            lo=mid;
            break;
        }
        if(mid%g!=0 && mid/g + k>=mid)
        {
            lo=mid;
        }
        else if(mid/g+ k>=mid)
        {
            lo=mid;
        }
        else
        {
            hi=mid-1;
        }
    }
    return lo;
}
int dfs(int n, vector<bool> &vis, vector<vector<int>> &adj, vector<int> &dp, int parent, int numnodes)
{
    vis[n]=true;
    if(adj[n].size()==1 && adj[n][0]==parent)
    {
        dp[n] = 1;
        return 0;
    }
    int edgecontris = 0;
    int subcard = 1;
    for(auto x: adj[n])
    {
        if(x==parent) continue;
        edgecontris += dfs(x, vis, adj, dp, n, numnodes);
        subcard = (subcard + dp[x])%mod;
    }
    for(auto x: adj[n])
    {   
        if(x==parent) continue;
        edgecontris = (edgecontris + ((numnodes - dp[x] + mod)%mod * dp[x])%mod)%mod;
    }
    dp[n] = subcard;
    return edgecontris;
}   
struct cmp {
    bool operator() (pair<int, int> a, pair<int, int> b) const {
        if(b.first > a.first && b.second > a.second) return true;
        return false;
    }
};

void construct_segment_tree(vector<int>& segtree,
                            vector<int>& a, int n)
{
    // assign values to leaves of the segment tree
    for (int i = 0; i < n; i++)
        segtree[n + i] = a[i];
 
    /* assign values to internal nodes
    to compute maximum in a given range */
    for (int i = n - 1; i >= 1; i--)
        segtree[i] = max(segtree[2 * i],
                         segtree[2 * i + 1]);
}

void printsegtree(vector<int>& segtree, int n)
{
    for (int i = 0; i < n; i++)
        cout<<segtree[n+i]<<", ";
    cout<<endl;
}
 
void update(vector<int>& segtree, int pos, int value,
            int n)
{
    // change the index to leaf node first
    pos += n;
 
    // update the value at the leaf node
    // at the exact index
    segtree[pos] = value;
 
    while (pos > 1) {
 
        // move up one level at a time in the tree
        pos >>= 1;
 
        // update the values in the nodes in
        // the next higher level
        segtree[pos] = max(segtree[2 * pos],
                           segtree[2 * pos + 1]);
    }
}
 
int range_query(vector<int>& segtree, int left, int
                                                    right,
                int n)
{
    /* Basically the left and right indices will move
        towards right and left respectively and with
        every each next higher level and compute the 
        maximum at each height. */
    // change the index to leaf node first
    left += n;
    right += n;
 
    // initialize maximum to a very low value
    int ma = INT_MIN;
 
    while (left < right) {
 
        // if left index in odd
        if (left & 1) {
            ma = max(ma, segtree[left]);
 
            // make left index even
            left++;
        }
 
        // if right index in odd
        if (right & 1) {
 
            // make right index even
            right--;
 
            ma = max(ma, segtree[right]);
        }
 
        // move to the next higher level
        left /= 2;
        right /= 2;
    }
    return ma;
}
void solve()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    vector<int> diff(n-1);
    vector<int> absdiff(n-1);
    for(int i=0;i<n-1;i++)
    {
        diff[i] = arr[i+1] - arr[i];
        absdiff[i] = abs(diff[i]);
    }
    vector<int> segtree(2 * (n-1));
    construct_segment_tree(segtree, absdiff, n-1);
    int q;cin>>q;
    for(int i=0;i<q;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        if(a==1)
        {
            //cout<<"earlier "<<diff[b-1]<<" and "<<diff[b-2]<<endl;
            if(b!=n) diff[b-1] -= c - arr[b-1];
            if(b!=1) diff[b-2] += c - arr[b-1];
            //cout<<"updating "<<diff[b-1]<<" and "<<diff[b-2]<<endl;
            if(b!=n) update(segtree, b-1, abs(diff[b-1]), n-1);
            if(b!=1) update(segtree, b-2, abs(diff[b-2]), n-1);
            arr[b-1] = c;
        }
        else
        {
            if(b==n)
            {
                cout<<n<<'\n';continue;
            }
            int lo=b-1,hi=n-1;
            while(lo<hi)
            {
                int mid = lo + (hi - lo)/2;
                if(range_query(segtree, lo, mid + 1, n-1) > c) hi = mid;
                else lo = mid + 1;
            }
            cout<<lo + 1<<'\n';
        }
        //printsegtree(segtree, n-1);
    }



    
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
    //cin>>t;
    //cout<<isSquare(36)<<'\n';
    while(t--)
    {
        solve();
    }
}