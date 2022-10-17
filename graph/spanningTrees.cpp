#include<iostream>
#include<vector>
#include<set>
#include<unordered_map>
#include<queue>
#include<algorithm>
#include<unordered_set>
using namespace std;

void print(vector<int>a){
    for(auto i:a)cout<<i<<" ";
    cout<<"\n";
}

void print(vector<vector<int>>a){
    for(auto i:a){
        for(auto j:i) cout<<j<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

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

class Graph{
    int n;
    unordered_map<int,vector<pair<int,int>>> graph;
    public:

    Graph(){}

    Graph(int n,unordered_map<int,vector<pair<int,int>>>mp):n{n}{
        this->graph=mp;
    }

    void print(){
        for(auto root:graph){
            cout<<root.first<<"-> ";
            for(auto n:graph[root.first]){
                int node=n.first;
                int w=n.second;
                cout<<node<<"W"<<w<<" ";
            }
            cout<<"\n";
        }
    }

    vector<vector<int>> krushkals(){
        vector<vector<int>>edges,ans;
        DSU *ds=new DSU(n+1);

        ds->makeset();

        for(auto root:graph){
            for(auto n:graph[root.first]){
                edges.push_back({root.first,n.first,n.second});
            }
        }

        sort(edges.begin(),edges.end(),[](vector<int>&a,vector<int>&b){
            return a[2]<b[2];
        });

        for(auto edge:edges){
            int u=edge[0];
            int v=edge[1];
            if(ds->find(u)!=ds->find(v)){
                ans.push_back(edge);
                ds->unify(u,v);
            }
        }
        delete ds;
        return ans;
    }

    vector<vector<int>> prims(){
        vector<vector<int>>ans;
        vector<int>key(n+1,1e9);
        vector<bool>mst(n+1,false);
        vector<int>parent(n+1,-1);
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>pq;
        key[0]=0;
        pq.push({0,0});
        while(pq.size()){
            auto tp=pq.top();
            pq.pop();
            int root=tp[1];
            mst[root]=true;
            for(auto n:graph[root]){
                int node=n.first;
                int w=n.second;
                if(!mst[node]&&w<key[node]){
                    parent[node]=root;
                    key[node]=w;
                    pq.push({key[node],node});
                }
            }
        }
        for(int i=0;i<parent.size();i++){
            if(parent[i]!=-1)
                ans.push_back({i,parent[i],key[i]});
        }
        return ans;
    }

};


int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    int n;cin>>n;
    vector<vector<int>>edges;

    int N=-1e9;

    for(int i=0;i<n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        N=max(N,a);
        N=max(N,b);
        edges.push_back({a,b,c});
    }

    unordered_map<int,vector<pair<int,int>>> graph;
    for(auto edge:edges){
        graph[edge[0]].push_back({edge[1],edge[2]});
        graph[edge[1]].push_back({edge[0],edge[2]});
    }

    Graph g(N,graph);

    vector<vector<int>>ans1=g.krushkals();
    vector<vector<int>>ans2=g.prims();
    
    print(ans1);
    print(ans2);

    return 0;
}