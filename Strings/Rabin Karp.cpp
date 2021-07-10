vector<int> rabin_karp(string const& s, string const& t) {
    const long long P = 31; 
    const long long MOD = 1e9 + 7;
    int S = s.size(), T = t.size();

    vector<long long> prime_pow(max(S, T)); 
    prime_pow[0] = 1; 
    int n = prime_pow.size();
    for (int i = 1; i < n; i++) 
        prime_pow[i] = (prime_pow[i - 1] * P) % MOD;

    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i + 1] = (h[i] + (t[i] - 'a' + 1) * prime_pow[i]) % MOD; 
    long long h_s = 0; 
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * prime_pow[i]) % MOD; 

    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++) { 
        long long cur_h = (h[i + S] - h[i] + MOD) % MOD; 
        if (cur_h == h_s * prime_pow[i] % MOD)
            occurences.push_back(i);
    }
    return occurences;
}