#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;

pair<int,int> xyarray[100000];
bool dom[100000];
int n;

void merg(int low,int mid,int high){
    int l,h,m,i;
    pair<int,int> tempara[100000];
    int ymin=INT_MAX,xmin=INT_MAX;

    for(l=low,h=mid+1,i=low;l<=mid&&h<=high;i++){
        if(xyarray[l].first<xyarray[h].first){
            tempara[i]=xyarray[l];
            l++;

        }
        else if(xyarray[l].first==xyarray[h].first){
            if(xyarray[l].second<=xyarray[h].second){
                tempara[i]=xyarray[l++];
            }
            else{
                tempara[i]=xyarray[h++];
            }
        }

         else tempara[i]=xyarray[h++];

//         if(tempara[i].second<ymin){
//            xmin=min(tempara[i].first,xmin);
//            ymin=min(tempara[i].second,ymin);
//        }
//        else if(tempara[i].second>ymin){
//            dom[i]=true;
//        }
//        else if(tempara[i].second==ymin&&tempara[i].first>xmin){
//            dom[i]=true;
//        }
//        else if(tempara[i].second==ymin&&tempara[i].first=xmin){
//            dom[i]=dom[i-1];
//        }
    }

    while(l<=mid){
        tempara[i++]=xyarray[l++];
    }

    while(h<=high){
        tempara[i++]=xyarray[h++];
    }

    for(i=low;i<=high;i++){
            xyarray[i]=tempara[i];
    }

    for(int iii=low;iii<=high;iii++){

        if(tempara[iii].second<ymin){
            xmin=min(tempara[iii].first,xmin);
            ymin=min(tempara[iii].second,ymin);
        }
        else if(tempara[iii].second>ymin){
            dom[tempara[iii].first]=true;
            dom[tempara[iii].second]=true;
        }
        else if(tempara[iii].second==ymin){
            if(tempara[iii].first>xmin){
                dom[tempara[iii].first]=true;
                dom[tempara[iii].second]=true;
            }
            else if(tempara[iii].first==xmin){
                    if(iii!=0){
                        dom[tempara[iii].first]=dom[tempara[iii-1].first];
                        dom[tempara[iii].second]=dom[tempara[iii-1].second];
                    }
            }
        }
    }
}

void msort(int low,int high){
    int mid;
    if(low<high){
        mid=(low+high)/2;
        msort(low,mid);
        msort(mid+1,high);
        merg(low,mid,high);
    }
    else return;
}

int main(){

    cin>>n;
    for(int i=0;i<n;i++){
       int a,b;
       cin>>a>>b;
       xyarray[i].first=a;
       xyarray[i].second=b;
    }

    msort(0,n-1);

    cout<<"Sorted array: "<<endl;

    for(int i=0;i<n;i++){
            cout<<xyarray[i].first<<" "<<xyarray[i].second<<endl;
    }

    cout<<"Required vertexes: "<<endl;

    for(int i=0;i<n;i++){
        if(dom[xyarray[i].first]==false||dom[xyarray[i].second]==false){
            cout<<xyarray[i].first<<" "<<xyarray[i].second<<endl;
        }
    }

    return 0;

}
