// CLASS BASED LCA

// 0 Based indexing is used        
template <typename T = long long>
class LCA{
public:
    int N = 2e5;    //Number of nodes.
    int P = 25; //Highest set bit possible
    vector<int> LOG2, level;
    vector<vector<int>> lca;    //LCA[i][j] stores the 2^(jth) parent of node i
    vector<vector<int>> graph;

    LCA(int n = 200005){
        N = n;
        LOG2.resize(N + 10);
        level.resize(N + 10);
        lca.resize(N + 10);
        graph.resize(N + 10);
        for(int i = 0; i <= N; i++){
            lca[i].resize(27);
        }
    }

    void add_edge(int x, int y){
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    void dfs(int node, int par = -1, int depth = 0){
        lca[node][0] = par;
        level[node] = depth;


        for(int child : graph[node]){
            if(child == par)
                continue;
            dfs(child, node, depth + 1);
        }
    }

    //We will root the tree at src 
    void precompute_LCA(int src){
        for(int i = 2; i <= N; i++)
            LOG2[i] = LOG2[i/2] + 1;
        int p = LOG2[N];
        for(int i = 0; i <= N; i++){
            for(int j = 0; j <= p; j++){
                lca[i][j] = -1;
            }
        }

        dfs(src, -1, 0);
        for(int p = 1; p <= P; p++){
            for(int node = 0; node <= N; node++){
                int par = lca[node][p - 1];
                if(par == -1)
                    lca[node][p] = -1;
                else
                    lca[node][p] = lca[par][p - 1];
            }
        }
    }
    
    int getLCA(int a, int b){
        //We need the deeper node
        //Assume a is the deeper node
        if(level[a] < level[b])
            swap(a,b);
        int diff = level[a] - level[b];
        while(diff > 0){
            int i = LOG2[diff];
            a = lca[a][i];
            diff -= (1 << i);
        }
        //If a is in the subtree of b
        if(a == b)
            return a;
        // while(lca[a][0] != lca[b][0]){
        //     a = lca[a][0];
        //     b = lca[b][0];
        // } Takes O(N) time
        for(int i = P; i >= 0; i--){
            if(lca[b][i] != -1 && (lca[a][i] != lca[b][i])){
                a = lca[a][i];
                b = lca[b][i];
            }
        }
        return lca[a][0];
    }
};

void solve(){
    int n, q;
    cin >> n >> q;
    LCA<int> lca(n);
    for(int i = 1; i <= n - 1; i++){
        int p;
        cin >> p;
        lca.add_edge(i, p);
    }
    lca.precompute_LCA(0);
    while(q--){
        int a,b;
        cin >> a >> b;
        cout << lca.getLCA(a,b) << "\n";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

const int N = 2e5;	//Number of nodes.
const int P = 25; //Highest set bit possible
int LCA[N + 1][P + 2]; //LCA[i][j] stores the 2^(jth) parent of node i
vector<int> adj[N + 1];
int LOG2[N + 1];
int level[N + 1];

void dfs(int node, int par){
	LCA[node][0] = par;
	if(par == -1){
		level[node] = 0;
	}
	else{
		level[node] = level[par] + 1;
	}
	for(int child : adj[node]){
		if(child != par)
			dfs(child, node);
	}
}

//We will root the tree at src 
void precompute_LCA(int src, int n){
	for(int i = 2; i <= N; i++)
		LOG2[i] = LOG2[i/2] + 1;
	int p = LOG2[n];	// Small optimization
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= p; j++)
			LCA[i][j] = -1;
	}
	dfs(src, -1);
	for(int j = 1; j <= p; j++){
		for(int i = 1; i <= n; i++){
			int par = LCA[i][j-1];
			if(par == -1)
				LCA[i][j] = -1;
			else
				LCA[i][j] = LCA[par][j-1];
		}
	}
	
}

int getLCA(int a, int b, int n){
	//We need the deeper node
	//Assume a is the deeper node
	if(level[a] < level[b])
		swap(a,b);
	int d = level[a] - level[b];
	while(d > 0){
		int i = LOG2[d];
		a = LCA[a][i];
		d -= (1 << i);
	}
	//If a is in the subtree of b
	if(a == b)
		return a;
	// while(LCA[a][0] != LCA[b][0]){
	// 	a = LCA[a][0];
	// 	b = LCA[b][0];
	// } Takes O(N) time
	int p = LOG2[n];	// Small optimization
	for(int i = p; i >= 0; i--){
		if(LCA[b][i] != -1 && (LCA[a][i] != LCA[b][i])){
			a = LCA[a][i];
			b = LCA[b][i];
		}
	}
	return LCA[a][0];
}

void solve(){
	int n;
	cin >> n;
	for(int i = 1; i < n; i++){
		int x,y;
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	precompute_LCA(1, n);
	int q;
	cin >> q;
	while(q--){
		int a,b;
		cin >> a >> b;
		cout << getLCA(a, b, n) << "\n";
	}
}