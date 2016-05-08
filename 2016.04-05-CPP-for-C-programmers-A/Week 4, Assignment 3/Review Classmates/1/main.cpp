#include <cmath>
#include <cstdio>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Graph;
class MST;
class PriorityQueue;

struct Node
{
    int index;
    float cost;
};

//PriorityQueue Class: the queue is sorted with the smallest element at the end of the queue.
class PriorityQueue
{
public:
    vector<Node> mqueue;
    void chgPriority(int index,float priority);
    void minPriority();
    bool contains(int index);
    void insert(Node node);
    Node top();
    int size();
    float getCost(int index);

};
Node PriorityQueue::top() //returns the top element of the queue(with the smallest priority)
{
    return mqueue.back();
}
int PriorityQueue::size() //returns the size of the queue
{
    return mqueue.size();
}
bool PriorityQueue::contains(int index) //checks if the queue contains a node
{
    for (auto itr=mqueue.begin();itr!=mqueue.end();++itr)
    {
        if (itr->index==index)
            return true;
    }
    return false;
}
void PriorityQueue::insert(Node node) //insert a new node
{
    mqueue.push_back(node);

    //the queue is always presorted except the last element, i.e. the newest element
    Node temp = mqueue.back();
    for (auto itr=mqueue.end()-2;itr>=mqueue.begin();--itr)
    {
        if (temp.cost>itr->cost)
        {
            *(itr+1)=*itr;
            *itr=temp;
        }
        else
            break;
    }
}

void PriorityQueue::minPriority() //removes the element with the lowest priority
{
    mqueue.pop_back();
}
void PriorityQueue::chgPriority(int index,float priority) //changes the priority of a node in the queue
{
    Node temp;
    vector<Node>::iterator current_ptr;
    for (auto itr=mqueue.begin();itr!=mqueue.end();++itr)
    {
        if (itr->index==index)
        {
            itr->cost = priority;
            current_ptr=itr;
            temp = *itr;
            break;
        }
    }

    //if the new priority of the node is greater than the priority of the previous node, swap them
    if (priority>(current_ptr-1)->cost)
    {
        for (auto itr=(current_ptr-1);itr>=mqueue.begin();itr--)
        {
            if (priority>itr->cost)
            {
                *(itr+1)=*itr;
                *itr=temp;
            }


        }
    }
    //if the new priority of the node is smaller than the priority of the next node, swap them
    else if(priority<(current_ptr+1)->cost)
    {
        for (auto itr=(current_ptr+1);itr!=mqueue.end();itr++)
        {
            if (priority<itr->cost)
            {
                *(itr-1)=*itr;
                *itr=temp;
            }
        }
    }
}

float PriorityQueue::getCost(int index) //get the cost of a node
{
    for (auto itr=mqueue.begin();itr!=mqueue.end();++itr)
    {
        if (itr->index==index)
            return itr->cost;
    }
    return 0;
}

//generate a random probability in 2 decimal points
float prob()
{
    float num=rand() % 101;
    num=num/100;
    return num;
}

//generate a random float number in the range (min, max) in 2 decimal points
float RandomFloatNumber(float min, float max)
{
    float result = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    result = static_cast<float> (static_cast<int> (result * 100)) / 100;
    return result;
}

// class Graph: the edges are saved in matrix form in the member mgraph.
class Graph{
public:
    Graph(int size,float density,float minCost, float maxCost);
    Graph(string inputFileName); //Contructor for loading graph from a file
    int GetNumVertices(){return nVertices;};
    int GetNumEdges(){return nEdges;};
    bool Adjacent(int nodeX,int nodeY);
    vector<int> Neighbours(int nodeX);
    void AddEdge(int nodeX, int nodeY);
    void DeleteEdge(int nodeX, int nodeY);
    float GetEdgeValue(int nodeX, int nodeY);
    void SetEdgeValue(int nodeX, int node, float value);
    ~Graph();
private:
    int nVertices=0;
    int nEdges=0;
    bool** mGraph;
    float** mCosts;

};

Graph::Graph(int size, float density, float minCost, float maxCost)
{
    nVertices = size;
    //    srand(time(0));
    mGraph = new bool*[size];
    mCosts = new float*[size];

    for (int i=0;i<size;++i)
    {
        mGraph[i]=new bool[size];
        mCosts[i]=new float[size];
    }
    for(int i=0;i<size;++i)
    {
        for (int j=i;j<size;++j)
        {
            //            srand(time(0)+i+j);
            if(i==j)
            {
                mGraph[i][j]=false;
                mCosts[i][j]=0;
            }
            else
            {
                float p=prob();
                mGraph[i][j]=mGraph[j][i]=(p<density);
                if(mGraph[i][j]==true)
                    nEdges++;
                mCosts[i][j]=mCosts[j][i]=RandomFloatNumber(minCost,maxCost);
            }
        }
    }
}

Graph::Graph(string inputFileName)
{
    ifstream input(inputFileName,ifstream::in);
    input>>nVertices;
    mGraph = new bool*[nVertices];
    mCosts = new float*[nVertices];


    //Initiate graph matrix
    for (int i=0;i<nVertices;++i)
    {
        mGraph[i]=new bool[nVertices];
        mCosts[i]=new float[nVertices];
    }
    for(int i=0;i<nVertices;++i)
    {
        for (int j=i;j<nVertices;++j)
        {
            mGraph[i][j] = mGraph[j][i] = false;
            mCosts[i][j] = mCosts[j][i] = -1;
        }

    }

    // now read values from file
    int i, j;
    float value;
    while(!input.eof())
    {
        i=j=value=-1;
        input>>i>>j>>value;
        //cout<<i<<" "<<j<<" "<<value<<" "<<endl;
        if (i<0||j<0||value<0)
        {
            cout<<"Bad value in input file!"<<endl;
            break;
        }
        mGraph[i][j] = mGraph[j][i] = true;
        mCosts[i][j] = mCosts[j][i] = value;
    }
}

