// File TSP_Basics.cc
#include "TSP_Basics.hh"

TSP_State::TSP_State(const TSP_Input &my_in) 
  : in(my_in)
{
  // Insert the code that initialized the data structure of the
  // state object based on the input object	



}

TSP_State& TSP_State::operator=(const TSP_State& st)
{
  // Insert the code that copies all data structures of the
  // state object from the ones of the parameter out
  // (excluding the reference to the input object, that is constant)
  //this->in=st.in;
  this->positions= st.positions;


  return *this;
}
  
bool operator==(const TSP_State& st1, const TSP_State& st2)
{
  // Insert the code that compares two states (this is used by the tester)
  unsigned i;
  for (i = 0; i < st1.in.get_num_nodes(); i++)
    if (st1[i] != st2[i])
      return false;
  return true;
}


ostream& operator<<(ostream& os, const TSP_State& st)
{
  // Insert the code that writes the state object (for debugging)
  unsigned i;
  for (i = 0; i < st.in.get_num_nodes(); i++)
    os << st[i] << " ";
  return os;
}


TSP_Swap::TSP_Swap(unsigned pos1, unsigned pos2)
{

  p1 = pos1;
  p2 = pos2;
  // Insert the code that initialize the move

}

bool operator==(const TSP_Swap& sq1, const TSP_Swap& sq2)
{
  // Insert the code that checks if two moves are identical
  return sq1.p1 == sq2.p1 && sq1.p2 == sq2.p2;
}

bool operator!=(const TSP_Swap& sq1, const TSP_Swap& sq2)
{
  // Insert the code that checks if two moves are different
  return sq1.p1 != sq2.p1 || sq1.p2 != sq2.p2;
}

bool operator<(const TSP_Swap& sq1, const TSP_Swap& sq2)
{
  // Insert the code that checks if one move precedes another one
  // (in any selected order)
  return sq1.p1 < sq2.p1 || (sq1.p1 == sq2.p1 && sq1.p2 < sq2.p2);
}

istream& operator>>(istream& is, TSP_Swap& sq)
{
  // Insert the code that read a move
  char ch;
  is >> ch >> sq.p1 >> ch >> sq.p2 >> ch;
  return is;
}

ostream& operator<<(ostream& os, const TSP_Swap& sq)
{
  // Insert the code that writes a move
  os << "<" << sq.p1 << "," << sq.p2 << ">";
  return os;
}
