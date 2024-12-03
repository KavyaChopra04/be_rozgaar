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

void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    //Initial solution was wrong in the sense that it assumed that only 
    // vector<int> A(n,0); //RR
    // vector<int> B(n,0); //RL
    // vector<int> C(n,0); //LR
    // vector<int> D(n,0); //LL
    // vector<int> E(n, 0); //RL_L
    // vector<int> F(n, 0); //RL_R
    // if(s[0] == 'R')
    // {
    //     D[0] = 1;
    //     B[0] = INT_MAX;
    //     C[0] = INT_MAX;
    //     E[0] = INT_MAX;
    //     F[0] = INT_MAX;
    //     C[1]+=1;
    //     D[1]+=1;
    // }
    // else
    // {
    //     A[0] = 1;
    //     B[0] = INT_MAX;
    //     C[0] = INT_MAX;
    //     E[0] = INT_MAX;
    //     F[0] = INT_MAX;
    //     A[1]+=1;
    //     B[1]+=1;
    //     E[1]+=1;
    // }
    // if(s[1] == 'L')
    // {
    //     F[1] = INT_MAX;
    //     A[1]+=1;
    //     C[1]+=1;
    // }
    // else
    // {
    //     F[1] = INT_MAX;
    //     B[1]+=1;
    //     D[1]+=1;
    //     E[1]+=1;
    // }
    // for(int i=2;i<n;i++)
    // {
    //     A[i] = E[i-1] + (s[i]=='R' ? 0 : 1);
    //     B[i] = A[i-2] + (s[i] == 'L' ? 0 : 1);
    //     C[i] = min(D[i-2] + (s[i-1]=='R' ? 0 : 1), D[i-1])+ (s[i]=='R' ? 0 : 1);
    //     D[i] = C[i-1] + (s[i] == 'L' ? 0 : 1);
    //     if(F[i-1]!=INT_MAX){
    //         E[i] = min(F[i-1], F[i-2] + (s[i-1]=='L' ? 0 : 1)) + (s[i] == 'L' ? 0 : 1);
    //     }
    //     else
    //     {
    //         E[i] = B[i-1] + (s[i] == 'L' ? 0 : 1);
    //     }
    //     F[i] = E[i-1] + (s[i]=='R' ? 0 : 1);
    // }
    // // for(int i=1;i<n;i++)
    // // {
    // //     cout<<i<<" RR: "<<A[i]<<" RL: "<<B[i]<<" LR: "<<C[i]<<" LL: "<<D[i]<<" RL_L: "<<E[i]<<endl;
    // // }
    // cout<<min(F[n-1],min(E[n-1],min(A[n-1], min(B[n-1], min(C[n-1], D[n-1])))))<<'\n';

    //Non-DP solution is much cuter; don't pigeonhole yourself into thinking in one way. Idea: No 3 characters of the same type should be together. 
    //Find all subsegments like this, divide their length by 3 and add up these quotients
    bool allSame = true;
    for(int i=0;i<n;i++)
    {
        if(s[i]!=s[0])
        {
            allSame= false;
            break;
        }
    }
    if(allSame)
    {
        cout<<(n+2)/3<<'\n';
        return;
    }
    vector<pair<int, int>> v;
    char prevc=s[0];
    int ans=0;
    int st=0, end=n-1;
    int ct=1;
    while(s[end]==s[st])
    {
        ct++;
        end--;
    }
    prevc = s[st];
    st++;
    while(st<=end)
    {
        while(st < n && s[st]==prevc)
        {
            ct++;
            st++;
        }
        //cout<<st<<" "<<ct<<'\n';
        ans+=ct/3;
        ct=0;
        prevc=s[st];
    }
    cout<<ans<<'\n';
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    cost[1]=0;
    int maxv = INT_MIN;
    // for(int i=2;i<=1000;i++)
    // {
    //     cost[i] = INT_MAX;
    //     for(int j=1;j<i;j++)
    //     {
    //         if(((j / (i-j)) && j / (j / (i-j)) == i-j) || j / ((j / (i-j)) + 1) == i-j)
    //         {
    //             cost[i] = min(cost[j] + 1, cost[i]);
    //         }
    //     }
    //     maxv = max(maxv, cost[i]);
    // }
    // for(int i=1;i<=10;i++)
    // {
    //     cout<<cost[i]<<", ";
    // }
    // cout<<endl;
    // cout<<maxv<<endl;
	int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
} 

