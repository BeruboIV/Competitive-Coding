const int SIZE = 26;

struct Trie{
    Trie* children[SIZE];
    bool endOfWord;
};

// Returns a new Trie Node (Initialized to NULLs)
Trie* getNode(){
    Trie* node = new Trie;
    node->endOfWord = false;

    for(int i = 0; i < SIZE; i++){
        node->children[i] = NULL;
    }

    return node;
}

// Insert iteratively
void insert(Trie* root, string &str){
    Trie* temp = root;
    int sz = str.size();

    for(int i = 0; i < sz; i++){
        int idx = str[i] - 'a';
        if(temp->children[idx] == NULL) // If node does not exist, create a node
            temp->children[idx] = getNode();
        temp = temp->children[idx];
    }

    temp->endOfWord = true;
}

// Search iteratively
bool search(Trie* root, string&str){
    Trie* temp = root;
    int sz = str.size();

    for(int i = 0; i < sz; i++){
        int idx = str[i] - 'a';
        if(temp->children[idx] == NULL)
            return false;
        temp = temp->children[idx];
    }

    return (temp->endOfWord);
}


void solve(){
    Trie* root = getNode();
    
    // Insert : insert(root, str);
    // Search : search(root, str);
}