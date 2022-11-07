#include <bits/stdc++.h>

using namespace std;

const long long INF = INT64_MAX;
long long V_size, E_size;// колличество вершин и рёбер соответсвенно
long long start_V, finish_V; // начальная и конечная вершины соответственно
vector<unordered_map<unsigned, long long>> adjacency_vec; // вектор смежности

void Graph_input(){
    cin >> V_size >> E_size >> start_V >> finish_V;
    adjacency_vec.resize(V_size);
    for(long long i = 0; i < E_size; ++i){
        long long v1, v2, length;
        cin >> v1 >> v2 >> length;
        adjacency_vec[v1 - 1].insert({v2 - 1, length});
    }
}

vector<long long> Dijkstras_algorithm(){
    vector<unordered_map<unsigned, long long>> graph_vec(V_size);
    vector<bool> visited(V_size, false);
    vector<long long> distance(V_size, INF);
    priority_queue<pair<long long, unsigned>, vector<pair<long long, unsigned>>, greater<>> v_to_visit;

    //переделываем из ориентированного в неориентированный
    for(int vi = 0; vi < V_size; ++vi)
        for(auto& j: adjacency_vec[vi]){
            graph_vec[vi].insert(j);
            graph_vec[j.first].insert({vi, j.second});
        }

    distance[start_V - 1] = 0;
    v_to_visit.push({0, start_V - 1});
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

vector<long long> Ford_Bellman_algorithm(){
    vector<pair<pair<unsigned, unsigned>, long long>> edges; // откуда, куда, длина ребра
    vector<long long> distance(V_size, INF);
    bool has_graph_changed = true;

    for(int i = 0; i < adjacency_vec.size(); ++i)
        for(auto& j: adjacency_vec[i])
            edges.push_back({{i,j.first}, j.second});


    distance[start_V - 1] = 0;
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
    Graph_input();
    vector<long long> min_distance = Ford_Bellman_algorithm();
    if(min_distance[finish_V - 1] == INF) {
        cout << "No solution" << endl;
    } else {
        cout<< min_distance[finish_V - 1] << endl;
    }
    return 0;
}