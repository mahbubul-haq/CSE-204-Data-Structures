#include<bits/stdc++.h>
using namespace std;
int n;

void Sort(int arr[],int mini,int maxi,int nn)
{

    int temp[nn+2];


    int count[maxi+2], i;
    memset(count, 0, sizeof(count));


    for(i = 0; i<nn; ++i)
        ++count[arr[i]];


    for (i = mini+1; i <= maxi; ++i)
        count[i] += count[i-1];


    for (i = 0; i<nn; ++i)
    {
        temp[count[arr[i]]-1] = arr[i];
        --count[arr[i]];
    }

    for (i = 0; i<nn; ++i)
        arr[i] = temp[i];
}

int main()
{
    cin>>n;

    int arr[n+1];

    int maxi=-1;
    int mini=INT_MAX;
    int nmaxi=-1;
    int nmini=INT_MAX;
    int posarr[n+1],negarr[n+1];
    int negc=0,posc=0;

    for(int i=0;i<n;i++){
        cin>>arr[i];

        if(arr[i]>=0){

            if(arr[i]>maxi) maxi=arr[i];
            if(arr[i]<mini) mini=arr[i];

            posarr[posc]=arr[i];
            posc++;
        }
        else{
            if(-arr[i]>nmaxi) nmaxi=-arr[i];
            if(-arr[i]<nmini) nmini=-arr[i];
            negarr[negc]=-arr[i];
            negc++;

        }
    }

    if(posc>0)
        Sort(posarr,mini,maxi,posc);

    if(negc>0)
        Sort(negarr,nmini,nmaxi,negc);

    printf("Sorted array: \n");

    for(int i=negc-1;i>=0;i--){
        cout<<-negarr[i]<<" ";
    }

    for(int i=0;i<posc;i++){
        cout<<posarr[i]<<" ";

    }

    cout<<endl;

    return 0;
}
