#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<vector<int>>& list, vector<int>& par, vector<vector<int>>& dp, int curr) {
    for (int i = 1; i < 19; i++) {
        int temp = dp[curr][i - 1];
        if (temp == -1) dp[curr][i] = -1;
        else dp[curr][i] = dp[temp][i - 1];
    }
    vector<int>& internal = list[curr];
    for (int i = 0; i < internal.size(); i++) {
        int next = internal[i];
        dfs(list, par, dp, next);
    }
    
}

int ans(vector<vector<int>>& dp, int curr, int temp) {
    int res = 0;
    while (temp != 0) {
        int bit = temp & 1;
        if (bit == 1) {
            int next = dp[curr][res];
            if (next == -1) return next;
            curr = next;
        }
        res++;
        temp = temp >> 1;
    }
    return curr + 1;
}

void solve(vector<vector<int>>& list, vector<int>& par, vector<vector<int>>& que, int n, int q) {
    vector<vector<int>> dp(n, vector<int>(19));
    for (int i = 0; i < n; i++) dp[i][0] = par[i];
    dfs(list, par, dp, 0);
    vector<int> res(q);
    for (int i = 0; i < q; i++) {
        int curr = que[i][0];
        int temp = que[i][1];
        res[i] = ans(dp, curr, temp);
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> list(n);
    vector<int> par(n);
    par[0] = -1;
    for (int i = 1; i < n; i++) {
        int a;
        cin >> a;
        a--;
        list[a].push_back(i);
        par[i] = a;
    }
    vector<vector<int>> que(q, vector<int>(2));
    for (int i = 0; i < q; i++) {
        cin >> que[i][0] >> que[i][1];
        que[i][0]--;
    }
    solve(list, par, que, n, q);
    return 0;
}
