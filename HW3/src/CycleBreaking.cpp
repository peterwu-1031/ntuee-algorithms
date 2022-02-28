#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void help_message() {
    cout << "usage: ./cb <input file name> <output file name>" << endl;
}

class Disjoint_Set {
public:
    vector<int> rank, parent;
    int set_num;

    Disjoint_Set(int n) {
        set_num = n;
        for(int i = 0; i < set_num; i++) {
           MakeSet(i);
        }
    }
  
    void MakeSet(int i) {
        rank.push_back(0);
        parent.push_back(i);
    }
  
    int Find(int x) {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }
  
    void Union(int x, int y) {
        int x_head = Find(x);
        int y_head = Find(y);
        if (rank[x_head] > rank[y_head]) {
            parent[y_head] = x_head;
        }
        else {
            parent[x_head] = y_head;
            if(rank[x_head] == rank[y_head]) {
                rank[y_head]++;
            }
        }
    }
};

class edge {
public:
    int weight, u, v;
};

class vertex {
public:
    char color = 'W';
};

// Merge sort method
void Merge(vector<edge>& data, int low, int middle1, int middle2, int high) {
    int n_left = middle1 - low + 1;
    int n_right = high - middle2 + 1;
    edge left[n_left + 1];
    edge right[n_right + 1];
    for(int i = 0; i < n_left; i++) {
        left[i] = data[low + i];
    }
    for(int i = 0; i < n_right; i++) {
        right[i] = data[middle2 + i];
    }
    left[n_left].weight = 101;
    right[n_right].weight = 101;
    int i = 0;
    int j = 0;
    for(int k = low; k <= high; k++) {
        if(left[i].weight <= right[j].weight) {
            data[k] = left[i];
            i++;
        }
        else {
            data[k] = right[j];
            j++;
        }
    }
}
void MergeSortSubVector(vector<edge>& data, int low, int high) {
    if(low < high) {
        int mid = (low+high)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid + 1, high);
        Merge(data, low, mid, mid + 1, high);
    }
}
void MergeSort(vector<edge>& data){
    MergeSortSubVector(data, 0, int(data.size()) - 1);
}

bool DFS_visit(vector<vector<int>> Adj, int i, vertex *v) {
    bool cycle;
    v[i].color = 'G';
    for(int j = 0; j < int(Adj[i].size()); j++) {
        if(v[Adj[i][j]].color == 'G') {
            return true;
        }
        else if(v[Adj[i][j]].color == 'W') {
            cycle = DFS_visit(Adj, Adj[i][j], v);
            if(cycle) {
                return true;
            }
        }
    }
    v[i].color = 'B';
    return false;
}

bool DFS_cycle(vector<vector<int>> Adj, int u_index, int v_index, int v_num) {
    bool cycle;
    vertex *v;
    v = new vertex[v_num];
    Adj[u_index].push_back(v_index);
    for(int i = 0; i < v_num; i++) {
        if(v[i].color == 'W') {
            cycle = DFS_visit(Adj, i, v);
            if(cycle) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
       help_message();
       return 0;
    }
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);

    char type;
    fin >> type;
    int v_num, e_num;
    fin >> v_num >> e_num;
    Disjoint_Set V(v_num);
    int u_index, v_index, w;
    if(type == 'u') {
        vector<edge> E;
        while(fin >> u_index >> v_index >> w) {
            edge e;
            e.u = u_index;
            e.v = v_index;
            e.weight = w;
            E.push_back(e);
        }
        MergeSort(E);
        vector<edge> removed;
        int cost = 0;
        for(int i = int(E.size()) - 1; i >= 0; i--) {
            if(V.Find(E[i].u) != V.Find(E[i].v)) {
                V.Union(E[i].u, E[i].v);
            }
            else {
                removed.push_back(E[i]);
                cost += E[i].weight;
            }
        }
        fout << cost << endl;
        for(int i = 0; i < int(removed.size()); i++) {
            fout << removed[i].u << " " << removed[i].v << " " << removed[i].weight << endl;
        }
    }
    else if(type == 'd'){
        vector<edge> E;
        while(fin >> u_index >> v_index >> w) {
            edge e;
            e.u = u_index;
            e.v = v_index;
            e.weight = w;
            E.push_back(e);
        }
        MergeSort(E);
        vector<vector<int>> Adj;
        for(int i = 0; i < v_num; i++) {
            Adj.push_back(vector<int>());
        }
        vector<edge> removed;
        int cost = 0;
        for(int i = int(E.size()) - 1; i >= 0; i--) {
            if(V.Find(E[i].u) != V.Find(E[i].v)) {
                V.Union(E[i].u, E[i].v);
                Adj[E[i].u].push_back(E[i].v);
            }
            else {
                removed.push_back(E[i]);
                cost += E[i].weight;
            }
        }

        for(int i = int(removed.size()) - 1; i >= 0; i--) {
            if(removed[i].weight <= 0) {
                continue;
            }
            else if(!DFS_cycle(Adj, removed[i].u, removed[i].v, v_num)) {
                Adj[removed[i].u].push_back(removed[i].v);
                removed.erase(removed.begin() + i);
                cost -= removed[i].weight;
            }
        }
        fout << cost << endl;
        for(int i = 0; i < int(removed.size()); i++) {
            fout << removed[i].u << " " << removed[i].v << " " << removed[i].weight << endl;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