Graph::~Graph()
{
    for (int i=0;i<nVertices;++i)
    {
        delete[] mGraph[i];
        delete[] mCosts[i];
    }
    delete[] mGraph;
    delete[] mCosts;
}

bool Graph::Adjacent(int nodeX,int nodeY)
//tests whether there is an edge from node x to node y
{
    return mGraph[nodeX][nodeY];
}
vector<int> Graph::Neighbours(int nodeX){
    //lists all nodes y such that there is an edge from x to y
    vector<int>neighbourList;
    for (int i=0;i<nVertices;++i)
    {
        if (mGraph[nodeX][i]==true)
            neighbourList.push_back(i);
    }
    return neighbourList;
}

void Graph::AddEdge(int nodeX, int nodeY){
    //adds to G the edge from x to y, if it is not there
    mGraph[nodeX][nodeY]=mGraph[nodeY][nodeX]=true;
}
void Graph::DeleteEdge(int nodeX, int nodeY){
    //removes the edge from x to y, if it is there
    mGraph[nodeX][nodeY]=mGraph[nodeY][nodeX]=false;
}

float Graph::GetEdgeValue(int nodeX, int nodeY){
    //returns the value associated to the edge (x,y)
    return mCosts[nodeX][nodeY];
}
void Graph::SetEdgeValue(int nodeX, int nodeY, float value){
    //sets the value associated to the edge (x,y) to v
    mCosts[nodeX][nodeY]=value;
}

class MST
{
public:
    MST(Graph& graph): mGraph(graph) {}
    vector<int> Path(int src);
    float PathSize(int src);
    bool IsInCloseSet(int index);
private:
    vector<Node> mCloseSet;
    PriorityQueue mOpenSet;
    Graph& mGraph;
    void FindMST(int src, int nNodes);
};

bool MST::IsInCloseSet(int index)
{
    for (auto itr=mCloseSet.begin();itr!=mCloseSet.end();++itr)
    {
        if (itr->index==index)
            return true;
    }
    return false;
}

void MST::FindMST(int src, int nNodes)
{
    Node currentNode = {src, 0};

    while (mCloseSet.size()<nNodes)
    {
        cout << "enter" << endl;

        mCloseSet.push_back(currentNode);
        vector<int> neighbours = mGraph.Neighbours(currentNode.index);
        for (auto itr = neighbours.begin();itr != neighbours.end(); ++itr)
        {
            if (!IsInCloseSet(*itr))
            {
                Node newNode;
                newNode.index = *itr;
                newNode.cost = mGraph.GetEdgeValue(currentNode.index,*itr);
                if(mOpenSet.contains(*itr))
                {
                    if (mOpenSet.getCost(*itr) > newNode.cost)
                        //update priority if the cost is lower
                        mOpenSet.chgPriority(*itr,newNode.cost);

                }
                else
                    mOpenSet.insert(newNode);
            }

        }
        // add the node with lowest distance in the open set to the close set
        currentNode = mOpenSet.top();
        mOpenSet.minPriority();

    }
    //No path to desitination, set cost to negative.
    if(mCloseSet.size()<nNodes)
    {
        for (auto itr = mCloseSet.begin();itr != mCloseSet.end(); ++itr)
        {
            itr->cost*=-1;
        }
        cout<<"Error: No MST found for this graph."<<endl;
    }
}
vector<int> MST::Path(int src)
{
    vector<int> result;
    FindMST(src, mGraph.GetNumVertices());

    for (auto itr = mCloseSet.begin();itr!=mCloseSet.end();++itr)
    {
        result.push_back(itr->index);
    }
    return result;
}

float MST::PathSize(int src)
{
    float result=0;
    FindMST(src, mGraph.GetNumVertices());
    for (auto itr = mCloseSet.begin();itr!=mCloseSet.end();++itr)
    {
        result+=(itr->cost);
        //cout<<"cost="<<itr->cost<<endl;
    }
    return result;
}

int main() {
    //Change to your input file path!!!
    string inputFileName = "test_graph.txt";
    ifstream input(inputFileName,ifstream::in);

    if (!input)
        cout<<"No input file found, check file path!!"<<endl;
    else{
        Graph myGraph(inputFileName);
        MST myMST(myGraph);
        int initialNodeIndex = 0;
        vector<int> minmumSpanningTree = myMST.Path(initialNodeIndex);
        cout << "second time" << endl;

        minmumSpanningTree = myMST.Path(3);

        cout<<"Minimum spanning tree is:"<<endl;
        for (auto it=minmumSpanningTree.begin();it!=minmumSpanningTree.end();++it)
            cout<<*it<<" ";
        cout<<endl;
        float currentWeight = myMST.PathSize(0);
        if (currentWeight > 0)
        {
            cout<<"Weight of minimum spanning tree = "<<currentWeight<<endl;
        }
        else
            cout<<"No minimum spanning tree found."<<endl;
    }
    
    return 0;
}

