#include<bits/stdc++.h>
using namespace std;

int used[100001];

int main(){
    int T;
    cin >> T;
    
    while(T--){
        int N;
        cin >> N;
        int A[N];
        for(int i=0;i<N;i++) cin >> A[i];
        
        sort(A, A+N, greater<int>());
        
        long long alex = 0, bob = 0;
        int turn = 0;
        
        for(int i=0;i<N;i++){
            if(used[A[i]] >= 2) continue;
            used[A[i]]++;
            if(turn == 0) alex += A[i];
            else bob += A[i];
            turn = 1 - turn; 
        }
        for(int i=0;i<N;i++) used[A[i]] = 0;
        
        if(alex > bob) cout << "Alex\n";
        else cout << "Bob\n";
    }
    
    return 0;
}
