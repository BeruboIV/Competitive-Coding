const int N = 6e5 + 10;
int parent[N], sz[N];
vector<pair<int, long long>> adj[N + 1];
vector<pair<long long, pair<int,int> > > cost; // {cost, x, y}

int findParent(int i){
    if(parent[parent[i]] != parent[i])
        parent[i] = findParent(parent[i]);
    return parent[i];
}

// int findParent(int i){
//     if(parent[i] != i)
//         parent[i] = findParent(parent[i]);
//     return parent[i];
// }

void unionNodes(int a,int b){
    int parent_a = findParent(a);
    int parent_b = findParent(b);
    if(parent_a == parent_b)
        return;

    if(sz[parent_a] >= sz[parent_b]){
        swap(parent_a,parent_b);
    }

    sz[parent_b] += sz[parent_a];
    parent[parent_a] = parent_b;
    return;
}

void clearDSU(int n){
    cost.clear();
    for(int i = 0; i <= n; i++){
        parent[i] = i;
        sz[i] = 1;
        adj[i].clear();
    }
}

void solve(){
    int n, m;
    cin >> n >> m;
    clearDSU(n);
    for(int i = 0; i < m; i++){
        int x,y;
        long long cst;
        cin >> x >> y >> cst;
        adj[x].push_back({y, cst});
        adj[y].push_back({x, cst});
        cost.push_back({cst, {x, y}});
    }
    
    // Kruskal's
    sort(cost.begin(), cost.end());
    
    long long sum = 0;
    for(auto edge : cost){
        long long cst = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        // We need the topmost parent
        int parent_u = findParent(u);
        int parent_v = findParent(v);
        if(parent_u != parent_v){ // Here parent_u = parent[parent_u]
            // We have to add this edge
            sum += cst;
            unionNodes(u, v);
            
        }
        else{
            // This edge will make a cycle, so we ignore it
            continue;
        }
    }
    cout << sum << "\n";
    for(int i = 1; i <= n; i++)
        cout << parent[i] << " ";
    cout << "\n";
    // For printing the size of each component
    for(int i = 1; i <= n; i++){
        int p = parent[i];
        cout << sz[p] << " ";
    }
}