#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ST {
private:
    vector<long long> seg;
    int n;

    long long push(long long a, long long b) {
        return a + b;
    }

public:
    ST(int n) : n(n), seg(4 * n) {}

    void build(vector<long long>& arr, int ind, int low, int high) {
        if (high - low == 0) {
            seg[ind] = arr[low];
            return;
        }
        int mid = low + (high - low) / 2;
        int leftind = (2 * ind) + 1;
        int rightind = (2 * ind) + 2;
        build(arr, leftind, low, mid);
        build(arr, rightind, mid + 1, high);
        seg[ind] = push(seg[leftind], seg[rightind]);
    }

    long long query(int ind, int low, int high, int s, int e) {
        if (high < s || e < low) return 0;
        if (s <= low && high <= e) return seg[ind];
        int mid = low + (high - low) / 2;
        int leftind = 2 * ind + 1;
        int rightind = 2 * ind + 2;
        long long a = query(leftind, low, mid, s, e);
        long long b = query(rightind, mid + 1, high, s, e);
        return push(a, b);
    }

    void update(int ind, int low, int high, int pivot, int val) {
        if (low == high) {
            seg[ind] = val;
            return;
        }
        int mid = low + (high - low) / 2;
        int leftind = 2 * ind + 1;
        int rightind = 2 * ind + 2;
        if (pivot <= mid) update(leftind, low, mid, pivot, val);
        else update(rightind, mid + 1, high, pivot, val);
        seg[ind] = push(seg[rightind], seg[leftind]);
    }
};

void dfs(vector<vector<int>>& list, vector<int>& temp, int curr, int prev) {
    vector<int> internal = list[curr];
    temp.push_back(curr);
    for (int i = 0; i < internal.size(); i++) {
        int next = internal[i];
        if (next != prev) dfs(list, temp, next, curr);
    }
    temp.push_back(curr);
}

void solve(vector<vector<int>>& list, vector<int>& val, int n, int q) {
    vector<vector<int>> ind(n, vector<int>(2, -1));
    vector<long long> arr(2 * n);
    vector<long long> ans;

    vector<int> temp;
    dfs(list, temp, 0, -1);

    for (int i = 0; i < temp.size(); i++) {
        int node = temp[i];
        if (ind[node][0] == -1) {
            ind[node][0] = i;
        }
        ind[node][1] = i;
    }

    for (int i = 0; i < n; i++) {
        arr[ind[i][0]] = val[i];
        arr[ind[i][1]] = -val[i];
    }

    ST seg(2 * n);
    seg.build(arr, 0, 0, 2 * n - 1);

    for (int i = 0; i < q; i++) {
        int type, root, val2;
        cin >> type >> root;
        root--;

        if (type == 1) {
            cin >> val2;
            seg.update(0, 0, 2 * n - 1, ind[root][0], val2);
            seg.update(0, 0, 2 * n - 1, ind[root][1], -val2);
        } else {
            ans.push_back(seg.query(0, 0, 2 * n - 1, 0, ind[root][0]));
        }
    }

    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<int> val(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    vector<vector<int>> list(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        list[a].push_back(b);
        list[b].push_back(a);
    }

    solve(list, val, n, q);

    return 0;
}
