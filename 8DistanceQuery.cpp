#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

void clevel(vector<vector<int>>& list, int* level, int curr,int prev, int l) {
    level[curr] = l;
    for(int i = 0; i < list[curr].size(); i++) {
        int next = list[curr][i];
        if(next!=prev) clevel(list, level, next,curr, l + 1);
    }
}

void fill(int* par, int** dp, int curr) {
    for(int i = 1; i < 19; i++) {
        int temp = dp[curr][i - 1];
        if(temp == -1) dp[curr][i] = -1;
        else dp[curr][i] = dp[temp][i - 1];
    }
}

void dfs(vector<vector<int>>& list, int* par, int** dp, int curr,int prev) {
    fill(par, dp, curr);
    for(int i = 0; i < list[curr].size(); i++) {
        int next = list[curr][i];
        if(next!=prev) dfs(list, par, dp, next,curr);
    }
}

int ans(int** dp, int curr, int temp) {
    int res = 0;
    while(temp != 0) {
        int bit = temp & 1;
        if(bit == 1) {
            int next = dp[curr][res];
            if(next == -1) return next;
            curr = next;
        }
        res++;
        temp = temp >> 1;
    }
    return curr;
}

int result(int** dp, int a, int b) {
    if(a == b) return 0;
    if(dp[a][0] == dp[b][0]) return 2;
    for(int i = 1; i < 19; i++) {
        if(dp[a][i] == dp[b][i]) {
            return pow(2,i)+result(dp, dp[a][i - 1], dp[b][i - 1]);
        }
    }
    return -1;
}

void solve(vector<vector<int>>& list, int* par, int** que, int n, int q) {
    int** dp = new int*[n];
    for(int i = 0; i < n; i++) {
        dp[i] = new int[19];
        memset(dp[i], -1, sizeof(int) * 19);
    }

    int* level = new int[n];
    clevel(list, level, 0, -1,0);

    for(int i = 0; i < n; i++) dp[i][0] = par[i];
    dfs(list, par, dp, 0,-1);

    int* res = new int[q];
    for(int i = 0; i < q; i++) {
        int a = que[i][0];
        int b = que[i][1];
        int level1 = level[a];
        int level2 = level[b];
        if(level1 > level2) a = ans(dp, a, level1 - level2);
        else b = ans(dp, b, level2 - level1);
        res[i] = result(dp, a, b) +abs(level2 - level1);
    }

    for(int i = 0; i < q; i++) {
        cout << res[i] << "\n";
    }

    for(int i = 0; i < n; i++) delete[] dp[i];
    delete[] dp;
    delete[] level;
    delete[] res;
}
void parfill(vector<vector<int>>& list,int* par,int curr,int prev) {
        par[curr]=prev;
        for(int i=0;i<list[curr].size();i++) {
            int next=list[curr][i];
            if(next!=prev) {
                parfill(list,par,next,curr);
            }
        }
    }

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> list(n);
    int* par = new int[n];

    par[0] = -1;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        list[a].push_back(b);
        list[b].push_back(a);
    }
    parfill(list,par,0,-1);

    int** que = new int*[q];
    for(int i = 0; i < q; i++) {
        que[i] = new int[2];
        cin >> que[i][0] >> que[i][1];
        que[i][0]--;
        que[i][1]--;
    }

    solve(list, par, que, n, q);

    delete[] par;
    for(int i = 0; i < q; i++) delete[] que[i];
    delete[] que;

    return 0;
}
