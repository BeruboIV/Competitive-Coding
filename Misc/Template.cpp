#include "bits/stdc++.h"
using namespace std;
using ll = long long int;
using ld = long double;
typedef priority_queue<ll, vector<ll>, greater<ll>> minheap;
typedef priority_queue<ll> maxheap;

#ifdef BeruboIV
#include "debug.h"
#else
#define debug(...) 42
#endif 

void solve(){
}

int main()
{
    ios_base::sync_with_stdio(false);
#ifndef BeruboIV
    cin.tie(NULL);
#endif
    int t = 1;
    cin >> t;
    while(t--){
        solve();
        // cout << fixed << setprecision(7); //For trailing 0's
    }
    return 0;
}