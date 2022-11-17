const static int ALPHABETS = 26;
const static char FIRST_ALPHABET = 'a';
class Node{
public:
    Node *children[ALPHABETS];
    int sz = 0;
    int endOfWord = 0;

    Node(){
        for(int i = 0; i < ALPHABETS; i++)
            children[i] = NULL;
        sz = 0;
        endOfWord = 0;
    }
};

class Trie{
public:
    Node *root;
    Trie(){
        root = new Node();
    }

    void insert(const string &str){
        Node *curr = root;
        curr->sz++;
        int sz = str.size();
        for(int i = 0; i < sz; i++){
            int idx = str[i] - FIRST_ALPHABET;
            if(curr->children[idx] == NULL)
                curr->children[idx] = new Node();
            curr = curr->children[idx];
            curr->sz++;
        }

        curr->endOfWord++;
    }

    bool find(const string &str){
        Node *curr = root;
        int sz = str.size();
        for(int i = 0; i < sz; i++){
            int idx = str[i] - FIRST_ALPHABET;
            if(curr->children[idx] == NULL)
                return false;
            curr = curr->children[idx];
        }

        return (curr->endOfWord);
    }

    bool isEmpty(Node* node){
        for(int i = 0; i < ALPHABETS; i++){
            if(node->children[i] != NULL)
                return false;
        }
        return true;
    }

    Node* remove_helper(Node *node, const string &str, int depth = 0){
        // If trie node is empty
        if(node == NULL)
            return NULL;
        node->sz--;

        // Last bit is being processed
        if(depth == str.size()){
            // Remove the single occurence
            cerr << node->endOfWord;
            if(node->endOfWord > 0){
                node->endOfWord--;
            }

            // If give is not prefix of any other number
            if(isEmpty(node)){
                cerr << "YO\n";
                delete(node);
                return NULL;
            }
            return node;
        }

        // If not 0th bit, recur for the child
        int idx = str[depth] - FIRST_ALPHABET;
        node->children[idx] = remove_helper(node->children[idx], str, depth + 1);

        // If trie node does not have any child (its only child got deleted),
        // and it is not end of another number
        if(isEmpty(node) && node->endOfWord == 0){
            delete (node);
            return NULL;
        }

        return node;
    }

    void remove(const string &str){
        if(!find(str))
            return;

        Node *curr = root;
        remove_helper(curr, str);
    }

};