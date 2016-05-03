//Week 3 assignment
//Results with density 0.2 fall around 4.45
//Results with density 0.4 fall around 2.21

#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <iomanip>
#include <iterator>
#include <functional>
#include <queue>
#include <algorithm>
#include <chrono>
#include <sys/time.h>

using namespace std;

//A class to deal with Graph nodes to be used in path definition
class Node
{
public:
    Node(int i, double v, int p);
    void setIndex(int i);
    int getIndex();
    void setVal(double v);
    double getVal();
    void setPrev(int p);
    int getPrev();
private:
    int index;
    double val;
    int prevNode;
};

Node::Node(int i = -1, double v = INFINITY, int p = -1):index(i), val(v), prevNode(p)
{

}

//sets index of node
void Node::setIndex(int i)
{
    index = i;
}

//Gets index of node
int Node::getIndex()
{
    return index;
}

//Sets node distance
void Node::setVal(double v)
{
    val = v;
}

//Gets node distance
double Node::getVal()
{
    return val;
}

//Sets prev node
void Node::setPrev(int p)
{
    prevNode = p;
}

//Return prev node
int Node::getPrev()
{
    return prevNode;
}

//A Class to deal with  randomly generated Graphs
class Graph
{
public:
    Graph(int s, double d, double r);
    ~Graph();
    void print();
    int V();
    int E();
    int adjacent(int i, int j);
    vector<int> neighbors(int i);
    int addEdge(int i, int j, double val);
    int delEdge(int i, int j);
    double getEdge(int i, int j);
    double get_node_value(int i);
    int set_node_value(int i, double val);
    vector<Node> *getNodes();
private:
    int size;
    double density;
    double range;
    int edges;
    vector<Node> nodes;
    vector< vector<double> > edges_matrix;

};


//Graph constructor
Graph::Graph(int s, double d, double r):size(s), density(d), range(r) {

    //cout << "New Instance of Graph with size: " << s << ", density: " << d << " and range: " << r << endl;


    random_device rd;
    mt19937 rng;

    struct timeval time;
    gettimeofday(&time,NULL);

    //time seeding of random number generator
    rng.seed((time.tv_sec * 1000) + (time.tv_usec / 1000));
    uniform_real_distribution<double> realDist(0.0, 1.0);
    uniform_real_distribution<double> rangeDist(0.0, range);

    for (int i=0; i<s; i++)
    {
        vector<double> temp_vec(size);
        edges_matrix.push_back(temp_vec);
    }

    edges = 0;

    for (int i=0; i<s; i++)
    {
        Node n;

        nodes.push_back(n);

        for (int j = i + 1; j < s; j++)
        {

            if (realDist(rng) < density)
            {
                 edges_matrix[i][j] = edges_matrix[j][i] = rangeDist(rng);
                 edges++;
            }
            else
            {
                edges_matrix[i][j] = edges_matrix[j][i] = 0.0;
            }
        }
    }


}

Graph::~Graph()
{
    //cout << "Deleting Graph";
}

//Printout of the graph
void Graph::print()
{
    for (int i=0; i< size; i++)
    {
        vector<double> temp_vec = edges_matrix[i];
        for (auto j = temp_vec.begin(); j != temp_vec.end(); ++j)
        {
            cout << setprecision(1) << fixed <<  *j << ' ';
        }
        cout << endl;
    }
}

//retrns Graph size
int Graph::V()
{
    return edges_matrix.size();
}



//Are nodes direcly connecnted?
int Graph::adjacent(int i, int j)
{
    if ((i < 0) || (i >= size) || (j < 0) || (j >= size))
    {
        return -1;
    }
    if (edges_matrix[i][j] > 0.0)
    {
        return 1;
    }
    return 0;
}

//Gets neigbors of node
vector<int> Graph::neighbors(int i)
{
    vector<int> temp_vec;
    if ( (i >= 0) && (i < size))
    {
        for (int j = 0; j < size; j++)
        {
            if (edges_matrix[i][j] > 0.0)
            {
                 temp_vec.push_back(j);
            }
        }
    }
    return temp_vec;
}

//Adds an edge between two nodes or updates value
int Graph::addEdge(int i, int j, double val)
{
    if ((i < 0) || (i >= size) || (j < 0) || (j >= size))
    {
        return -1;
    }

    edges_matrix[i][j] = val;

    return 0;
}

//Deletes edge between nodes
int Graph::delEdge(int i, int j)
{
    if ((i < 0) || (i >= size) || (j < 0) || (j >= size))
    {
        return -1;
    }

    edges_matrix[i][j] = 0.0;

    return 0;
}

//Gets edge value between nodes
double Graph::getEdge(int i, int j)
{
    if ((i < 0) || (i >= size) || (j < 0) || (j >= size))
    {
        return INFINITY;
    }

    return edges_matrix[i][j];
}

//Gets node value
double Graph::get_node_value(int i)
{
    if ((i < 0) || (i >= size))
    {
        return INFINITY;
    }

    return nodes[i].getVal();
}

