# include<iostream>
# include<vector>
# include<string>
using namespace std;

class Node{
    public:
    Node*child[26];
    bool flag;

    Node(){
        flag=false;
    }

    bool contains_key(char ch){
        return child[ch-'a']!=nullptr;
    }

    void put(char ch,Node* node){
        child[ch-'a']=node;
    }

    Node* get(char ch){
        return child[ch-'a'];
    }

    bool set_end(){
        return flag=true;
    }

    bool is_end(){
        return flag;
    }

};

class Trie{
    public:
    Node*root;
    Trie(){
        root=new Node();
    }

    void insert(string word){
        Node* node=root;
        for(int i=0;i<word.size();i++){
            if(!node->contains_key(word[i])){
                node->put(word[i],new Node());
            }
            node=node->get(word[i]);
        }
        node->set_end();
    }

    bool search(string word){
        Node*node=root;
        for(int i=0;i<word.size();i++){
            if(!node->contains_key(word[i])){
                return false;
            }
            node=node->get(word[i]);
        }
        return node->is_end(); 
    }

    bool start_with(string pre){
        Node*node=root;
        for(int i=0;i<pre.size();i++){
            if(!node->contains_key(pre[i])){
                return false;
            }
            node=node->get(pre[i]);
        }
        return true;
    }


};

int main()
{
	int n = 5;
	vector<int>type = {1, 1, 2, 3, 2};
	vector<string>value = {"hello", "help", "help", "hel", "hel"};
	Trie trie;
	for (int i = 0; i < n; i++) {
		if (type[i] == 1) {
			trie.insert(value[i]);
		}
		else if (type[i] == 2) {
			if (trie.search(value[i])) {
				cout << "true" << "\n";
			}
			else {
				cout << "false" << "\n";
			}
		}
		else {
			if (trie.start_with(value[i])) {
				cout << "true" << "\n";
			}
			else {
				cout << "false" << "\n";
			}
		}
	}
    return 0;
}