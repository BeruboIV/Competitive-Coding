const int N = 2e5;
const long long INF = 1e18;
vector<pair<int,long long>> adj[N + 1];
long long dist[N + 1];
int parent[N + 1];

void dijsktra(int src, int n){
	for(int i = 1; i <= n; i++){
		dist[i] = INF;
		parent[i] = -1;
	}
	dist[src] = 0;
	set<pair<long long, int>> pq;
	//{dist, node}
	pq.insert({0, src});
	while(!pq.empty()){
		pair<long long,int> p = *pq.begin();
		long long curr_dist = p.first;
		int curr_node = p.second;
		pq.erase(pq.begin());
		// if(curr_dist != dist[curr_node])
		// 	continue;
		for(auto edge : adj[curr_node]){
			int next_node = edge.first;
			long long edge_cost = edge.second;

			long long new_dist = curr_dist + edge_cost;
			if(new_dist < dist[next_node]){
				// If we perform relaxation, then the adjacent edges might
				// also get relaxed
				dist[next_node] = new_dist;
				parent[next_node] = curr_node;
				auto it = pq.find({dist[next_node], next_node});
				if(it != pq.end())
					pq.erase(it);
				pq.insert({new_dist, next_node});
			}
		}
	}
}

void solve(){
	int n,m;
	cin >> n >> m;
	// n -> Vertices, m -> Edges
	for(int i = 0; i < m; i++){
		int x,y;
		long long cst;
		cin >> x >> y >> cst;
		adj[x].push_back({y, cst});
		adj[y].push_back({x, cst});
	}
	int src = 1;
	dijsktra(src, n);
	for(int i = 1; i <= n; i++)
		cout << dist[i] << " ";
}
