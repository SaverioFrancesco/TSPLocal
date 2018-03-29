EASYLOCAL = ../easylocal-3
FLAGS = -std=c++11 -Wall #-O3 # -g
COMPOPTS = -I$(EASYLOCAL)/include $(FLAGS)
EASYLOCALLIB = -lEasyLocal -lboost_program_options
LINKOPTS = -L$(EASYLOCAL)/lib $(EASYLOCALLIB)  -pthread

SOURCE_FILES = TSP_Data.cc TSP_Basics.cc TSP_Helpers.cc  TSP_Main.cc
OBJECT_FILES = TSP_Data.o TSP_Basics.o TSP_Helpers.o TSP_Main.o
HEADER_FILES = TSP_Data.hh TSP_Basics.hh TSP_Helpers.hh  

TSP: $(OBJECT_FILES)
	g++ $(OBJECT_FILES) $(LINKOPTS) -o TSP

TSP_Data.o: TSP_Data.cc TSP_Data.hh
	g++ -c $(COMPOPTS) TSP_Data.cc

TSP_Basics.o: TSP_Basics.cc TSP_Basics.hh TSP_Data.hh
	g++ -c $(COMPOPTS) TSP_Basics.cc

TSP_Helpers.o: TSP_Helpers.cc TSP_Helpers.hh TSP_Basics.hh TSP_Data.hh
	g++ -c $(COMPOPTS) TSP_Helpers.cc

TSP_Main.o: TSP_Main.cc TSP_Helpers.hh TSP_Basics.hh TSP_Data.hh
	g++ -c $(COMPOPTS) TSP_Main.cc

clean:
	rm -f $(OBJECT_FILES) TSP

