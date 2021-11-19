const int N = 1e5;
set<int> adj[N + 1];
int subtree[N + 1], parentCentroid[N + 1];

void dfs(int src, int par){
    subtree[src] = 1;

    for(int child : adj[src]){

        if(child == par)
            continue;
        dfs(child, src);
        subtree[src] += subtree[child];
    }
}

int centroid(int src, int par, int n){
    for(int child : adj[src]){
        if(child == par)
            continue;

        if(subtree[child] > (n / 2))
            return centroid(child, src, n);
    }

    return src;
}

void decompose(int src, int par = -1){
    int subTreeSize = dfs(src, -1);

    int centroid_node = centroid(src, par, subTreeSize);

    parentCentroid[centroid_node] = par;

    for(int child : adj[src]){
        adj[child].erase(src);
        decompose(child, centroid_node);
    }
}
