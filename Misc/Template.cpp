#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
# define ll  long long int
# define ld  long double
# define pb push_back
typedef priority_queue<ll, vector<ll>, greater<ll>> minheap;
typedef priority_queue<ll> maxheap;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

void solve(){
}

int main()
{
    #ifndef ONLINE_JUDGE
      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
    #endif
     IOS
     int t = 1;
     cin >> t;
     while(t--){
     	solve();
     	// cout << fixed << setprecision(7); //For trailing 0's
     }
	return 0;
}