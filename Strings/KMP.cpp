vector<int> prefix_function(const string &s) {
    int n = (int)s.length();
    vector<int> pi(n, 0);
    pi[0] = 0;

    for (int i = 1; i < n; i++) {
        pi[i] = 0;
        int j = pi[i - 1];    /* trying length j + 1 */
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}


vector<int> kmp_find_matches(const string &text, const string &pat){
    //  text --> The text string(is the string which we look into for the pattern)
    //  pat --> Pattern String(is the pattern to be looked for in the text string "text")
    int n = pat.length(), m = text.length();
    string s = pat + "$" + text;
    vector<int> pi = prefix_function(s), ans;

    for (int i = n + 1; i <= n + m; i++) { /* n + 1 is where the text starts */
        if (pi[i] == n) {
            ans.push_back(i - 2 * n); /* i - (n - 1) - (n + 1) */
        }
    }
    
    return ans;
}

// Question 1: https://www.spoj.com/problems/NAJPF/
// Solution 1: https://ideone.com/pKifdk