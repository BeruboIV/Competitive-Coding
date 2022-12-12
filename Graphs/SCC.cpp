const int MAXN = 3e5;
vector<int> adj[MAXN+1], transAdj[MAXN+1];
vector<bool> used(MAXN+1);
vector<int> order, component;
 
void dfs1(int src) {
    used[src] = true;
    for (int child : adj[src])
        if(!used[child]) 
            dfs1(child);
    order.push_back(src);
}
 
void dfs2 (int src) {
    used[src] = true;
    component.push_back(src);
    for (int child : transAdj[src])
        if (!used[child])
            dfs2(child);
}

void solve(){
    int n, m;
    cin >> n >> m;

    order.clear();
    for(int i = 1; i <= n; i++){
        used[i] = false;
        adj[i].clear();
        transAdj[i].clear();
    }

    for(int i = 1; i <= m; i++)
    {
        int x,y;
        cin >> x >> y;
        adj[x].pb(y);

        transAdj[y].pb(x);
    }
    for (int i = 1; i <= n; ++i)
        if (!used[i])
            dfs1(i);
    used.assign(n + 1, false);
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int v = order[n - i];
        if (!used[v]) {
            dfs2(v);
            component.clear();
            cnt++;
        }
    }
    
    cout << cnt << "\n";
}  