const int N = 6e5 + 10;
int parent[N], sz[N];

/* If parent[i] = -1 for all i <= N
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

OR

int findParent(int a){
	if(parent[a] == -1)
		return a;
	return parent[a] = findParent(parent[a]);
}
*/

int findParent(int i){
	if(parent[parent[i]] != parent[i])
		parent[i] = findParent(parent[i]);
	return parent[i];
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

	return;
}

void clearDSU(int n){
	for(int i = 0; i <= n; i++){
		parent[i] = i;
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
	cout << "\n";
	// For printing the size of each component
	for(int i = 1; i <= n; i++){
		int p = parent[i];
		cout << sz[p] << " ";
	}
}

// Question: https://www.codechef.com/problems/CNCTCT?tab=statement
// Solution: https://www.codechef.com/viewsolution/81320820