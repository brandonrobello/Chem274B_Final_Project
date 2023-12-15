#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <memory> // For std::unique_ptr
using namespace std;
#include "myCA_edit.h"
#include "COVID.h"

int main(){

    CellularAutomata COVID_test_CA;
    string CAframe_outfile_path = "Test_COVID_CAframe_output.txt";
    string CAcellState_outfile_path = "Test_COVID_CAcellState_output.txt";
    
    // Define the transition states
    CovidSusceptibilityRule rule;

    vector<Rule*> rules;
    rules.push_back(&rule);
    ;

    // Setup the CA
    COVID_test_CA.setup_dimension(2, 9, 9);
    COVID_test_CA.setup_neighborhood(MOORE);
    COVID_test_CA.set_boundtype(STATIC, 1);

    // Initialize states
    COVID_test_CA.init_CA_stateWprob(0, 0.20);
    std::cout << "Wait for 4 seconds..." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    COVID_test_CA.init_CA_stateWprob(1, 0.20);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    COVID_test_CA.init_CA_stateWprob(2, 0.20);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    COVID_test_CA.init_CA_stateWprob(3, 0.20);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    COVID_test_CA.init_CA_stateWprob(4, 0.20);
    
    

    // Run the CA for a certain number of steps
    for (int step = 0; step < 5; step++)
    {
        
        cout << "Step " << step << endl;
        COVID_test_CA.record_CAframe(CAframe_outfile_path);
        COVID_test_CA.print();
        auto COVID_cellstates =  COVID_test_CA.query_cellState();
        for (auto& state : COVID_cellstates) {
        
        cout << state.first << "," << state.second << "\t";
        }
        cout << endl;
        COVID_test_CA.record_cellState(CAcellState_outfile_path);

        COVID_test_CA.update(rules);                
    }
    
return 0;
}