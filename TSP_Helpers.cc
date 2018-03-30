// File TSP_Helpers.cc
#include "TSP_Helpers.hh"

int TSP_CostComponent1::ComputeCost(const TSP_State& st) const
{
  unsigned cost = 0;
  // Insert the code that computes the cost for component 1 
  // of state st
  unsigned i;
  for (i = 0; i < st.getInput().get_num_nodes() - 1; i++)
    if (st.getInput().get_arc_cost(st.get_positions(i), st.get_positions(i+1)) == 0)
      cost++;
    
  if (st.getInput().get_arc_cost(st.get_positions(i), st.get_positions(0)) == 0)
    cost++;
  //throw logic_error("TSP_CostComponent1::ComputeCost not implemented yet");	
  return cost;
}
          
void TSP_CostComponent1::PrintViolations(const TSP_State& st, ostream& os) const
{
  // Insert the code that prints the violations of component 1 
  // of state st
  unsigned i;
  for (i = 0; i < st.getInput().get_num_nodes() - 1; i++)
    if (st.getInput().get_arc_cost(st.get_positions(i), st.get_positions(i+1)) == 0)
      cout << "Arc between " << st.get_positions(i) << " and " << st.get_positions(i+1) << " does not exist" << endl;
    
  if (st.getInput().get_arc_cost(st.get_positions(i), st.get_positions(0)) == 0)
    cout << "Arc between " << st.get_positions(i) << " and " << st.get_positions(0) << " does not exist" << endl;
	//throw logic_error("TSP_CostComponent1::PrintViolations not implemented yet");	
}

int TSP_CostComponent2::ComputeCost(const TSP_State& st) const
{ 
  unsigned cost = 0;
  // Insert the code that computes the cost for component 2
  // of state st
  unsigned i;
  for (i = 0; i < st.getInput().get_num_nodes() - 1; i++)
    cost = cost + st.getInput().get_arc_cost(st.get_positions(i), st.get_positions(i+1));
  cost = cost + st.getInput().get_arc_cost(st.get_positions(i), st.get_positions(0));
	
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

void TSP_OutputManager::InputState(TSP_State& st, const TSP_Output& out) const 
{
  
  
  //adjacencyMatrix.resize(num_nodes);

  for (unsigned s = 0; s < st.getInput().get_num_nodes(); s++)
    st.set_positions(s, out.get_tcp_path(s));

}

void TSP_OutputManager::OutputState(const TSP_State& st, TSP_Output& out) const 
{
  unsigned i;
  for (i = 0; i < st.getInput().get_num_nodes(); i++)
      out.set_tcp_path(i,st.get_positions(i));
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
 
}
          
int TSP_SwapDeltaCostComponent1::ComputeDeltaCost(const TSP_State& st, const TSP_Swap& sw) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	/* unsigned i;
  int delta_violations = 0;
  for (i = 0; i < st.getInput().get_num_nodes()-1; i++)
  {
    delta_violations+= st.getInput().get_arc_cost(st[i], st[i+1]);
  }
  return delta_violations; */
  
  // A -> b -> c -> D -> e -> f -> A
  // swap <0, 3> (A with D)
  // D -> b -> c -> A -> e -> f -> D
  // check whether the new arcs modify the violations (adding/removing arcs with cost 0)
  int a = sw.p1;
  int d = sw.p2;
  int n = st.getInput().get_num_nodes();
  int b = (a + 1 < n  ? a + 1 : 0);
  int f = (a - 1 >= 0 ? a - 1 : n - 1);
  int c = (d - 1 >= 0 ? d - 1 : n - 1);
  int e = (d + 1 < n  ? d + 1 : 0);
  
  if (st.getInput().get_arc_cost(st.get_positions(a), st.get_positions(b)) == 0) // was already violated
    if (st.getInput().get_arc_cost(st.get_positions(d), st.get_positions(b)) != 0) // after swap, won't violate
      cost--;  // then decrease cost
  if (st.getInput().get_arc_cost(st.get_positions(a), st.get_positions(b)) != 0) // not already violated
    if (st.getInput().get_arc_cost(st.get_positions(d), st.get_positions(b)) == 0) // after swap, will violate
      cost++;  // then increase cost
  
  if (st.getInput().get_arc_cost(st.get_positions(f), st.get_positions(a)) == 0)
    if (st.getInput().get_arc_cost(st.get_positions(f), st.get_positions(d)) != 0)
      cost--;
  if (st.getInput().get_arc_cost(st.get_positions(f), st.get_positions(a)) != 0)
    if (st.getInput().get_arc_cost(st.get_positions(f), st.get_positions(d)) == 0)
      cost++;
  
  if (st.getInput().get_arc_cost(st.get_positions(c), st.get_positions(d)) == 0)
    if (st.getInput().get_arc_cost(st.get_positions(c), st.get_positions(a)) != 0)
      cost--;
  if (st.getInput().get_arc_cost(st.get_positions(c), st.get_positions(d)) != 0)
    if (st.getInput().get_arc_cost(st.get_positions(c), st.get_positions(a)) == 0)
      cost++;
  
  if (st.getInput().get_arc_cost(st.get_positions(d), st.get_positions(e)) == 0)
    if (st.getInput().get_arc_cost(st.get_positions(a), st.get_positions(e)) != 0)
      cost--;
  if (st.getInput().get_arc_cost(st.get_positions(d), st.get_positions(e)) != 0)
    if (st.getInput().get_arc_cost(st.get_positions(a), st.get_positions(e)) == 0)
      cost++;
  
  
  
  return cost;
}


