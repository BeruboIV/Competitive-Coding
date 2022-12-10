//1 based indexing is followed here
const int MAXN = 1e3;
int mat[MAXN + 1][MAXN + 1];
int BIT[MAXN + 1][MAXN + 1];
int n,m;

void update(int x, int y, int val){
	for(int i = x; i <= n; i += (i & (-i))){
		for(int j = y; j <= m; j += (j & (-j))){
			BIT[i][j] += val;
		}
	}
}

//Gets the sum of cells upto [x,y]
int getSum(int x, int y){
	int ret = 0;
	for(int i = x; i > 0; i -= (i & (-i))){
		for(int j = y; j > 0; j -= (j & (-j))){
			ret += BIT[i][j];
		}
	}
	return ret;
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> mat[i][j];
			update(i, j, mat[i][j]);
		}
	}
	int q;
	cin >> q;
	while(q--){
		int l,r;
		cin >> l >> r;
		cout << getSum(l, r) << "\n";
	}
}


/////////////////////////////////////////////////
//0 Based-Indexing BIT

const int N = 1e3;
int mat[N + 1][N + 1];
int BIT[N + 1][N + 1];
int n,m;

void update(int x, int y, int val){
	for(int i = x; i < n; i = (i | (i + 1)) ){
		for(int j = y; j < m; j = (j | (j + 1)) ){
			BIT[i][j] += val;
		}
	}
}

//Gets the sum of cells upto [x,y]
int getSum(int x, int y){
	int ret = 0;
	for(int i = x; i >= 0; i = (i & (i + 1)) - 1){
		for(int j = y; j >= 0; j = (j & (j + 1)) - 1){
			ret += BIT[i][j];
		}
	}
	return ret;
}

void solve(){
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> mat[i][j];
			update(i, j, mat[i][j]);
		}
	}
	int q;
	cin >> q;
	while(q--){
		int l,r;
		cin >> l >> r;
		l--, r--;
		cout << getSum(l, r) << "\n";
	}
}