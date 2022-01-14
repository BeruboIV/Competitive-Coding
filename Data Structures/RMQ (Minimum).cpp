
// Note: 0 based indexing is followed here
template <typename T = long long>
class RMQ{

public:
    int N = 2e5;
    vector<int> LOG2;    //Quick lookup table for floor(log2(i)), 1 <= i <= N
    vector<T> dp[26];    //dp[i][j] = [j, j + (1 << i) ) --> Notice the open interval
    vector<T> arr;

    RMQ(){
        LOG2.resize(N + 1);
        arr.resize(N + 1);
        for(int i = 0; i < 26; i++){
            dp[i].resize(N + 1);
        }

        for(int i = 2; i <= N; i++)
            LOG2[i] = 1 + LOG2[i/2];
    }

    RMQ(int N)
        : N(N){
        LOG2.resize(N + 1);
        arr.resize(N + 1);
        for(int i = 0; i < 26; i++){
            dp[i].resize(N + 1);
        }
        
        for(int i = 2; i <= N; i++)
            LOG2[i] = 1 + LOG2[i/2];
    }

    RMQ (vector<T> &a){
        N = (a.empty() ? N : a.size());
        LOG2.resize(N + 1);
        arr.resize(N + 1);
        for(int i = 0; i < 26; i++){
            dp[i].resize(N + 1);
        }

        for(int i = 2; i <= N; i++)
            LOG2[i] = 1 + LOG2[i/2];

        if(!a.empty())
            build(a);
    }

    void build(vector<T> &a){
        int n = a.size();
        for(int i = 0; i < n; i++)
            arr[i] = a[i];

        //Filling first row
        for(int i = 0; i < n; i++){
            dp[0][i] = i;
        }

        // Note: Breaks ties by choosing the largest index
        int P = LOG2[n];
        for(int p = 1; p <= P; p++){
            for(int i = 0; i + (1 << p) <= n; i++){
                T left = dp[p - 1][i];
                T right = dp[p - 1][i + (1 << (p - 1))];
                if(arr[left] < arr[right])
                    dp[p][i] = left;
                else
                    dp[p][i] = right;

            }
        }
    }

    //Query the smallest element in the range [l, r], O(1)
    T query_val(int l, int r){
        if(l > r){
            return 1e18;
        }
        int len = r - l + 1;
        int p = LOG2[len];
        T left = arr[dp[p][l]];
        T right = arr[dp[p][r - (1 << p) + 1]];
        return min(left, right);
    }

    //Query the smallest element in the range [l, r] by doing
    //a cascading min query, O(log2(n));
    //This function can be used to return sum of ranges also
    T CascadingQuery(int l, int r){
        T min_val = 1e18;
        for(int p = LOG2[r - l + 1]; l <= r; p = LOG2[r - l + 1]){
            min_val = min(min_val, arr[dp[p][l]]);
            l += (1 << p);
        }
        return min_val;
    }

    int query_idx(int l, int r){
        if(l > r){
            return N + 1;
        }
        int len = r - l + 1;
        int p = LOG2[len];
        int left = dp[p][l];
        int right = dp[p][r - (1 << p) + 1];
        return (arr[left] < arr[right] ? left : right);
    }

};

void solve(){
    int n;
    cin >> n;

    vector<long long> arr(n);
    for(auto &x : arr)
        cin >> x;

    RMQ<long long> rmq(arr);

    int q;
    cin >> q;
    while(q--){
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << rmq.query_val(l, r) << "\n";
    }
}