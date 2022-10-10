#include<iostream>

using namespace std;

class Node{
    public:
    int val,lazy;
    Node*left,*right;
    Node():val(0),lazy(0),left(nullptr),right(nullptr){}

    void extend(){
        if(left==nullptr) left=new Node();
        if(right==nullptr) right=new Node();
    }

};

class Seg {
public:
    Node* root;
    int n;
    
    Seg(int n): n(n) {
        root = new Node();
    }
    
    void update_lazy_util(Node* node,int low,int high,int l,int r,int val) {
        if(node->lazy) {
            node->val+=node->lazy;
            if(low!=high) { 
                node->extend();
                node->left->lazy+=node->lazy;
                node->right->lazy+=node->lazy;
            }
            node->lazy=0;
        }
        
        if(low>r || high<l) return;
        
        if(low>=l && high<=r) {
            node->val+=val;
            if(low!=high) {
                node->extend();
                node->left->lazy+=val;
                node->right->lazy+=val;
            }
            return;
        }
        
        int m=(low+high)/2;

        node->extend();
        update_lazy_util(node->left,low,m,l,r,val);
        update_lazy_util(node->right,m+1,high,l,r,val);
        node->val=max(node->left->val, node->right->val);
    }
    
    void update(int l,int r, int val) {
        update_lazy_util(root,1,n,l,r,val);
    }
    
    int query_lazy_util(Node* node,int low,int high,int l, int r) {
         if(node->lazy) {
            node->val+=node->lazy;
            if(low!=high) { 
                node->extend();
                node->left->lazy+=node->lazy;
                node->right->lazy+=node->lazy;
            }
            node->lazy=0;
        }
        
        if(low>r || high < l) {
			return 0;
		}
        
        if(low>=l && high<=r) {
            return node->val;
        }
        
        int mid=(low+high)/2;
        node->extend();
        int left=query_lazy_util(node->left,low,mid,l,r);
        int right=query_lazy_util(node->right,mid+1,high,l,r);
        return max(left,right);
    }

    int query(int l,int r) {
        return query_lazy_util(root,1,n,l,r);
    }

};

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    return 0;
}