#include<iostream>
#include<vector>
#include<math.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;

class Segment{
    int n;
    vector<int>num;
    vector<int>seg;
    vector<int>lazy;

    void build_util(int index,int l,int r){
        if(l==r){
            seg[index]=num[l];
            return;
        }
        int mid=(l+r)>>1;
        build_util(2*index+1,l,mid);
        build_util(2*index+2,mid+1,r);
        int left=seg[2*index+1];
        int right=seg[2*index+2];
        seg[index]=(left+right);
    }

    int query_util(int index,int low,int high,int l,int r){
        if(high<l||low>r) return 0;
        else if(low>=l && high<=r) return seg[index];
        
        int mid=(low+high)>>1;
        int left=query_util(2*index+1,low,mid,l,r);
        int right=query_util(2*index+2,mid+1,high,l,r);
        return (left+right);
    }

    void update_util(int index,int low,int high,int pnt,int val){
        if(low==high){
            seg[index]=val;
            return ;
        }
        
        int mid=(low+high)>>1;
        if(pnt<=mid) update_util(2*index+1,low,mid,pnt,val);
        else update_util(2*index+2,mid+1,high,pnt,val);

        int left=seg[2*index+1];
        int right=seg[2*index+2];

        seg[index]=(left+right);

    }

    void update_lazy_util(int index,int low,int high,int l,int r,int val){
        if(lazy[index]!=0){
            seg[index]+=(high-low+1)*lazy[index];
            
            if(low!=high){
                lazy[2*index+1]+=lazy[index];
                lazy[2*index+2]+=lazy[index];
            }
            lazy[index]=0;
        }

        if(high<l||low>r) return ;

        if(low>=l&&high<=r){
            seg[index]+=(high-low+1)*val;
            
            if(low!=high){
                lazy[2*index+1]+=val;
                lazy[2*index+2]+=val;
            }
            return;
        }

        int mid=(low+high)>>1;

        update_lazy_util(2*index+1,low,mid,l,r,val);
        update_lazy_util(2*index+2,mid+1,high,l,r,val);
        seg[index]=seg[2*index+1]+seg[2*index+2];
    }

    int query_lazy_util(int index,int low,int high,int l,int r){

        if(lazy[index]!=0){
            seg[index]+=(high-low+1)*lazy[index];
            if(low!=high){
                lazy[2*index+1]+=lazy[index];
                lazy[2*index+2]+=lazy[index];
            }
            lazy[index]=0;
        }

        if(high<l||low>r) return 0;
        else if(low>=l&&high<=r) return seg[index];
        int mid=(low+high)>>1;
        int left=query_lazy_util(2*index+1,low,mid,l,r);
        int right=query_lazy_util(2*index+2,mid+1,high,l,r);
        return left+right;
    }

    public:

    Segment(){}

    Segment(vector<int>nums){
        this->n=nums.size();
        this->num=nums;
        seg.resize(4*n,0);
        lazy.resize(4*n,0);
    }
    
    void build(vector<int>nums){
        this->n=nums.size();
        this->num=nums;
        seg.resize(4*n,0);
        lazy.resize(4*n,0);
        build_util(0,0,n-1);
    }

    int query(int l,int r){
        return query_util(0,0,num.size()-1,l,r);
    }

    void update(int point,int val){
        num[point]=val;
        update_util(0,0,num.size()-1,point,val);
    }

    void update_lazy(int l,int r,int val){
        update_lazy_util(0,0,num.size()-1,l,r,val);
    }

    int query_lazy(int l,int r){
        return query_lazy_util(0,0,num.size()-1,l,r);
    }

    void print(){
        for(auto i:seg)cout<<i<<" ";
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
    for(int i=0;i<n;i++){
        int temp;
        cin>>temp;
        nums.push_back(temp);
    }

    Segment sg;
    sg.build(nums);

    int q;cin>>q;
    while(q--){
        int type;cin>>type;
        if(type==1){
            int l,r;
            cin>>l>>r;
            cout<<sg.query_lazy(l,r)<<"\n";
        }else{
            int l,r,val;
            cin>>l>>r>>val;
            sg.update_lazy(l,r,val);
        }
    }

    return 0;
}