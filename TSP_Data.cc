// File TSP_Data.cc
#include "TSP_Data.hh"
#include <fstream>
#include <cassert>

TSP_Input::TSP_Input(string file_name)
{
  // Insert the code that reads the input from the file 
  // and stored it into the data structures of the object 

  ifstream is(file_name.c_str());
  assert(!is.fail());
  
  //unsigned num_nodes;
  is >> num_nodes; 

  adjacencyMatrix.resize(num_nodes);

  for (unsigned s = 0; s < num_nodes; s++)
  {
    for (unsigned k = 0; k < num_nodes; k++)
      is>> adjacencyMatrix[s][k];   
  }


}

ostream& operator<<(ostream& os, const TSP_Input& pa)
{
  // Insert the code that write the input object (needed for debugging purposes)

  unsigned u= pa.get_num_nodes();
  
  for (unsigned s = 0; s < u; s++)
  {
    for (unsigned k = 0; k < u; k++)
      os<< pa.get_arc_cost(s,k);
  }


  //throw logic_error("operator<<(ostream& os, const TSP_Input& pa) not implemented yet");	
  return os;
}

TSP_Output::TSP_Output(const TSP_Input& my_in)
  : in(my_in)
{
  // Insert the code that initialize the data structures of the
  // output object based in the input object

  unsigned u=my_in.get_num_nodes();
  tcp_path.resize(u);

  for (unsigned i = 0; i < u; ++i)
  {
    /* code */
    tcp_path[i]=i;
  }
  //cerr << "TSP_Output::TSP_Output(const TSP_Input&) not implemented yet" << endl;
}

TSP_Output& TSP_Output::operator=(const TSP_Output& out)
{
  // Insert the code that copies all data structures of the
  // output object from the ones of the parameter out
  // (excluding the reference to the input object, that is constant)

  this->tcp_path=out.tcp_path;

  //throw logic_error("TSP_Output::operator= not implemented yet");	
  return *this;
}

template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

ostream& operator<<(ostream& os, const TSP_Output& out)
{ 
 // Insert the code that writes the output object
  //
  
  os << out.tcp_path ;
  
  

  //throw logic_error("operator<<(ostream& os, const TSP_Output& out) not implemented yet");		
  return os;
}

istream& operator>>(istream& is, TSP_Output& out)
{
  // Insert the code that reads the output object
  throw logic_error("operator>>(istream& is, TSP_Output& out) not implemented yet");	
  return is;
}
