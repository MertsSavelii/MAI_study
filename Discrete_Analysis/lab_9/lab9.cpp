#include <bits/stdc++.h>

using namespace std;

struct edge_t
{
    unsigned from, to;
    long long distane;
};


const long long INF = INT64_MAX;

vector<unordered_map<unsigned, long long>> Graph_input(unsigned V_size, unsigned E_size){
    vector<unordered_map<unsigned, long long>> adjacency_vec(V_size);
    for(long long i = 0; i < E_size; ++i){
        long long v1, v2, length;
        cin >> v1 >> v2 >> length;
        adjacency_vec[v1 - 1].insert({v2 - 1, length});
    }
    return adjacency_vec;
}

vector<long long> Dijkstras_algorithm(unsigned V_size, unsigned start_V, vector<unordered_map<unsigned, long long>> graph_vec){
    vector<bool> visited(V_size, false);
    vector<long long> distance(V_size, INF);
    priority_queue<pair<long long, unsigned>, vector<pair<long long, unsigned>>, greater<>> v_to_visit;

    distance[start_V ] = 0;
    v_to_visit.push({0, start_V });
    while(!v_to_visit.empty()){
        long long v = v_to_visit.top().second;
        v_to_visit.pop();
        if(!visited[v]){
            for(auto& j: graph_vec[v])
                if(distance[v] + j.second < distance[j.first]){
                    distance[j.first] = distance[v] + j.second;
                    v_to_visit.push({distance[j.first], j.first});
                }
            visited[v] = true;
        }
    }
    return distance;
}

vector<long long> Ford_Bellman_algorithm(unsigned V_size, unsigned start_V, vector<edge_t> edges){
    vector<long long> distance(V_size, INF);
    bool has_graph_changed = true;

    distance[start_V] = 0;
    for(int i = 0; has_graph_changed and i < V_size+1; ++i){
        has_graph_changed = false;
        for(auto& edge: edges)
            if(distance[edge.first.first] < INF)
                if(distance[edge.first.second] > distance[edge.first.first] + edge.second){
                    distance[edge.first.second] = distance[edge.first.first] + edge.second;
                    has_graph_changed = true;
                }
    }
    if(has_graph_changed){
        cout << "Negative cycle" <<endl;
        exit(0);
    }
    return distance;
}

int main(){
    unsigned V_size, E_size; // колличество вершин и рёбер соответсвенно
    vector<unordered_map<unsigned, long long>> adjacency_vec; // вектор смежности
    cin >> V_size >> E_size;
    adjacency_vec = Graph_input(V_size, E_size);

    // вектор рёбер удобно использовать в Ford_Bellman
    vector<edge_t> edges; // pair<pair<откуда, куда>, длина ребра>
    for(unsigned i = 0; i < adjacency_vec.size(); ++i)
        for(auto& j: adjacency_vec[i])
            edges.push_back(edge_t{i, j.first, j.second});

    // добавляе фиктивую вершину для использования в Ford_Bellman
    for(unsigned i = 0; i < V_size; ++i)
        edges.push_back(edge_t{V_size, i, 0});


    vector<long long> h = Ford_Bellman_algorithm(V_size + 1, V_size, edges);

    for (int i = 0; i < V_size; ++i)
        for (auto& edge: adjacency_vec[i])
            edge.second = edge.second + h[i] - h[edge.first];



    for(int i = 0; i < V_size; ++i){
        vector<long long> d = Dijkstras_algorithm(V_size, i, adjacency_vec);
        for (int j = 0; j < V_size; ++j){
            if (d[j] == INF) cout << "inf ";
            else cout << d[j] + h[j] - h[i] << " ";
        }
        cout << endl;
    }
    return 0;
}