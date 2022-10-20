#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<math.h>
#include<unordered_map>

using namespace std;

void print(vector<vector<int>>a){
    for(auto i:a){
        for(auto j:i) cout<<j<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

void print(stack<int>st){
    while(st.size()){
        cout<<st.top()<<" ";
        st.pop();
    }
}

void print(vector<int>a){
    for(auto i:a) cout<<i<<" ";
    cout<<"\n";
}

class Graph{
    int n;
    unordered_map<int,vector<int>>graph;
    unordered_map<int,vector<int>>rgraph;
    public:
    Graph(){};
    Graph(int n,unordered_map<int,vector<int>>&mp,unordered_map<int,vector<int>>&rmp):n{n}{
        this->graph=mp;
        this->rgraph=rmp;
    }

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

    void dfs_util_scc(int root,vector<bool>&visited,vector<int>&st){
        visited[root]=true;

        if(graph.count(root))
            for(auto node:graph[root])
                if(!visited[node])
                    dfs_util_scc(node,visited,st);
        st.push_back(root);
    }

    void dfs_util_scc2(int root,vector<bool>&visited,vector<int>&temp){
        visited[root]=true;
        temp.push_back(root);
        if(rgraph.count(root))
            for(auto node:rgraph[root])
                if(!visited[node])
                    dfs_util_scc2(node,visited,temp);
    }

    vector<vector<int>> stronglyConnected(){
        vector<vector<int>>ans;
        vector<bool>visited(n+1,false);
        vector<int>st;

        for(auto root:graph) 
            if(!visited[root.first]) 
                dfs_util_scc(root.first,visited,st);

        for(int i=0;i<visited.size();i++) visited[i]=false;
        reverse(st.begin(),st.end());

        for(auto root:st){
            if(!visited[root]){
                vector<int>temp;
                dfs_util_scc2(root,visited,temp);
                ans.push_back(temp);
            }
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
    int N=-1e9;
    unordered_map<int,vector<int>>mp,rev;

    while(n--){
        int a,b;
        cin>>a>>b;
        N=max({N,a,b});
        mp[a].push_back(b);
        rev[b].push_back(a);
    }

    Graph g(N,mp,rev);
    vector<vector<int>>ans=g.stronglyConnected();

    print(ans);

    return 0;
}