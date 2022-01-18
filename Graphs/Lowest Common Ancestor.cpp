// Class based LCA
// 1 Based indexing is used

template <typename T = long long>
class LCA{
public:
    int N = 2e5;    //Number of nodes.
    int P = 25; //Highest set bit possible
    int LOG2[N + 1], level[N + 1];
    int LCA[N + 1][P + 2]; //LCA[i][j] stores the 2^(jth) parent of node i
    vector<int> graph[N + 1];

    LCA(int n = 200005){
        N = n + 1;
    }

    void add_edge(int x, int y){
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    void dfs(int node, int par, int depth = 0){

        for(int child : graph[node]){
            if(child == par)
                continue;
            LCA[child][0] = node;   // Parent
            level[child] = depth + 1;
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
                LCA[i][j] = -1;
            }
        }

        level[src] = 0;
        dfs(src, -1, 0);
        for(int p = 1; p <= P; p++){
            for(int node = 1; node <= N; node++){
                int par = LCA[node][p - 1];
                if(par == -1)
                    LCA[node][p] = -1;
                else
                    LCA[node][p] = LCA[par][p - 1];
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
            a = LCA[a][i];
            diff -= (1 << i);
        }
        //If a is in the subtree of b
        if(a == b)
            return a;
        // while(LCA[a][0] != LCA[b][0]){
        //     a = LCA[a][0];
        //     b = LCA[b][0];
        // } Takes O(N) time
        for(int i = P; i >= 0; i--){
            if(LCA[b][i] != -1 && (LCA[a][i] != LCA[b][i])){
                a = LCA[a][i];
                b = LCA[b][i];
            }
        }
        return LCA[a][0];
    }
};

void solve(){
    int n;
    cin >> n;
    LCA<long long> lca(n);
    for(int i = 0; i < n - 1; i++){
        int x,y;
        cin >> x >> y;
        lca.add_edge(x, y);
    }
    lca.precompute_LCA(1);
    int q;
    cin >> q;
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