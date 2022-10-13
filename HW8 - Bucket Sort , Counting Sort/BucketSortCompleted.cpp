#include<bits/stdc++.h>
using namespace std;

int n;

void Sort(double arr[], int nn,int divider)
{
    vector<double> b[n+6];

    for (int i=0; i<nn; i++)
    {

       int bi = floor(arr[i]/divider);

        b[bi].push_back(arr[i]);
    }



    for (int i=0; i<5; i++){
       sort(b[i].begin(), b[i].end());

    }

    int index = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < b[i].size(); j++)
          arr[index++] = b[i][j];
}

int main()
{
    cin>>n;
    double arr[n+2];
    double negarr[n+2],posarr[n+2];
    int negc=0,posc=0;

    int maxi=0,maxi2=0;
    for(int i=0;i<n;i++){
        cin>>arr[i];

        if(arr[i]<0){
            negarr[negc]=-arr[i];
            negc++;
            if(maxi2<-arr[i]) maxi2= - arr[i];
        }
        else{
            if(arr[i]>maxi) maxi=arr[i];
            posarr[posc]=arr[i];
            posc++;
        }

    }
    int bucket=5;
    int divider=ceil((maxi+1)*1.0/bucket);
    Sort(posarr, posc,divider);

    int divider2=ceil((maxi2+1)*1.0/bucket);

    Sort(negarr,negc,divider2);

    cout << "Sorted array:"<<endl;
    for(int i=negc-1;i>=0;i--){
        cout<<-negarr[i]<<" ";
    }

    for (int i=0; i<posc; i++)
       cout << posarr[i] << " ";

       cout<<endl;

    return 0;
}
