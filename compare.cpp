#include<stdio.h>
#include<vector>
#include<set>
#include<iostream>
using namespace std;
int main(){
    FILE *Dhruv=fopen("OutliersEEG","r");
    FILE *Dip=fopen("Rsvm","r");
    int num;
    vector<int> V1,V2;
    while(fscanf(Dhruv,"%d",&num)!=EOF){
        V1.push_back(num);
    }
    while(fscanf(Dip,"%d",&num)!=EOF){
        V2.push_back(num);
    }
    int cc=0;
    for(int i=0 ; i<V1.size() ; i++){
        for(int j=0 ; j<V2.size() ; j++){
            if(V1[i]+1==V2[j])
                cc++;
        }
    }
    printf("Size of Vector1 %d\nSize of Vector2 %d\n",V1.size(),V2.size());
    cout<<cc<<endl;
    return 0;
}
