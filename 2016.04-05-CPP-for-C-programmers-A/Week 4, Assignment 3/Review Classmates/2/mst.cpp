#include <iostream>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;

// fixed file name
const char* filename = "mst_data";
const int infinity = 9999;

class Graph {
private:
    int** cost;
    int size;
    bool file_available;

public:
    // init the graph from file
    Graph() {
        ifstream my_input(filename);
        int from, to, cst;

        // if the file is not available, don't proceed further
        file_available = false;
        if(!my_input.is_open()) {
            cout << "Can't open the data file. Please rename it to \"";
            cout << filename << "\"" << endl;
            exit(1);
        }

        // get graph size from the first line of the file
        my_input >> size;

        cost  = new int*[size];
        for(int i = 0; i < size; i++) {
            cost[i]  = new int[size];
        }

        while(!my_input.eof()) {
            // read originate node, destination node, and cost from each line
            my_input >> from >> to >> cst;
            cost[from][to] = cost[to][from] = cst;
        }
    }

    // return the graph size
    int get_size(void) { return size; }

    // return cost of the edge
    int get_cost(int a, int b) { return cost[a][b]; }

    // display graph matrix
    void print() {
        cout << "Graph size : " << size << endl;
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++)
                cout << setw(2) << cost[i][j] << " ";
            cout << endl;
        }
    }
};

class PrimMST {
private:
    vector<bool> reach;
    vector<int> cost_to_node;
    vector<int> from_node;

    // pick unselected minimum cost node
    int pick_min_node(void) {
        int min_val = infinity;
        int pick_node;
        for( int i = 0; i < reach.size(); i++) {
            if(reach[i] == false && cost_to_node[i] < min_val){
                min_val = cost_to_node[i];
                pick_node = i;
            }
        }
        return pick_node;
    }

    // main MST processing
    void process_prim(Graph* graph) {
        // always pick node 0 first whereas it's the root node (point to self)
        cost_to_node[0] = 0;
        from_node[0] = 0;

        // calculate |V| - 1 times
        while(accumulate(reach.begin() + 1, reach.end(), 0) < reach.size() - 1) {
            // select minimum cost node
            int picked_node = pick_min_node();
            reach[picked_node] = true;

            // update values
            for(int i = 0; i < reach.size(); i++) {
                if(graph->get_cost(picked_node, i) > 0 && reach[i] == false &&
                   graph->get_cost(picked_node, i) < cost_to_node[i]) {
                    from_node[i] = picked_node;
                    cost_to_node[i] = graph->get_cost(picked_node, i);
                }
            }
        }
    }

public:
    // init algo for inputted graph
    PrimMST(Graph* graph) {
        // initial selected list
        for(int i = 0; i < graph->get_size(); i++) {
            reach.push_back(false);
            cost_to_node.push_back(infinity);
            from_node.push_back(-1);
        }
        process_prim(graph);
    }

    // display the calculated tree
    void print_tree(void) {
        for(int i = 1; i < reach.size(); i++) {
            cout << "(" << setw(2) << i << ")--(";
            cout << setw(2) << from_node[i] << ") cost ";
            cout << setw(2) << cost_to_node[i] << endl;
        }
    }

    // return MST cost
    int get_cost(void) { 
        return accumulate(cost_to_node.begin(), cost_to_node.end(), 0);
    }
};

int main(void) {
    Graph* my_graph = new Graph();
    //my_graph->print();

    PrimMST* prim = new PrimMST(my_graph);
    prim->print_tree();
    cout << "MST cost: " << prim->get_cost() << endl;

    return 0;
}

