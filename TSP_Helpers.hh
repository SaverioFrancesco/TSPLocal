// File TSP_Helpers.hh
#ifndef TSP_HELPERS_HH
#define TSP_HELPERS_HH

#include "TSP_Basics.hh"
#include <easylocal/easylocal.hh>


using namespace EasyLocal::Core;

/***************************************************************************
 * State Manager 
 ***************************************************************************/

class TSP_CostComponent1 : public CostComponent<TSP_Input,TSP_State> 
{
public:
  TSP_CostComponent1(const TSP_Input & in, int w, bool hard) :    CostComponent<TSP_Input,TSP_State>(in,w,hard,"TSP_CostComponent1") 
  {}
  int ComputeCost(const TSP_State& st) const;
  void PrintViolations(const TSP_State& st, ostream& os = cout) const;
};

class  TSP_CostComponent2: public CostComponent<TSP_Input,TSP_State> 
{
public:
  TSP_CostComponent2(const TSP_Input & in, int w, bool hard) : CostComponent<TSP_Input,TSP_State>(in,w,hard,"TSP_CostComponent2") 
  {}
  int ComputeCost(const TSP_State& st) const;
  void PrintViolations(const TSP_State& st, ostream& os = cout) const;
};

class TSP_StateManager : public StateManager<TSP_Input,TSP_State> 
{
public:
  TSP_StateManager(const TSP_Input &);
  void RandomState(TSP_State&);   
  bool CheckConsistency(const TSP_State& st) const;
protected:
}; 

/***************************************************************************
 * TSP_Swap Neighborhood Explorer:
 ***************************************************************************/

class TSP_SwapDeltaCostComponent1
  : public DeltaCostComponent<TSP_Input,TSP_State,TSP_Swap>
{
public:
  TSP_SwapDeltaCostComponent1(const TSP_Input & in, TSP_CostComponent1& cc) 
    : DeltaCostComponent<TSP_Input,TSP_State,TSP_Swap>(in,cc,"TSP_SwapDeltaCostComponent1") 
  {}
  int ComputeDeltaCost(const TSP_State& st, const TSP_Swap& mv) const;
};

class TSP_SwapDeltaCostComponent2
  : public DeltaCostComponent<TSP_Input,TSP_State,TSP_Swap>
{
public:
  TSP_SwapDeltaCostComponent2(const TSP_Input & in, TSP_CostComponent2& cc) 
    : DeltaCostComponent<TSP_Input,TSP_State,TSP_Swap>(in,cc,"TSP_SwapDeltaCostComponent2") 
  {}
  int ComputeDeltaCost(const TSP_State& st, const TSP_Swap& mv) const;
};

class TSP_SwapNeighborhoodExplorer
  : public NeighborhoodExplorer<TSP_Input,TSP_State,TSP_Swap> 
{
public:
  TSP_SwapNeighborhoodExplorer(const TSP_Input & pin, StateManager<TSP_Input,TSP_State>& psm)  
    : NeighborhoodExplorer<TSP_Input,TSP_State,TSP_Swap>(pin, psm, "TSP_SwapNeighborhoodExplorer") {} 
  void RandomMove(const TSP_State&, TSP_Swap&) const throw(EmptyNeighborhood);          
  bool FeasibleMove(const TSP_State&, const TSP_Swap&) const;  
  void MakeMove(TSP_State&,const TSP_Swap&) const;             
  void FirstMove(const TSP_State&,TSP_Swap&) const throw(EmptyNeighborhood);  
  bool NextMove(const TSP_State&,TSP_Swap&) const;   
protected:
};

/***************************************************************************
 * Output Manager:
 ***************************************************************************/
class TSP_OutputManager
  : public OutputManager<TSP_Input,TSP_Output,TSP_State> 
{
public:
  TSP_OutputManager(const TSP_Input & pin)
    : OutputManager<TSP_Input,TSP_Output,TSP_State>(pin,"TSPOutputManager") {}
  void InputState(TSP_State&, const TSP_Output&) const;  
  void OutputState(const TSP_State&, TSP_Output&) const; 
}; 
#endif
