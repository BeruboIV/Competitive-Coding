struct edge{
	int from, to, cost;
};

int n,m,S;
vector<edge> e;
const int INF = 9999;

vector<int> bellman(){
	vector<int> dist(n, INF);
	dist[S] = 0;
	for(int i = 0; i < n - 1; i++){
		bool flag = false; //For optimization
		for(int j = 0; j < m; j++){
			if(dist[e[j].from] < INF){
				if(dist[e[j].to] > dist[e[j].from] + e[j].cost){
					flag = true;
					dist[e[j].to] = dist[e[j].from] + e[j].cost;
				}
			}
		}
		if(!flag)
			break;
	}
	return dist;
}	

void solve(){
	cin >> n >> m >> S;
	//n --> Number of vertices
	//m --> Number of edges
	//S --> Starting vertex
	for(int i = 0; i < m; i++){
		edge temp;
		cin >> temp.from >> temp.to >> temp.cost;
		e.push_back(temp);
	}
	vector<int> dist = bellman();
	for(int x : dist)
		cout << x << "\n";
}

/*
Sample Input
9 10 0
0 1 1
1 2 1
2 4 1
4 3 -3
3 2 1
1 5 4
1 6 4
5 6 5
6 7 4
5 7 3
*/

/*
Sample Output
0
1
-6
-7
-4
5
5
8
9999
9999
*/