void TSP_SwapDeltaCostComponent2::PrintViolations(const TSP_State& st, ostream& os) const
{
 
}

int TSP_SwapDeltaCostComponent2::ComputeDeltaCost(const TSP_State& st, const TSP_Swap& sw) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 2 for move mv in state st
  // A -> b -> c -> D -> e -> f -> A
  // swap <0, 3> (A with D)
  // D -> b -> c -> A -> e -> f -> D
  // removed costs: A -> b, f -> A, c -> D, D -> e
  // added costs:   D -> b, f -> D, c -> A, A -> e
  int a = sw.p1;
  int d = sw.p2;
  int n = st.getInput().get_num_nodes();
  int b = (a + 1 < n  ? a + 1 : 0);
  int f = (a - 1 >= 0 ? a - 1 : n - 1);
  int c = (d - 1 >= 0 ? d - 1 : n - 1);
  int e = (d + 1 < n  ? d + 1 : 0);
  
  if (abs(a - b) > 1)
    cost = cost
      - st.getInput().get_arc_cost(st.get_positions(a), st.get_positions(b))
      - st.getInput().get_arc_cost(st.get_positions(f), st.get_positions(a))
      - st.getInput().get_arc_cost(st.get_positions(c), st.get_positions(d))
      - st.getInput().get_arc_cost(st.get_positions(d), st.get_positions(e))
      + st.getInput().get_arc_cost(st.get_positions(d), st.get_positions(b))
      + st.getInput().get_arc_cost(st.get_positions(f), st.get_positions(d))
      + st.getInput().get_arc_cost(st.get_positions(c), st.get_positions(a))
      + st.getInput().get_arc_cost(st.get_positions(a), st.get_positions(e));
  else // A -> D -> e -> ... -> f -> A
    cost = cost
      - st.getInput().get_arc_cost(st.get_positions(a), st.get_positions(d))
      - st.getInput().get_arc_cost(st.get_positions(f), st.get_positions(a))
      - st.getInput().get_arc_cost(st.get_positions(d), st.get_positions(e))
      + st.getInput().get_arc_cost(st.get_positions(a), st.get_positions(e))
      + st.getInput().get_arc_cost(st.get_positions(f), st.get_positions(d))
      + st.getInput().get_arc_cost(st.get_positions(d), st.get_positions(a));
      
    
  return cost;
}

