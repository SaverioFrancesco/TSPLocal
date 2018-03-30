// File TSP_Data.hh
#ifndef TSP_DATA_HH
#define TSP_DATA_HH

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class TSP_Output;

class TSP_Input 
{
  friend class TSP_Output;
  friend ostream& operator<<(ostream& os, const TSP_Input& bs);
public:
  TSP_Input(string file_name);
  // Insert your getters

  vector<vector<int>> get_adjacencyMatrix() const { return adjacencyMatrix;};
  int const get_arc_cost(unsigned i, unsigned j) const { return adjacencyMatrix[i][j];}
  unsigned const get_num_nodes() const { return num_nodes; };
  void set_arc_cost(unsigned i, unsigned j, int w) { adjacencyMatrix[i][j]=w; };

  //nb:: il primo const dice che num_nodes non cambia mai,
  // il secondo che questa procedura assicura che num_nodes non sarà cambiata durante l esecuzione.

protected:
  // Insert your data members
  vector<vector<int>> adjacencyMatrix;
  unsigned num_nodes;
  
};

class TSP_Output 
{
  friend ostream& operator<<(ostream& os, const TSP_Output& out);
  friend istream& operator>>(istream& is, TSP_Output& out);
public:
  TSP_Output(const TSP_Input& i);
  TSP_Output& operator=(const TSP_Output& out);
  // Insert your getters
  std::vector<unsigned> const & get_tcp_path() { return tcp_path; };
  void set_tcp_path(unsigned i, unsigned j) { tcp_path[i]=j;};
  unsigned const get_tcp_path(unsigned i) const { return tcp_path[i];}

protected:
  const TSP_Input& in;
  // Insert your data members
  vector<unsigned> tcp_path;
};
#endif
