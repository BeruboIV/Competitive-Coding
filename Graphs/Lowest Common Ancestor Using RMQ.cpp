//0 Based indexing is followed here.
const int N = 2e5;
int LOG2[N + 1]; //Quick lookup table for floor(log2(i)), 1 <= i <= N
int min_idx[26][N + 1];
vector<int> adj[N + 1];
vector<int> euler; //stores the euler tour indices
vector<int> depth; //Stores the depth of the indices in the euler tour
int first[N + 1]; //Stores the first encounter of each index in the euler tour
int T; //Initialize with -1 --> Times the entry of each node in euler tour

void init(){
    for(int i = 2; i <= N; i++)
        LOG2[i] = 1 + LOG2[i/2];
}

void dfs(int src, int par, int dep){
    T++;
    if(first[src] == -1)
        first[src] = T;
    euler.push_back(src);
    depth.push_back(dep);
    for(int child : adj[src]){
        if(child != par){
            dfs(child, src, dep + 1);
            euler.push_back(src);
            depth.push_back(dep);
            T++;
        }
    }
}

int MinIdx(int l, int r){
    int len = r - l + 1;
    int p = LOG2[len];
    int left = depth[min_idx[p][l]];
    int right = depth[min_idx[p][r - (1 << p) + 1]];
    if(left <= right)
        return min_idx[p][l];
    else
        return min_idx[p][r - (1 << p) + 1];
}

int LCA(int u, int v){
    int left_idx = first[u];
    int right_idx = first[v];
    if(left_idx > right_idx)
        swap(left_idx, right_idx);
    int node_idx = MinIdx(left_idx, right_idx);
    return euler[node_idx];
}

void solve(){
    T = -1;
    euler.clear();
    depth.clear();
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        adj[i].clear();
        first[i] = -1;
    }
    for(int i = 1; i < n; i++){
        int x,y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    
    dfs(1, -1, 0);
    int size = depth.size();
    for(int i = 0; i < size; i++){
        min_idx[0][i] = i;
    }
    int P = LOG2[n];
    for(int p = 1; p <= P; p++){
        for(int i = 0; i + (1 << p) <= size; i++){
            int left = depth[min_idx[p - 1][i]];
            int right = depth[min_idx[p - 1][i + (1 << (p - 1))]];
            if(left <= right)
                min_idx[p][i] = min_idx[p - 1][i];
            else
                min_idx[p][i] = min_idx[p - 1][i + (1 << (p - 1))];
        }
    }
    int q;
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        cout << LCA(u, v) << "\n";
    }
}