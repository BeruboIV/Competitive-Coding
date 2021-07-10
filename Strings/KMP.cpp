vector<int> pi_table(const string &p){
    int n = p.size();
    vector<int> pi(n,0);
    int i = 0, j = 1;
    while(j < n){
        if(p[i] == p[j]){
            pi[j] = i + 1;
            j++;
            i++;
        }
        else{
            if(i != 0)
                i = pi[i - 1];
            else{
                j++;
            }
        }
    }
    return pi;
}

long long kmp(const string &t, const string &p){
    //  t --> The text string(is the string which we look into for the pattern)
    //  p --> Pattern String(is the pattern to be looked for in the string s)
     vector<int> pi = pi_table(p);
     long long cnt = 0;
     int j = 0, i = 0;
     int m = t.size();
     int n = p.size();
     while(j < m){
         if(t[j] == p[i]){
             i++;
             j++;
         }
         if(i == n){
             cnt++;
             i = 0; // For non-overlapping substrings
             // i = pi[i-1]; // For over-lapping substrings
         }
         else if(j < n && t[j] != p[i]){
             if(i != 0){
                 i = pi[i - 1];
             }
             else{
                 j++;
             }
         }
     }
     return cnt;
}