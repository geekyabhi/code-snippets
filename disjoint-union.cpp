#include<iostream>
#include<vector>

using namespace std;

class DSU{
    public:
    int n;
    vector<int>parent;
    vector<int>rank;
    
    DSU(){}
    
    DSU(int n){
        this->n=n;
        parent.resize(n);
        rank.resize(n,0);
    }
    
    void make(int v){
        parent[v]=v;
        rank[v]=0;
    }
    
    void makeset(){
        for(int i=0;i<n;i++) make(i);
    }
    
    int find(int v){
        if(parent[v]==v) return v;
        return parent[v]=find(parent[v]);
    }
    
    void unify(int a,int b){
        a=find(a);
        b=find(b);
        if(rank[a]<rank[b]) parent[a]=b;
        else if(rank[b]<rank[a]) parent[b]=a;
        else parent[a]=b,rank[b]++; 
    }
};

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    return 0;
}