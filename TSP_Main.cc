#include "TSP_Helpers.hh"

using namespace EasyLocal::Debug;

int main(int argc, const char* argv[])
{
  ParameterBox main_parameters("main", "Main Program options");

  // The set of arguments added are the following:
  
  Parameter<string> instance("instance", "Input instance", main_parameters); 
  Parameter<int> seed("seed", "Random seed", main_parameters);
  Parameter<string> method("method", "Solution method (empty for tester)", main_parameters);   
  Parameter<string> init_state("init_state", "Initial state (to be read from file)", main_parameters);
  Parameter<unsigned> observer("observer", "Attach the observers", main_parameters);
  Parameter<string> output_file("output_file", "Write the output to a file (filename required)", main_parameters);
 
  // 3rd parameter: false = do not check unregistered parameters
  // 4th parameter: true = silent
  CommandLineParameters::Parse(argc, argv, false, true);  

  if (!instance.IsSet())
    {
      cout << "Error: --main::instance filename option must always be set" << endl;
      return 1;
    }
 
  TSP_Input in(instance);

  cout << in;

  if (seed.IsSet())
    Random::Seed(seed);
  
  // cost components: second parameter is the cost, third is the type (true -> hard, false -> soft)
  TSP_CostComponent1 cc1(in, 1, true);
  //TSP_CostComponent2 cc2(in, 1, true);

  TSP_SwapDeltaCostComponent1 dcc1(in, cc1);
  //TSP_SwapDeltaCostComponent2 dcc2(in, cc2);

  // helpers
  TSP_StateManager TSP_sm(in);
  TSP_SwapNeighborhoodExplorer TSP_nhe(in, TSP_sm);

  TSP_OutputManager TSP_om(in);
  
  // All cost components must be added to the state manager
  TSP_sm.AddCostComponent(cc1);
 // TSP_sm.AddCostComponent(cc2);
  
  // All delta cost components must be added to the neighborhood explorer
  TSP_nhe.AddDeltaCostComponent(dcc1);
  //TSP_nhe.AddDeltaCostComponent(dcc2);
  
  // runners
  HillClimbing<TSP_Input, TSP_State, TSP_Swap> TSP_hc(in, TSP_sm, TSP_nhe, "TSP_SwapHillClimbing");
  SteepestDescent<TSP_Input, TSP_State, TSP_Swap> TSP_sd(in, TSP_sm, TSP_nhe, "TSP_SwapSteepestDescent");
  SimulatedAnnealing<TSP_Input, TSP_State, TSP_Swap> TSP_sa(in, TSP_sm, TSP_nhe, "TSP_SwapSimulatedAnnealing");

  // tester
  Tester<TSP_Input, TSP_Output, TSP_State> tester(in,TSP_sm,TSP_om);
  MoveTester<TSP_Input, TSP_Output, TSP_State, TSP_Swap> swap_move_test(in,TSP_sm,TSP_om,TSP_nhe, "TSP_Swap move", tester); 

  SimpleLocalSearch<TSP_Input, TSP_Output, TSP_State> TSP_solver(in, TSP_sm, TSP_om, "TSP solver");
  if (!CommandLineParameters::Parse(argc, argv, true, false))
    return 1;

  if (!method.IsSet())
    { // If no search method is set -> enter in the tester
      if (init_state.IsSet())
	    tester.RunMainMenu(init_state);
      else
	    tester.RunMainMenu();
    }
  else
    {

      if (method == string("SA"))
        {
          TSP_solver.SetRunner(TSP_sa);
        }
      else if (method == string("HC"))
        {
          TSP_solver.SetRunner(TSP_hc);
        }
      else // if (method.GetValue() == string("SD"))
        {
          TSP_solver.SetRunner(TSP_sd);
        }
      auto result = TSP_solver.Solve();
	  // result is a tuple: 0: solutio, 1: number of violations, 2: total cost, 3: computing time
      TSP_Output out = result.output;
      if (output_file.IsSet())
        { // write the output on the file passed in the command line
          ofstream os(static_cast<string>(output_file).c_str());
          os << out << endl;
          os << "Cost: " << result.cost.total << endl;
					os << "Time: " << result.running_time << "s " << endl;
          os.close();
        }
      else
        { // write the solution in the standard output
          cout << out << endl;
          cout << "Cost: " << result.cost.total << endl;
					cout << "Time: " << result.running_time << "s " << endl;					
        }
   }

   
  return 0;
}
