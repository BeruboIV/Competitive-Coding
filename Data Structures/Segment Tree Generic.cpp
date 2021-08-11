const int32_t maxn = 2e5;

template<typename T = long long>
class SegmentTree{
private:
public:
    T t[2 * maxn];
    int32_t n;  // array size

    SegmentTree(){ }

    SegmentTree(int32_t n)
        :n(n){ }

    void input(){
        // Values are stored at index n, n + 1, n + 2, ..., n + (n - 1)
        for(int32_t i = 0; i < n; i++){
            t[i] = 0;
            cin >> t[n + i];
        }
    }

    // Change this as per requirement
    void merge(T &node_val, const T &val1, const T &val2){
        node_val = val1 + val2;
        // node_val __gcd(val1, val2);
        // node_val = max(val1, val2);
    }

    void updateNode(T &node_val, const T &new_val){ // Changes only the node value
        node_val += val;
        // node_val = val;
    }

    void build(){   // build the tree
        for(int32_t i = n - 1; i > 0; --i){
            merge(t[i], t[i << 1], t[i << 1 | 1]);
        }
    }

    void modify(int32_t p, T value){  // Updates the tree
        updateNode(t[p += n], value);   // Set value at position p
        for(; p > 1; p >>= 1){
            merge(t[p >> 1], t[p], t[p ^ 1]);
        }
    }

    T queryRange(int32_t l, int32_t r){  // query on interval [l, r)
        T res = ;   
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l&1){
                merge(res, res, t[l++]);
            }
            if(r&1){
                merge(res, res, t[--r]);
            }
        }

        return res;
    }
};

SegmentTree<long long> seg;

void solve(){
    int n;
    cin >> n;
    seg.n = n;
    seg.input();
    // To get array values, use seg.t[n + i]
    seg.build();
    cout << seg.queryRange(3, 5);
}