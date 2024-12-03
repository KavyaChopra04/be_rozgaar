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
   int n,q;cin>>n>>q;
   vector<int> v(n);
   set<int> main_cp;
   int sum =0;
   for(int i=0;i<n;i++)
   {
    cin>>v[i];
    sum+=v[i];
    if(sum == ((i + 1)*(i+2))/2) {main_cp.insert(i);}
   }
//    for(auto x: main_x)
   set<int> curr_cp;
   int numextra = 0;
    string s; 
    cin>>s;
    for(int i=0;i<n-1;i++)
    {
        if(s[i]=='L' && s[i+1]=='R')
        {
            curr_cp.insert(i);
            if(main_cp.find(i) == main_cp.end())
            {
                numextra++;
                
            }

        }
    }
    // P(numextra);
    while(q--)
    {
        int k;
        cin>>k;
        k--;
        
            if(k < n-1 && s[k] == 'L' && s[k+1] == 'R')
            {   
                curr_cp.erase(curr_cp.find(k));
                if(main_cp.find(k) == main_cp.end())
                {
                    numextra--;
                }

            }
            
            if(k > 0 && s[k-1] == 'L' && s[k] == 'R')
            {
                curr_cp.erase(curr_cp.find(k-1));
                if(main_cp.find(k-1) == main_cp.end())
                {
                    numextra--;
                }
            }
            if(k > 0 && s[k-1] == 'L' && s[k] == 'L')
            {
                curr_cp.insert(k-1);
                if(main_cp.find(k-1) == main_cp.end())
                {
                    numextra++;
                }
            }
            if(k < n - 1 && s[k] == 'R' && s[k+1] == 'R')
            {   
                curr_cp.insert(k);
                if(main_cp.find(k) == main_cp.end())
                {
                    numextra++;
                }
            }
            s[k] = 'L' +'R' - s[k];
            if(numextra == 0)
            {
                cout<<"YES\n";
            }
            else
            {
                cout<<"NO\n";
            }

        }
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