//Sets node value
int Graph::set_node_value(int i, double val)
{
    if ((i < 0) || (i >= size))
    {
        return -1;
    }

    nodes[i].setVal(val);

    return 0;
}

//Return ponter to the nodes
vector<Node> *Graph::getNodes()
{
    return &nodes;
}

//A priority queue class
class FastQueue
{
public:
    FastQueue();
    int push(Node n);
    Node pop();
    int update(Node n);
    int size();
private:
    vector<Node> nodes;


};

//Priority queue constructor
FastQueue::FastQueue()
{

}

//Push a node in queue
int FastQueue::push(Node n)
{

    nodes.push_back(n);

    return 0;
}

//Return highest priority node and removes from queue
Node FastQueue::pop()
{
    double min = INFINITY;
    Node n;
    for (int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i].getVal() <= min)
        {
            min = nodes[i].getVal();
            n = nodes[i];
        }
    }
    if (n.getIndex() != -1)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            if(nodes[i].getIndex() == n.getIndex())
            {
                nodes.erase(nodes.begin() + i);
            }
        }
    }
    return n;
}

//Size of queue
int FastQueue::size()
{
    return nodes.size();
}

//Update priority of node in queue
int FastQueue::update(Node n)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i].getIndex() == n.getIndex())
        {
            nodes[i] = n;
        }
    }

    return 0;
}


//Class for shortest path computation
class ShortestPath
{
public:
    ShortestPath(Graph *g);
    vector<int> path(int source, int dest);
    double pathLen(int source, int dest);
private:
    Graph *mGraph;
};

//ShortestPath constructor takes a reference to a graph
ShortestPath::ShortestPath(Graph *g):mGraph(g)
{

}


//Compute path between nodes
vector<int> ShortestPath::path(int source, int dest)
{
    vector<Node> *nodes = mGraph->getNodes();
    function<bool(Node, Node)> ccc =  [](Node left, Node right){return left.getVal() > right.getVal();};
    FastQueue queue;


    //Source node Init
    (*nodes)[source].setIndex(source);
    (*nodes)[source].setVal(0.0);

    //Other Nodes
    for (unsigned int i = 0; i < (*nodes).size(); i++)
    {
        if (i != source)
        {
            (*nodes)[i].setIndex(i);
            (*nodes)[i].setVal(INFINITY);
            (*nodes)[i].setPrev(-1);
        }
        Node n = (*nodes)[i];
        queue.push(n);

    }

    //Loop over pririty queue to scan neighbors
    while(queue.size() != 0)
    {
        Node n = queue.pop();

        int u = n.getIndex();
        vector<int> neighbors = mGraph->neighbors(u);
        if (neighbors.size() > 0)
        {
            for (unsigned int j = 0; j < neighbors.size(); j++)
            {
                int v = neighbors[j];
                Node nodeV= (*nodes)[v];
                double alt = n.getVal() + mGraph->getEdge(u, v);
                if (alt < nodeV.getVal())
                {
                    nodeV.setVal(alt);
                    nodeV.setPrev(u);
                    queue.update(nodeV);
                    (*nodes)[v] = nodeV;
                }
            }
        }
    }

    if ((*nodes)[dest].getVal() == INFINITY)
    {
        vector<int> empty;
        return empty;
    }

    vector<int> mPath;
    Node p = (*nodes)[dest];

    while(p.getIndex() != source)
    {
        mPath.push_back(p.getIndex());
        p = (*nodes)[p.getPrev()];
    }

    return mPath;
}

//Compute leght of path given by ShortestPath::path
double ShortestPath::pathLen(int source, int dest)
{
    vector<int> mPath = path(source, dest);
    double result = 0;
    if (mPath.size() > 0)
    {
        for (int i = 0; i < (mPath.size()-1) ; i++)
        {
            result += mGraph->getEdge(mPath[i], mPath[i+1]);
        }

        result += mGraph->getEdge(mPath[mPath.size()-1], source);

    }
    else
    {
        result = INFINITY;
    }

    return result;
}

//Main Monte Carlo Driver progam
int main(int argc, char *argv[])
{
    int mcSize = 1000;      //Number of samples
    int size = 50;          //Size of graph
    double density = 0.2;   //density of graph
    double range = 10.0;    //Range of edges distance

    double MCDist = 0;

    for (int m = 0; m < mcSize; m++)
    {
        Graph g(size, density, range);

        //g.print();

        ShortestPath mPath(&g);

        double avgDist = 0.0;
        int cnt = 0;
        for(int i = 1; i < size; i++)
        {
            double dist =  mPath.pathLen(0,i);
            if (dist < INFINITY)
            {
                avgDist += dist;
                cnt++;
            }
             //cout << "Distance (" << 0 << ", " << i << ") :" << dist << endl;
        }

        avgDist = avgDist/((double)cnt);

        //cout << setprecision(10) << fixed << "Min dist: " << min << endl;
        MCDist += avgDist;

    }

    cout << "Result of Monte Carlo Simulation: " << MCDist/((double)mcSize) << endl;



    return 0;
}
