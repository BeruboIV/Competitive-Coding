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

bool isEmpty(Trie* root){
    for(int i = 0; i < SIZE; i++){
        if(root->children[i] != NULL)
            return false;
    }
    return true;
}

// depth -> str.size()
Trie* remove(Trie* root, string &str, int curr_depth, int depth){
    // If the trie is empty
    if(root == NULL)
        return NULL;

    // If last character is being processed
    if(curr_depth == depth){
        root->endOfWord = false;    // "unmark" the node

        //  If the current node is not the prefix of any other node, we can delete this node
        if(isEmpty(root)){
            delete (root);
            root = NULL;
        }       
        return root;
    }

    //  Recurse to the next letter/ node
    int idx = str[curr_depth] - 'a';

    // // If the node is not present
    // if(root->children[idx] == NULL){
    //     // Not needed as we are already checking root == NULL
    //     return NULL;
    // }

    root->children[idx] = remove(root->children[idx], str, curr_depth + 1, depth);

    if(isEmpty(root) && root->endOfWord == false){
        delete (root);
        root = NULL;
    } 

    return root;
}

void solve(){
    Trie* root = getNode();
    
    // Insert : insert(root, str);
    // Search : search(root, str);
    // Remove : remove(root, str, 0, (int)str.size());
}