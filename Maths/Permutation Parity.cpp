// 0 based indexing: numbers should be between [0, N - 1]
// N -> size of array
// p -> permutation array
// NOTE: ALL ELEMENTS SHOULD BE DISTINCT
bool parity(const vector<int> &p) {
    int parity = 0;
    int n = p.size();
    vector<bool> visited(n);

    for(int curr_node = 0; curr_node < n; curr_node++){
        if(visited[curr_node])
            continue;
        int cycle_size = 0;
        for (int next_node = curr_node; cycle_size == 0 || next_node != curr_node; next_node = p[next_node]) {
            cycle_size++;
            visited[next_node] = true;
        }

        parity += cycle_size + 1;
        parity %= 2;
    }
    return parity;
}