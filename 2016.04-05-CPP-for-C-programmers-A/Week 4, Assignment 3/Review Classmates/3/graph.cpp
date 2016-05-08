#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <fstream>

using std::vector;
using std::cout;
using std::endl;
using std::pair;
using std::set;
using std::string;

// Base class for the edge
template <class T>
struct edge {
    unsigned int targ=0;
    T leng=0;
    edge() {}; 
    edge(unsigned int t, T l) : targ(t), leng(l) {}; 
};

// Base class for the graph
template <class T>
class graph {
  private:
    unsigned int sizeG = 0;  //size of vertices
    unsigned int sizeE = 0;  //size of edges
  public:
    vector< vector < edge<T> > > G;   // double vector of edges
    vector< T> node;
    
    graph (const unsigned int & sizeG);
    graph (const string & fileName);   //read file
    
    //constructor for random generator
    graph (const unsigned int & sizeG, const double & density, const T & rangeMin, const T & rangeMax);
    
    unsigned int V () const {return sizeG;}
    unsigned int E () const {return sizeE;}
    bool adjacent (const unsigned int & x, const unsigned int & y) const;
    void neighbors (const unsigned int & x) const;
    bool add (const unsigned int & x, const unsigned int & y);
    bool add (const unsigned int & x, const unsigned int & y, const T & v);
    bool del (const unsigned int & x, const unsigned int & y);
    bool set_edge_value (const unsigned int & x, const unsigned int & y, const T & v);
    T get_edge_value (const unsigned int & x, const unsigned int & y) const;
    bool set_node_value (const unsigned int & x, const T &  v);
    T get_node_value (const unsigned int & x) const;
    
    void setAllNodesMax(const unsigned int & M);
    void primaMST(unsigned int n);
};

//=====================================================================
//=====================================================================
//=====================================================================
//Implementation

template <class T>
graph<T>::graph (const unsigned int & s) {
  sizeG = s;
  G = vector<vector <edge <T> > >(sizeG, vector<edge <T> > ());
  node = vector<T>(sizeG, 0);
}

template <class T>
graph<T>::graph (const unsigned int & s, const double & density, const T & rangeMin, const T & rangeMax) {
  std::random_device rd;
  std::mt19937 rng(rd());
  sizeG = s;
  G = vector<vector <edge <T> > >(sizeG, vector<edge <T> > ());
  node = vector<T>(sizeG, 0);
  std::uniform_real_distribution<T> uni_range(rangeMin,rangeMax);
  std::uniform_real_distribution<T> uni_dens(0,1);

  for (unsigned int i=0; i < sizeG ; i++) {
    for (unsigned int j=i+1; j < sizeG ; j++) {
      const double randomDen = uni_dens(rng);
      if (randomDen <= density) {
        T genRange = uni_range(rng);
        add(i, j, genRange);
      } 
    }
  }
}
template <class T>
graph<T>::graph (const string & fileName) {
  std::ifstream fileRead (fileName);
  fileRead >> sizeG;
  G = vector<vector <edge <T> > >(sizeG, vector<edge <T> > ());
  node = vector<T>(sizeG, 0);
  int from=0, to=0;
  T weight;
  unsigned int counter = 0;
  while (fileRead >> from >> to >> weight) {
    this->add (from, to, weight);
    counter++;
  }
  cout<<"Imported "<<counter<<" edges"<<endl;
  fileRead.close();
}

template <class T>
bool graph<T>::adjacent (const unsigned int & x, const unsigned int & y) const {
  for (const auto e : G[x]) {
    if (e.targ == y) return true;
  }
  return false;
}

template <class T>
void graph<T>::neighbors (const unsigned int & x) const {
  cout<<"Neighbours of ("<<x<<") are: "; 
  for (const auto e : G[x]) {
    cout<<e.targ<<" ";
  };
  cout<<endl;
}

template <class T>
bool graph<T>::add (const unsigned int & x, const unsigned int & y) {
  bool noEdgeX2Y = true;
  for (const auto e : G[x]) {
    if (y==e.targ) noEdgeX2Y = false;
  }
  
  bool noEdgeY2X = true;
  for (const auto e : G[y]) {
    if (x==e.targ) noEdgeY2X = false;
  }
  
  if (noEdgeX2Y && noEdgeY2X) {
    const edge<T> ex(x,0);
    const edge<T> ey(y,0);
    G[x].push_back(ey);
    G[y].push_back(ex);
    sizeE++;
    return true;
  } else {
    return false;
  }
}

