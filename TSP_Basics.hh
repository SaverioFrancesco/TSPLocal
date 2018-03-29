// File TSP_Basics.hh
#ifndef TSP_BASICS_HH
#define TSP_BASICS_HH

#include "TSP_Data.hh"

class TSP_State
{  
  friend ostream& operator<<(ostream& os, const TSP_State& st);
  friend bool operator==(const TSP_State& st1, const TSP_State& st2);
public:
  TSP_State(const TSP_Input &in);
  TSP_State& operator=(const TSP_State& s);
  unsigned operator[](unsigned i) const { return positions[i]; }
  unsigned& operator[](unsigned i) { return positions[i]; }
  
  TSP_Input const &getInput() const{ return in;} 

protected:
  const TSP_Input & in;  
  vector<unsigned> positions;
};

class TSP_Swap
{
  friend bool operator==(const TSP_Swap& m1, const TSP_Swap& m2);
  friend bool operator!=(const TSP_Swap& m1, const TSP_Swap& m2);
  friend bool operator<(const TSP_Swap& m1, const TSP_Swap& m2);
  friend ostream& operator<<(ostream& os, const TSP_Swap& c);
  friend istream& operator>>(istream& is, TSP_Swap& c);
 public:
  TSP_Swap(unsigned pos1 = 0, unsigned pos2 = 0);
  unsigned p1, p2;
};
#endif

