#include<bits/stdc++.h>
using namespace std;
#define MAX 1000

int row[MAX],col[MAX];
int dp[MAX][MAX];

int func(int beg,int end)
{
	if(beg>=end) return 0;
	if(dp[beg][end]) return dp[beg][end];
	int ans= INT_MAX;
	for(int mid=beg;mid<end;mid++)
	{
		int opr_left=func(beg,mid);
		int opr_right=func(mid+1,end);
		int opr_for_left_mul_right=row[beg]*col[mid]*col[end];
		int total=opr_for_left_mul_right+opr_left+opr_right;

		ans=min(ans,total);
	}

	return dp[beg][end]=ans;
}

int main()
{
	int n;
	cin>>n;
	int j=0;
	int ara[MAX];
	for(int i=0;i<n;i++){
		cin>>ara[i];
		if(i>0){
            row[j]=ara[i-1];
            col[j]=ara[i];
            j++;
		}
	}

	cout<<func(0,n-2)<<endl;

	return 0;
}
