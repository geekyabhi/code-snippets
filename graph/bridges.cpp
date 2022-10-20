#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

void print(vector<int>&a){
    for(auto i:a) cout<<i<<" ";
    cout<<"\n";
}

void print(vector<vector<int>>&a){
    for(auto i:a){ 
        for(auto j:i) cout<<j<<" ";
        cout<<"\n";
    }
}

class Graph{
    int n;
    unordered_map<int,vector<int>>graph;
    public:
    Graph(int n,unordered_map<int,vector<int>>&mp):n{n}{this->graph=mp;}

    void print(){
        for(auto root:graph){
            cout<<root.first<<"-> ";
            for(auto n:graph[root.first]){
                int node=n;
                cout<<node<<" ";
            }
            cout<<"\n";
        }
    }

    void dfs_util(int root,int par,vector<int>&timein,vector<int>&low,vector<vector<int>>&ans){
        static int time=0;
        timein[root]=low[root]=time++;

        for(auto node:graph[root]){
            if(node==par){ 
                continue;
            }else if(timein[node]!=-1){
                low[root]=min(low[root],low[node]);
            }else{
                dfs_util(node,root,timein,low,ans);
                low[root]=min(low[root],low[node]);
                if(low[node]>timein[root]) ans.push_back({root,node});
            }
        }
    }


    vector<vector<int>> bridges(){
        vector<int>timein(n+1,-1),low(n+1,-1);
        vector<vector<int>>ans;

        for(auto root:graph)
            if(timein[root.first]==-1)
                dfs_util(root.first,-1,timein,low,ans);

        return ans;
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

    Graph *g;

    while(n--){
        int a,b;cin>>a>>b;
        N=max({N,a,b});
        mp[a].push_back(b);
        mp[b].push_back(a);
    }

    g=new Graph(N,mp);

    vector<vector<int>>ans=g->bridges();

    print(ans);

    return 0;
}