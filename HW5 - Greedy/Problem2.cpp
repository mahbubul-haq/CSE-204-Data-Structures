#include<iostream>
using namespace std;

pair<int,int> pairArray[10000];

void merg(int low,int mid,int high){
    pair<int,int>tempArray[10000];

    int i,j,k;

    for(i=low,j=mid+1,k=low;i<=mid&&j<=high;k++){
        if(pairArray[i].first<=pairArray[j].first){
            tempArray[k]=pairArray[i];
            i++;
        }
        else tempArray[k]=pairArray[j++];
    }

    while(i<=mid){
        tempArray[k++]=pairArray[i++];
    }
    while(j<=high){
        tempArray[k++]=pairArray[j++];
    }

    for(int i=low;i<=high;i++){
        pairArray[i]=tempArray[i];
    }

}


void msort(int low,int high){
    if(low<high){
        int mid=(low+high)/2;

        msort(low,mid);
        msort(mid+1,high);
        merg(low,mid,high);
    }
}

int main(){

    int n;
    cin>>n;

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        pairArray[i].first=x;
        pairArray[i].second=i+1;
    }

    msort(0,n-1);

    for(int i=0;i<n;i++){
        cout<<pairArray[i].second<<" ";
    }
    cout<<endl;

    return 0;
}
