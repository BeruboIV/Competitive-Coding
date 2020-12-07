vector<int> pi_table(string t){
	int n = t.length();
	vector<int> pi(n,0);
	int i = 1, j = 0;
	while(i < n){
		if(t[i] == t[j]){
			pi[i] = j + 1;
			j++;
			i++;
		}
		else{
			if(j != 0)
				j = pi[j - 1];
			else{
				i++;
			}
		}
	}
	return pi;
}

ll kmp(string s, string t){
	// s --> The text string(is the string which we look into for the pattern)
     //t --> Pattern String(is the pattern to be looked for in the string s)
	 vector<int> pi = pi_table(t);
     ll cnt = 0;
     int j = 0, i = 0;
     int n = s.length();
     int m = t.length();
     while(i < n){
     	if(s[i] == t[j]){
     		i++;
     		j++;
     	}
     	if(j == m){
     		cnt++;
     		j = 0; // For non-overlapping substrings
     		//j = pi[j-1]; // For over-lapping substrings
     	}
     	else if(i < n && s[i] != t[j]){
     		if(j != 0){
     			j = pi[j - 1];
     		}
     		else{
     			i++;
     		}
     	}
     }
     return cnt;
}