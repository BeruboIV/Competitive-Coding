const int INF = INT_MAX;

// Longest non-decreasing subsequence.
vector<int> LNDS(vector<int> A, bool rev){
    if(rev)
        reverse(a.begin(), a.end());

    int N = A.size();

    vector<int> lenLNDS(N, 1);  // Length of LNDS ending with Ai

    map<int, int> last; // last[ele] = index of last processed ele

    vector<int> d(N + 1, INF);
    d[0] = -INF;

    for(int i = 0; i < N; i++){
        int j = upper_bound(d.begin(), d.end(), A[i]) - d.begin();
        if(A[i] < d[j])
            d[j] = A[i];

        lenLNDS[i] = j;

        last[A[i]] = i;
    }

    if(rev){
        reverse(lenLNDS.begin(), lenLNDS.end());
    }

    return lenLNDS;
}

// Longest non-increasing subsequence
vector<vector<int>> LNIS(vector<int> A, bool rev){
    // flipping sign of all elements will make LNIS of
    // original array equal to LNDS of flipped array.
    for(int &x : A)
        x = -x;

    return LNDS(A, rev);
}