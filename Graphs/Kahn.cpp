const int N = 5e5;
vector<int> adj[N + 1];
vector<int> res;
int in_degree[N + 1];

void kahn(int n){
	queue<int> q;
	//Use priority queue in case nodes have different priorities
	for(int i = 1; i <= n; i++){
		if(in_degree[i] == 0)
			q.push(i);
	}
	while(!q.empty()){
		int curr = q.front();
		q.pop();
		res.push_back(curr);
		for(int node : adj[curr]){
			in_degree[node]--;
			if(in_degree[node] == 0){
				q.push(node);
			}
		}
	}
	// return (res.size() == n);	// topological sort exists else it does not exist

}

void solve(){
	int n,m;
	cin >> n >> m;
	for(int i = 0; i <= n; i++){
		adj[i].clear();
		in_degree[i] = 0;
	}
	res.clear();
	for(int i = 0; i < m; i++){
		int x,y;
		cin >> x >> y;
		adj[x].push_back(y);
		in_degree[y]++;
	}
	kahn(n);
}
