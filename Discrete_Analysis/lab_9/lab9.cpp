#include <bits/stdc++.h>

using namespace std;

const long long INF = INT64_MAX;

vector<long long> Dijkstras_algorithm(vector<unordered_map<unsigned, long long>> adjacency_vec, long long start_V){
    vector<bool> visited(adjacency_vec.size(), false);
    vector<long long> distance(adjacency_vec.size(), INF);
    priority_queue<pair<long long, unsigned>, vector<pair<long long, unsigned>>, greater<>> v_to_visit;

    distance[start_V] = 0;
    v_to_visit.push({0, start_V});
    while(!v_to_visit.empty()){
        long long v = v_to_visit.top().second;
        v_to_visit.pop();
        if(!visited[v]){
            for(auto& j: adjacency_vec[v]){
                if(distance[v] + j.second < distance[j.first]){
                    distance[j.first] = distance[v] + j.second;
                    v_to_visit.push({distance[j.first], j.first});
                }
            }
            visited[v] = true;
        }
    }
    return distance;
}

int main(){
    long long V_size, E_size;
    long long start_V, finish_V;
    cin >> V_size >> E_size >> start_V >> finish_V;
    vector<unordered_map<unsigned, long long>> adjacency_vec (V_size);
    for(long long i = 0; i < E_size; ++i){
        long long v1, v2, length;
        cin >> v1 >> v2 >> length;
        adjacency_vec[v1 - 1].insert({v2 - 1, length});
        adjacency_vec[v2 - 1].insert({v1 - 1, length});
    }
    
    return 0;
}