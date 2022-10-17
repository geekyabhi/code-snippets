#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

void print(vector<int>a){
    for(auto i:a) cout<<i<<" ";
    cout<<"\n";
}

void print(vector<int>a,int l,int r){
    for(int i=l;i<=r;i++) cout<<a[i]<<" ";
    cout<<"\n";
}

class Graph{
    int n;
    unordered_map<int,vector<int>>graph;

    public:

    Graph(){}

    Graph(int n,unordered_map<int,vector<int>>&mp):n{n}{graph=mp;}

    void print(){
        for(auto root:graph){
            cout<<root.first<<"->";
            for(auto node:root.second) cout<<node<<" ";
            cout<<"\n";
        }
    }

    
    void dfs1(int root,int parent,int &time,vector<int>&timein,vector<int>&timeout){
        timein[root]=time++;
        for(auto node:graph[root]){
            if(node!=parent) dfs1(node,root,time,timein,timeout);
        }
        timeout[root]=time++;
    }
    
    void dfs2(int root,int parent,int &time,vector<int>&timein,vector<int>&timeout){
        timein[root]=++time;
        for(auto node:graph[root]){
            if(node!=parent) dfs2(node,root,time,timein,timeout);
        }
        timeout[root]=time;
    }

    pair<vector<int>,vector<int>> euler1(int src){
        vector<int>timein(n+1,0);
        vector<int>timeout(n+1,0);
        int time=1;
        dfs1(src,-1,time,timein,timeout);
        // ::print(timein,1,n);
        // ::print(timeout,1,n);
        return {timein,timeout};
    }
    
    vector<int> euler2(int src){
        vector<int>timein(n+1,0);
        vector<int>timeout(n+1,0);
        vector<int>flat(n+1,0);
        int time=0;
        dfs2(src,-1,time,timein,timeout);
        // ::print(timein,1,n);
        // ::print(timeout,1,n);
        for(int i=0;i<timein.size();i++){
            flat[timein[i]]=i;
        }
        return flat;
    }

};


int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    int n;cin>>n;
    int N=0;
    unordered_map<int,vector<int>>mp;
    while(n--){
        int a,b;cin>>a>>b;
        N=max({N,a,b});
        mp[a].push_back(b);
        mp[b].push_back(a);
    }

    Graph g(N,mp);

    vector<int>ans=g.euler2(1);
    print(ans);
    return 0;
}