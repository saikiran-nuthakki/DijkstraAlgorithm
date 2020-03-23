//---------------------------------------------------------------------
// Name: Saikiran Nuthakki
// Email: sqn5261@psu.edu
// Description: This program uses Dijkstra algorithm to find the shortest path between two nodes
//---------------------------------------------------------------------

#include <iostream>
#include <string>
#include "graph.h"
#include "min_heap.h"
#include "set.h"
#include "stack.h"

using namespace std;
void dijkstra (Graph, int, int);


int main()
{
    Graph g;
    string path;
    MinHeap h;
    int so, ta;
    
    
    
    cout << "Please enter location of graph file to load: "; // prompts user to input location of graph files
    cin >> path;// User input for location of graph files
    
    g.create_graph(path);
    
    cout << g.dimension() << endl;
    
    g.print_adj_matrix(); // prints the matrix
    
    
    cout << "Please enter the index of the starting vertex: "; // Prompts user for index of starting vertex
    cin >> so;
    
    cout << " Please enter the index of the terget vertex: "; // Prompts user for index of target vertex
    cin >> ta;
    
    dijkstra (g,so ,ta); // Finds shortest path
    
    
    return 0;
}

void dijkstra (Graph g, int s, int t){
    
    int* distance = new int[g.dimension()];
    for ( int i = 0; i < g.dimension(); i++){
        distance[i] = 0;
    }
    int *previous = new int[g.dimension()];
    for (int i = 0; i < g.dimension(); i++) {
        previous[i] = 0;
    }

    
    distance[s] = 0;
    
    MinHeap* Q = new MinHeap();
    
    for(int v = 0; v < g.dimension(); v++) {
        if (v != s ){
            distance [v] = INT_MAX;
        }
        previous[v] = -1;
        Q -> insert(v, distance[v]);
        
        
    }
        
    int prev_v = 0;
    while(!Q-> is_empty()){
        int u = Q-> extract_min();
        
        if (u == t){
            break;
        }
    
        for (int v = 0; v < g.dimension(); v++) {
            int length = g.get_weight(v,u);
            if (length != 0) {
                int alt = distance[u] + length;
                if(alt < distance[v]){
                    distance[v] = alt;
                    previous[v] = u;
                    Q->decrease_priority(v, alt);
                    
                }
                
            }
        }
    
        
    }
    
    
    
    
    
    Stack* stack = new Stack();
    
    int u = t;
    
    while (previous[u] != -1) {
        stack-> push(u);
        u = previous[u];
    }
    
    stack-> push(u);
    int tot=0;
    int prev = stack-> pop();
    int i = 0;
    while (!stack -> isEmpty()) {
        int temp = stack-> pop();
        cout << prev << "to" << temp << ":" << g.get_weight(temp, prev) << endl;
        tot +=g.get_weight(temp, prev);
        prev = temp;
        i++;
    }
    cout<<"Total path length: "<<tot<<endl; // Outputs the total path length
    delete distance;
    delete previous;
}

