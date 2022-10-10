#include<iostream>
#include<vector>
using namespace std;

class Heap{
    vector<int>nums;
    public:

    void insert(int num){
        nums.push_back(num);
        int i=nums.size()-1;
        while(i>1&&nums[i/2]>nums[i]){
            swap(nums[i/2],nums[i]);
            i=i/2;
        }
    }

    void print(){
        for(auto i:nums)cout<<i<<" ";
        cout<<"\n";
    }

};

int main(){
    Heap h;
    vector<int>nums{1,2,3,4,5};
    for(auto i:nums) h.insert(i);
    h.print();
    return 0;
}