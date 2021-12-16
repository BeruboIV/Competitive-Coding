template<typename T>
void coordinate_compress(vector<T> &arr, map<int, T> &rev_idx){
    set<T> distinct;    // To get the sorted order
    for(T x : arr)
        distinct.insert(x);

    int Timer = 0;
    map<T, int> forward_idx;
    for(T x : distinct){
        forward_idx[x] = Timer;
        rev_idx[Timer] = x;
        Timer++;
    }

    for(T &x : arr){
        x = forward_idx[x];
    }

}