#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const long long INF = INT64_MAX;
long long V_size;

vector<long long> Dijkstras_algorithm(vector<vector<long long>> adjacency_matrix, long long start_V){
    vector<bool> visited(V_size, false);
    vector<long long> distance(V_size, INF);
    distance[start_V] = 0;
    long long min, min_idx;
    do{
        min = INF, min_idx = INF;
        for(long long i = 0; i < V_size; ++i)
            if(!visited[i] && distance[i] < min)
                min = distance[i], min_idx = i;

        if(min_idx != INF){
            for(long long i = 0; i < V_size; ++i)
                if(adjacency_matrix[min_idx][i] > 0)
                    if(min + adjacency_matrix[min_idx][i] < distance[i])
                        distance[i] = min + adjacency_matrix[min_idx][i];
            visited[min_idx] = true;
        }
    } while (min_idx < INF);
    return distance;
}

int main(){
    long long E_size;
    long long start_V, finish_V;
    cin >> V_size >> E_size >> start_V >> finish_V;
    vector<vector<long long>> adjacency_matrix (V_size, {V_size, 0});
    for(long long i = 0; i < E_size; ++i){
        long long v1, v2;
        cin >> v1 >> v2 >> adjacency_matrix[v1][v2];
    }
    vector<long long> min_distance = Dijkstras_algorithm(adjacency_matrix, start_V);
    for(int i = 0; i < V_size; ++i){
        cout << min_distance[i] << ' ';
    }
    cout<<endl;
    return 0;
}