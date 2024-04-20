#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void parfill(vector<vector<int>>& list, int* par, int curr, int prev);
void dfs(vector<vector<int>>& list, int* par, int** dp, int curr, int prev);
void fill(int* par, int** dp, int curr);
void clevel(vector<vector<int>>& list, int* level, int curr, int prev, int l);
int cnt(vector<vector<int>>& list, int* temp, int* ans, int curr, int prev);
int tres(int** dp, int a, int b);
int ans(int** dp, int curr, int temp);

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> list(n);
    int par[n];
    memset(par, -1, sizeof(par));
    int** que = new int*[q];
    for (int i = 0; i < q; ++i) {
        que[i] = new int[2];
    }

    par[0] = -1;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        list[a].push_back(b);
        list[b].push_back(a);
    }
    parfill(list, par, 0, -1);

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        que[i][0] = a;
        que[i][1] = b;
    }

    int** dp = new int*[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = new int[19];
    }
    int level[n];
    memset(level, 0, sizeof(level));

    clevel(list, level, 0, -1, 0);
    for (int i = 0; i < n; i++) dp[i][0] = par[i];
    dfs(list, par, dp, 0, -1);

    int res[q];
    for (int i = 0; i < q; i++) {
        int a = que[i][0];
        int b = que[i][1];
        int level1 = level[a];
        int level2 = level[b];
        if (level1 > level2) a = ans(dp, a, level1 - level2);
        else b = ans(dp, b, level2 - level1);
        res[i] = tres(dp, a, b);
    }

    int temp[n];
    memset(temp, 0, sizeof(temp));
    for (int i = 0; i < q; i++) {
        int a = que[i][0];
        int b = que[i][1];
        int root = res[i];
        if (root == a) {
            temp[b]++;
            if (par[root] != -1) temp[par[root]]--;
        } else if (root == b) {
            temp[a]++;
            if (par[root] != -1) temp[par[root]]--;
        } else {
            temp[a]++;
            temp[b]++;
            temp[root]--;
            if (par[root] != -1) temp[par[root]]--;
        }
    }

    int ans[n];
    cnt(list, temp, ans, 0, -1);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    // Free dynamically allocated memory
    for (int i = 0; i < n; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
    for (int i = 0; i < q; ++i) {
        delete[] que[i];
    }
    delete[] que;

    return 0;
}

void parfill(vector<vector<int>>& list, int* par, int curr, int prev) {
    par[curr] = prev;
    for (int next : list[curr]) {
        if (next != prev) {
            parfill(list, par, next, curr);
        }
    }
}

void dfs(vector<vector<int>>& list, int* par, int** dp, int curr, int prev) {
    fill(par, dp, curr);
    for (int next : list[curr]) {
        if (next != prev) {
            dfs(list, par, dp, next, curr);
        }
    }
}

void fill(int* par, int** dp, int curr) {
    for (int i = 1; i < 19; i++) {
        int temp = dp[curr][i - 1];
        if (temp == -1) dp[curr][i] = -1;
        else dp[curr][i] = dp[temp][i - 1];
    }
}

void clevel(vector<vector<int>>& list, int* level, int curr, int prev, int l) {
    level[curr] = l;
    for (int next : list[curr]) {
        if (next != prev) clevel(list, level, next, curr, l + 1);
    }
}

int cnt(vector<vector<int>>& list, int* temp, int* ans, int curr, int prev) {
    int sum = temp[curr];
    for (int next : list[curr]) {
        if (next != prev) sum += cnt(list, temp, ans, next, curr);
    }
    ans[curr] = sum;
    return ans[curr];
}

int tres(int** dp, int a, int b) {
    if (a == b) return a;
    if (dp[a][0] == dp[b][0]) return dp[a][0];
    for (int i = 1; i < 19; i++) {
        if (dp[a][i] == dp[b][i]) {
            return tres(dp, dp[a][i - 1], dp[b][i - 1]);
        }
    }
    return -1;
}

int ans(int** dp, int curr, int temp) {
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
    return curr;
}
