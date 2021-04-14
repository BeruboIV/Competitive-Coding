const int N = 2e5 + 10;
int parent[N], sz[N];

// Note always call findParent() method because union node changes the 
// root element
int findParent(int i){
	if(parent[parent[i]] != parent[i])
		parent[i] = findParent(parent[i]);
	return parent[i];
}

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


// Another implementation
/*
const int maxn = 2e5 + 5;
int sz[maxn], parent[maxn];
int findParent(int x)
{
    if(parent[x] == x)
        return x;
    return parent[x] = findParent(parent[x]);
}
 
// 0 --> If the nodes were already connected
// 1 --> If the nodes are now connected
int unionNodes(int u, int v)
{
    u = findParent(u);
    v = findParent(v);
    if(u != v)
    {
        if(sz[u] < sz[v])
            swap(u, v);
        parent[v] = u;
        sz[u] += sz[v];
        return 1;
    }
    return 0;
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
*/