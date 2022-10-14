#include<iostream>
#include<vector>

using namespace std;

class Fen{
    int n;
    vector<int>fen;
    vector<int>a;
    public:

    Fen(int size){
        this->n=size+1;
        fen.resize(n,0);
        a.resize(size,0);
    }

    Fen(vector<int>nums){
        this->a=nums;
        this->n=nums.size()+1;
        fen.resize(n,0);
    }

    void build(){
        for(int i=0;i<a.size();i++)
            update(i,a[i]);
    }

    void update(int index,int val){
        index++;
        while(index<n){
            fen[index]+=val;
            index=index+(index&(-index));
        }
    }

    int query(int index){
        index++;
        int sum=0;
        while(index>0){
            sum+=fen[index];
            index=index-(index&(-index));
        }
        return sum;
    }

    int query(int l,int r){
        if(l>0) return query(r)-query(l-1);
        return query(r);
    }

    void print(){
        for(auto i:fen) cout<<i<<" ";
        cout<<"\n";
    }

};

int main(){
    
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    int n;cin>>n;
    vector<int>nums;

    int mx=INT16_MIN;

    for(int i=0;i<n;i++){
        int t;cin>>t;
        nums.push_back(t);
    }


    for(auto i:nums)
        if(mx<i) mx=i;

    vector<int>t(mx+1,0);

    for(int i=0;i<nums.size();i++){
        t[nums[i]]++;
    }

    // for(auto i:t) cout<<i<<" ";
    // cout<<"\n";

    vector<int>ans(nums.size(),0);

    Fen fn(t);
    fn.build();

    for(int i=0;i<nums.size();i++){
        ans[i]=fn.query(nums[i]-1);
        fn.update(nums[i],-1);
    }

    for(auto i:ans) cout<<i<<" "; 

    return 0;
}