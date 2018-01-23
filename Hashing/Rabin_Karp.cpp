#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

const int MAX = 10e4;

int mod_pow(long long int x, long long int y, long long int p)
{
    long long int res = 1;

    x = x % p;

    while (y > 0)
    {
        if (y & 1)
            res = (res*x) % p;

		y = y>>1;
        x = (x*x) % p;
    }

    return res;
}

void rabin_karp(char *pat, char *str){
	const int p = 10007; //Prime must be greater than pattern length
	const int d = 255; //Number of possible characters
	int hp = 0, hs = 0, lp = strlen(pat);
	int h = mod_pow(d, lp - 1, p), i;

	for(i = 0; i < lp && str[i]; ++i){
		hp = (d * hp + pat[i]) % p;
		hs = (d * hs + str[i]) % p;
	}

	if(i != lp) return;

	for(; ; ++i){
		if(hp == hs){
			int j;
			for(j = 0; j < lp; ++j) if(str[i - lp + j] != pat[j]) break;
			if(j == lp) cout<<i - lp<<" ";
		}

		if(!str[i]) break;

		hs = (d * (hs - str[i - lp] * h) + str[i]) % p;
        if(hs < 0) hs = (hs + p);
	}
}

int main(){
	char s[MAX], p[MAX];
	cout<<"Pattern: ";
	cin>>p;
	cout<<"Text: ";
	cin>>s;
	cout<<"Indices at which pattern was found: ";
	rabin_karp(p, s);
	cout<<endl;
	return 0;
}