template <class T>
bool graph<T>::add (const unsigned int & x, const unsigned int & y, const T & v) {
  const auto ret1 = add(x,y);
  const auto ret2 = set_edge_value(x, y, v);
  return (ret1&&ret2);
}

template <class T>
bool graph<T>::del (const unsigned int & x, const unsigned int & y) {
  bool delX = false;
  bool delY = false;
  
  for (unsigned int i=0; i < G[x].size(); i++) {
    if (G[x][i].targ==y) {
      delX = true;
      G[x].erase (G[x].begin()+i);
      break;
    }
  }
  
  for (unsigned int i=0; i < G[y].size(); i++) {
    if (G[y][i].targ==x) {
      delY = true;
      G[y].erase(G[y].begin()+i);
      break;
    }
  }
  if (delX && delY) return true;
  else return false;
}

template <class T>
bool graph<T>::set_edge_value (const unsigned int & x, const unsigned int & y, const T & v) {
  bool setX = false;
  bool setY = false;
  
  for (unsigned int i=0; i < G[x].size(); i++) {
    if (G[x][i].targ==y) {
      setX = true;
      G[x][i].leng = v;
      break;
    }
  }
  
  for (unsigned int i=0; i < G[y].size(); i++) {
    if (G[y][i].targ==x) {
      setY = true;
      G[y][i].leng = v;
      break;
    }
  }
  
  if (setX && setY) return true;
  else return false;
}

template <class T>
T graph<T>::get_edge_value (const unsigned int & x, const unsigned int & y) const {
  for (unsigned int i=0; i < G[x].size(); i++) {
    if (G[x][i].targ==y) {
      return G[x][i].leng;
    }
  }
  return 0;
}

template <class T>
bool graph<T>::set_node_value (const unsigned int & x, const T & v) {
  if (x < sizeG) {
    node[x] = v;
    return true;
  } else {
    return false;
  }
}

template <class T>
T graph<T>::get_node_value (const unsigned int & x) const {
  if (x < sizeG) {
    return node[x];
  } else {
    return 0;
  }
}

template <class T>
void graph<T>::setAllNodesMax(const unsigned int & M) {
  for (unsigned int i=0; i < sizeG; i++) node[i]=M;
}

template <class T>
void graph<T>::primaMST(unsigned int u) {
  setAllNodesMax(99999);
  set < unsigned int > mstSet;
  vector < pair < int, int > >  pathE;    // result path
  vector < T >  pathC;    // result costs
  T costE = 0.;  //result costs
  mstSet.insert(u);
  set_node_value(u,0);
  while (mstSet.size() < sizeG) {
    // go through all adjacent nodes and update their values
    for (const auto e : G[u]) {
      if (mstSet.find(e.targ) == mstSet.end()) {
        node[e.targ] = node[u] + e.leng;
      }
    };
    //find minimal length in all adjacent nodes
    T minVal = 99999.;
    int minID = 99999;
    pair <int, int > pathS;
    T curPathCost = 0.;
    for (const auto g : mstSet) {
      for (const auto e : G[g]) {
        if (mstSet.find(e.targ) == mstSet.end()) {
          if ((e.leng) < minVal ) {
            minVal = e.leng;
            minID = e.targ;
            pathS = {g, e.targ};
            curPathCost = e.leng;
          }
        }
      };
    }
    u = minID;
    mstSet.insert(u);
    pathE.push_back(pathS);
    pathC.push_back(curPathCost);
    costE += curPathCost;
  }
  cout<<"From->To"<<endl;
  for (const auto e : pathE) {
    std::cout<<e.first<<"->"<<e.second<<endl;
  }
  cout<<"========\nTotal costs: "<<costE<<endl;
}

//=====================================================================
//=====================================================================
//=====================================================================
//Main program

int main(int argc, char **argv) {
  
  std::string fileName;
  if (argc > 1) {
    fileName = argv[1];
    std::cout<<fileName<<std::endl;
    graph<double> g1(fileName);
    g1.primaMST(0);
  } else {
    cout<<"Usage: graph fileName"<<endl;
  }
  
  return 0;
}

