#include<iostream>
#include<unordered_map>
#include<vector>
#include<math.h>
#include<algorithm>

using namespace std;

void print(vector<int>a){
    for(auto i:a) cout<<i<<" ";
    cout<<"\n";
}

void print(vector<vector<int>>a){
    for(auto i:a){
        for(auto j:i)cout<<j<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

class Graph{
    int n;
    unordered_map<int,vector<int>>graph;
    public:

    Graph(){}
    Graph(int n,unordered_map<int,vector<int>>&mp):n{n}{graph=mp;}

    void dfs_util_bf(int root,int par,vector<int>&depth,vector<int>&parent){
        parent[root]=par;
        depth[root]=depth[par]+1;
        for(auto node:graph[root])
            if(node!=par)
                dfs_util_bf(node,root,depth,parent);
    }

    // Total complexity for one query is O(n) and for q queries O(qn)

    int lca_bf(int u,int v){
        if(u==v) return u;
        int root=1,par=-1;
        vector<int>depth(n+1,0);
        vector<int>parent(n+1,-1);
        dfs_util_bf(root,par,depth,parent);

        if(depth[u]<depth[v]) swap(u,v);

        int diff=depth[u]-depth[v];

        while(diff--) u=parent[u];
        while(u!=v) u=parent[u],v=parent[v];

        return u;
    }
    
    
    //#################################################################################



    void dfs_util_lft(int root,int par,vector<vector<int>>&sparse,vector<int>&depth){
        sparse[root][0]=par;
        depth[root]=par<0?0:depth[par]+1;
        for(int j=1;j<sparse[0].size();j++)
            sparse[root][j]=sparse[root][j-1]==-1?sparse[0][j-1]:sparse[sparse[root][j-1]][j-1];

        for(auto node:graph[root])
            if(node!=par)
                dfs_util_lft(node,root,sparse,depth);
    }

    //Total time complexity for precomputation is O(nm) and for each query O(m) wheere m = log(n)

    int lca_lft(int u,int v){
        int m=ceil(log(n));
        vector<vector<int>>sparse(n+1,vector<int>(m+1,-1));
        vector<int>depth(n+1,0);
        dfs_util_lft(1,-1,sparse,depth);
        if(u==v) return u;
        if(depth[u]<depth[v]) swap(u,v);

        int diff=depth[u]-depth[v];

        for(int j=m-1;j>=0;j--){
            if(diff&(1<<j)){
                u=sparse[u][j];
            }
        }

        for(int j=m-1;j>=0;j--){
            if(sparse[u][j]!=sparse[v][j]){
                u=sparse[u][j];
                v=sparse[v][j];
            }
        }

        return sparse[u][0];
    }

};

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    int n;cin>>n;
    int N=-1e9;
    unordered_map<int,vector<int>>mp;
    while(n--){
        int a, b;
        cin>>a>>b;
        N=max({N,a,b});
        mp[a].push_back(b);
        mp[b].push_back(a);
    }

    Graph g(N,mp);

    cout<<g.lca_lft(9,12);
    cout<<g.lca_lft(10,8);
    cout<<g.lca_lft(9,11);

    return 0;
}
