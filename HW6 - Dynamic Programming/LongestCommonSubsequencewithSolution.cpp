#include<iostream>
using namespace std;
bool visited[1000][1000];
int dp[1000][1000];

string str1,str2;
string ans;

void printAllSolutions(int i,int j){
    if(str1[i]==NULL||str2[j]==NULL) {
        cout<<ans<<endl;
        return;
    }
    if(str1[i]==str2[j]){
        ans+=str1[i];
        printAllSolutions(i+1,j+1);
        ans.erase(ans.end()-1);
    }
    else if(dp[i][j+1]<dp[i+1][j]) printAllSolutions(i+1,j);
    else if(dp[i+1][j]<dp[i][j+1]) printAllSolutions(i,j+1);
    else{
        printAllSolutions(i,j+1);
        printAllSolutions(i+1,j);
    }
}

void printOneSolution(int i,int j){
    if(str1[i]==NULL||str2[j]==NULL){
        cout<<ans<<endl;
        return;
    }
    if(str1[i]==str2[j]){
        ans+=str1[i];
        printOneSolution(i+1,j+1);
    }
    else{
        if(dp[i+1][j]>dp[i][j+1]) printOneSolution(i+1,j);
        else printOneSolution(i,j+1);
    }
}

int LCS(int i,int j){
    if(str1[i]==NULL||str2[j]==NULL) return 0;
    if(visited[i][j]) return dp[i][j];

    int ans=0;
    if(str1[i]==str2[j]) ans=1+LCS(i+1,j+1);
    else{
        int val1=LCS(i,j+1);
        int val2=LCS(i+1,j);
        ans=max(val2,val1);
    }
    visited[i][j]=true;
    dp[i][j]=ans;
    return dp[i][j];
}

int main(){

    cin>>str1>>str2;
    cout<<LCS(0,0)<<endl;

    cout<<"One solution: "<<endl;
    printOneSolution(0,0);

    return 0;
}
