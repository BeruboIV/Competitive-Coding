const int N = 1e5;
int parent[N + 1], sz[N + 1];

int findParent(int a){
	vector<int> nodes;
	while(parent[a] > 0){
		nodes.push_back(a);
		a = parent[a];
	}

	for(int node : nodes)
		parent[node] = a;
	return a;
}

void unionNodes(int a, int b){
	int parent_a = findParent(a);
	int parent_b = findParent(b);

	if(parent_a == parent_b)
		return;

	if(sz[parent_a] > sz[parent_b]){
		//a would be parent
		parent[parent_b] = parent_a;
		sz[parent_a] += sz[parent_b];
	}
	else{
		//b would be parent
		parent[parent_a] = parent_b;
		sz[parent_b] += sz[parent_a];
	}

}

void clearDSU(int n){
	for(int i = 0; i <= n; i++){
		parent[i] = -1;
		sz[i] = 1;
	}
}

void solve(){
	int n;
	cin >> n;
	clearDSU(n);
	int q;
	cin >> q;
	while(q--){
		int a, b;
		cin >> a >> b;
		unionNodes(a, b);
	}
	for(int i = 1; i <= n; i++)
		cout << parent[i] << " ";
}