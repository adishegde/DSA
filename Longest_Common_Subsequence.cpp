#include<iostream>
#include<vector>
#define max(x, y) ((x)>(y)?(x):(y))
using namespace std;

int longest_common_subseq(string a, string b){
	vector< vector<int> > dp(a.size() + 1, vector<int>(b.size() + 1));
	for(int i = 0; i <= a.size(); ++i){
		for(int j = 0; j <= b.size(); ++j){
			if(!(i && j)) dp[i][j] = 0;
			else if(a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
			else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}

	return dp[a.size()][b.size()];
}

int main(){
	string s1 = "ABCB", s2 = "BDCA";
	cout<<longest_common_subseq(s1, s2)<<" "<<longest_common_subseq(s2, s1)<<endl;
	return 0;
}
