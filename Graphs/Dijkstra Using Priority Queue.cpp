const int N = 2e5;
const int INF = 1e9;
vector<pair<int,long long>> adj[N + 1];
long long dist[N + 1];
int parent[N + 1];	

void dijsktra(int src, int n){
	for(int i = 1; i <= n; i++){
		dist[i] = INF;
		parent[i] = -1;
	}
	dist[src] = 0;
	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
	pq.push({0, src});
	while(!pq.empty()){
		pair<long long,int> p = pq.top();
		pq.pop();
		long long curr_dist = p.first;
		int curr_node = p.second;
		if(curr_dist != dist[curr_node])
			continue;
		for(auto edge : adj[curr_node]){
			int next_node = edge.first;
			long long edge_cost = edge.second;

			long long new_dist = curr_dist + edge_cost;
			if(new_dist < dist[next_node]){
				dist[next_node] = new_dist;
				parent[next_node] = curr_node;
				pq.push({new_dist, next_node});
			}
		}
	}
}	

void solve(){
	int n,m;
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int x,y;
		long long cst;
		cin >> x >> y >> cst;
		adj[x].push_back({y, cst});
		adj[y].push_back({x, cst});
	}
	int src = 1;
	dijsktra(src, n);
}
