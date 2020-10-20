//FOR 1 BASED INDEXING --> The Smallest Node Value is 1

const int N = 3e5;
vector<int> adj[N+1], transAdj[N+1];
vector<bool> used(N+1);
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
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        int x,y;
        cin >> x >> y;
        adj[x].pb(y);

        transAdj[y].pb(x);
    }
    used.assign(n + 1, false);
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
    order.clear(); 
    used.assign(n, false);
    for(int i = 1; i <= n; i++){
        adj[i].clear();
        transAdj[i].clear();
    }
    cout << cnt << "\n";
}  

/*

FOR 0 BASED INDEXING --> The Smallest Node Value is 0

const int N = 3e5;
vector<int> adj[N+1], transAdj[N+1];
vector<bool> used(N+1);
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
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int x,y;
        cin >> x >> y;
        adj[x].pb(y);

        transAdj[y].pb(x);
    }
    used.assign(n, false);
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs1(i);
    used.assign(n, false);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int v = order[n - 1 - i];
        if (!used[v]) {
            dfs2(v);
            component.clear();
            cnt++;
        }
    }
    order.clear(); 
    used.assign(n, false);
    for(int i = 0; i < n; i++){
        adj[i].clear();
        transAdj[i].clear();
    }
    cout << cnt << "\n";
}  


*/