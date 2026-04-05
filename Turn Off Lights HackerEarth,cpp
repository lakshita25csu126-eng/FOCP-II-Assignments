#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    for(int l = 1; l <= n; l++){
        int ops = 0, i = 0;
        while(i < n){
            if(s[i] == '1'){
              ops++; i += l;
            }
            else{ 
              i++;
            }
        }
        if(ops <= k){
        cout << l; 
        return 0; }
    }
}
