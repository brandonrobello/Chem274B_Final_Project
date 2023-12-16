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
#include "COVID_edit.h"

int main(){
    srand(static_cast<unsigned int>(time(0)));

    string CAframe_outfile_path = "Test_COVID_CAframe_output.txt";
    string CAcellState_outfile_path = "Test_COVID_CAcellState_output.txt";
    
    // Define the transition states
    CellularAutomata COVID_test_CA;
    VaccinationRule VacRule(0.5); // 25% vaccination rate
    InfectionRule InfectRule(0.9, 0.25); // 70% infection rate and 0.5 immunity multiplier for vaccination
    recoveryRule RecovRule(0.30); //50% recover rate
    ReinfectionRule ReinfectRule(0.7, 0.25); // 70% infection rate and 0.5 recovery immunity multiplier for vaccination

    vector<Rule*> rules;
    rules.push_back(&ReinfectRule);
    rules.push_back(&VacRule);
    rules.push_back(&InfectRule);
    rules.push_back(&RecovRule);

    // Setup the CA
    COVID_test_CA.setup_dimension(2, 9, 9); // 2 dims, 9x9 matrix
    COVID_test_CA.setup_neighborhood(MOORE); // Moore Neighborhood
    COVID_test_CA.set_boundtype(STATIC, 1); // Static boundary with 1 radius

    // Initialize states
    COVID_test_CA.init_CA_state(0); // Initialize all states to 0 empty space
    COVID_test_CA.init_CA_stateWprob(1, 0.50); // Initialize to 50% healthy individuals
    COVID_test_CA.init_CA_stateWprob(3, 0.1); // Initialize 5% of cells as infected
    
    
    

    // Run the CA for a certain number of steps
    for (int step = 0; step < 5; step++)
    {
        cout << "Step " << step << endl;
        COVID_test_CA.record_CAframe(CAframe_outfile_path);
        COVID_test_CA.print();
        auto COVID_cellstates =  COVID_test_CA.query_cellState();
        cout << "Cell Query cout " << step << endl;
        for (auto& state : COVID_cellstates) {
        
        cout << state.first << "," << state.second << "\t";
        }
        cout << endl;
        COVID_test_CA.record_cellState(CAcellState_outfile_path);

        COVID_test_CA.update(rules);                
    }

    
return 0;
}




/*
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
    COVID_test_CA.init_CA_state(0);
    std::cout << "Wait for 3 seconds..." << endl;
    
    COVID_test_CA.init_CA_stateWprob(3, 0.20);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    COVID_test_CA.init_CA_stateWprob(4, 0.20);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    COVID_test_CA.init_CA_stateWprob(2, 0.025);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    COVID_test_CA.init_CA_stateWprob(1, 0.025);
    
    

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

*/