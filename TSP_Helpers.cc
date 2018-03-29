// File TSP_Helpers.cc
#include "TSP_Helpers.hh"

int TSP_CostComponent1::ComputeCost(const TSP_State& st) const
{
  unsigned cost = 0;
  // Insert the code that computes the cost for component 1 
  // of state st
	throw logic_error("TSP_CostComponent1::ComputeCost not implemented yet");	
  return cost;
}
          
void TSP_CostComponent1::PrintViolations(const TSP_State& st, ostream& os) const
{
  // Insert the code that prints the violations of component 1 
  // of state st
	throw logic_error("TSP_CostComponent1::PrintViolations not implemented yet");	
}

int TSP_CostComponent2::ComputeCost(const TSP_State& st) const
{ 
  unsigned cost = 0;
  // Insert the code that computes the cost for component 2
  // of state st
	throw logic_error("TSP_CostComponent2::ComputeCost not implemented yet");	
  return cost;
}
 
void TSP_CostComponent2::PrintViolations(const TSP_State& st, ostream& os) const
{
  // Insert the code that prints the violations of component 1 
  // of state st
	throw logic_error("TSP_CostComponent2::PrintViolations not implemented yet");	
}

// constructor
TSP_StateManager::TSP_StateManager(const TSP_Input & pin) 
  : StateManager<TSP_Input,TSP_State>(pin, "TSPStateManager")  {} 
// initial state builder (random rooms)
void TSP_StateManager::RandomState(TSP_State& st) 
{
// Insert the code that creates a random state in object st
	vector<bool> tag(st.getInput().get_num_nodes(), false);
  unsigned i, j;
  
  for (j = 0; j < st.getInput().get_num_nodes(); j++)
    { 
      do
      i = Random::Int(0, st.getInput().get_num_nodes() - 1);
      while (tag[i]);
      tag[i] = true;
      st[j] = i;
    }
} 
bool TSP_StateManager::CheckConsistency(const TSP_State& st) const
{
  
  unsigned j;
  vector<bool> tag(st.getInput().get_num_nodes(), false);
  for (j = 0; j < st.getInput().get_num_nodes(); j++)
    if (tag[st[j]])
    return false;
  else
      tag[st[j]] = true;  
  	
  return true;
}

/*****************************************************************************
 * Output Manager Methods
 *****************************************************************************/

void TSP_OutputManager::InputState(TSP_State& st, const TSP_Output& TSP) const 
{
  // Insert the code that "translates" an output object to a state object
	throw logic_error("TSP_OutputManager::InputState not implemented yet");	
}

void TSP_OutputManager::OutputState(const TSP_State& st, TSP_Output& TSP) const 
{
  // Insert the code that "translates" a state object to an output object
	throw logic_error("TSP_OutputManager::OutputState not implemented yet");	
}


/*****************************************************************************
 * TSP_Swap Neighborhood Explorer Methods
 *****************************************************************************/

// initial move builder
void TSP_SwapNeighborhoodExplorer::RandomMove(const TSP_State& st, TSP_Swap& sw) const  throw(EmptyNeighborhood)
{
  // insert the code that writes a random move on mv in state st
	sw.p1 = Random::Int(0, st.getInput().get_num_nodes() - 1);
  sw.p2 = Random::Int(0, st.getInput().get_num_nodes() - 2);
  if (sw.p2 >= sw.p1)
   sw.p2++;
  if (sw.p1 > sw.p2) // swap p1 and p2 so that p1 < p2
    swap(sw.p1, sw.p2);
} 

// check move feasibility
bool TSP_SwapNeighborhoodExplorer::FeasibleMove(const TSP_State& st, const TSP_Swap& sw) const
{
  // Insert the code that check is move mv is legal in state st 
  // (return true if legal, false otherwise)
	return sw.p1 < sw.p2;
} 

// update the state according to the move 
void TSP_SwapNeighborhoodExplorer::MakeMove(TSP_State& st, const TSP_Swap& sw) const
{
  // Insert the code that modify the state st based on the application of move mv

  swap(st[sw.p1], st[sw.p2]);
}  

void TSP_SwapNeighborhoodExplorer::FirstMove(const TSP_State& st, TSP_Swap& sw) const  throw(EmptyNeighborhood)
{
  // Insert the code the generate the first move in the neighborhood and store it in mv
	sw.p1 = 0; 
  sw.p2 = 1;
}

bool TSP_SwapNeighborhoodExplorer::NextMove(const TSP_State& st, TSP_Swap& sw) const
{
  // Insert the code that generate the move that follows mv in the neighborhood, and writes
  // it back in mv. Return false if mv is already the last move. 
	if (sw.p2 < st.getInput().get_num_nodes() - 1) 
      {
      sw.p2++;
      return true;
      }
    else if (sw.p1 < st.getInput().get_num_nodes() - 2)
      { 
      sw.p1++; 
      sw.p2 = sw.p1 + 1; 
      return true;
      }
    else
      return false;
}

void TSP_SwapDeltaCostComponent1::PrintViolations(const TSP_State& st, ostream& os) const
{
  unsigned i, j;
  for (i = 0; i < st.getInput().get_num_nodes() - 1; i++)
    for (j = i + 1; j < st.getInput().get_num_nodes(); j++)
      if (static_cast<int>(j - i) == abs(static_cast<int>(st[i]) - static_cast<int>(st[j])))
      os << "Queens in position (" << i << "," << st[i] << ") and (" 
         << j << "," << st[j] << ") attack each other" << endl;
}
          
int TSP_SwapDeltaCostComponent1::ComputeDeltaCost(const TSP_State& st, const TSP_Swap& sw) const
{
  //int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	unsigned i;
  int delta_violations = 0;
  for (i = 0; i < st.getInput().get_num_nodes(); i++)
    {
      if (i != sw.p1 && i != sw.p2)
    {
      int ii = static_cast<int>(i), p1 = static_cast<int>(sw.p1), p2 = static_cast<int>(sw.p2);
      if (abs(ii - p1) == abs(static_cast<int>(st[i]) - static_cast<int>(st[p1])))
        delta_violations--;
      if (abs(ii - p2) == abs(static_cast<int>(st[i]) - static_cast<int>(st[p2])))
        delta_violations--;
      if (abs(ii - p1) == abs(static_cast<int>(st[i]) - static_cast<int>(st[p2])))
        delta_violations++;
      if (abs(ii - p2) == abs(static_cast<int>(st[i]) - static_cast<int>(st[p1])))
        delta_violations++;
       }
   }
  return delta_violations;
}

