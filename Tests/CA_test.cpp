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

int main() {

    int run_CA_selection = 3;

if (run_CA_selection == 1){
    CellularAutomata test_CA_majority;
    auto majorityrule = make_unique<MajorityRule>();

    vector<unique_ptr<Rule>> rules;
    rules.push_back(make_unique<MajorityRule>());

    string CAframe_outfile_path = "Test_CAframe_output_1.txt";

    test_CA_majority.setup_dimension(2, 9, 9);
    test_CA_majority.setup_neighborhood(MOORE);
    test_CA_majority.set_boundtype(STATIC, 1);
    test_CA_majority.init_CA_state(0);
    test_CA_majority.init_CA_stateWprob(2, 0.45);

    for (int step = 0; step < 2; step++) {
        cout << "Step " << step << " Frame:" << endl;
        test_CA_majority.print();
        test_CA_majority.record_CAframe(CAframe_outfile_path);

        // Convert unique_ptr to raw pointers for the update function
        vector<Rule*> raw_rules;
        for (auto& rule : rules) {
            raw_rules.push_back(rule.get());
        }

        test_CA_majority.update(raw_rules);
        cout << "After update and swap, Frame:" << endl;
        test_CA_majority.print();
    }
}

if (run_CA_selection == 2){
    CellularAutomata test_CA;
    string CAframe_outfile_path = "Test_CAframe_output_2.txt";

    
    // Define the transition states f
    vector<int> transitionStates = {0, 1, 2, 3}; // Example sequence
    StraightConditionalRule straightRule(transitionStates);

    vector<Rule*> rules;
    rules.push_back(&straightRule);

    // Setup the CA
    test_CA.setup_dimension(2, 9, 9);
    test_CA.setup_neighborhood(MOORE);
    test_CA.set_boundtype(STATIC, 1);

    // Initialize states
    test_CA.init_CA_stateWprob(0, 0.25);
    std::cout << "Wait for 3 seconds...";
    // Wait for 3 seconds
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "...3";
    test_CA.init_CA_stateWprob(1, 0.25);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "...3";
    test_CA.init_CA_stateWprob(2, 0.25);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "...3";
    test_CA.init_CA_stateWprob(3, 0.25);
    std::cout << "Continuing execution." << std::endl;

    // Run the CA for a certain number of steps
    for (int step = 0; step < 10; step++)
    {
        cout << "Step " << step << " Before Update:" << endl;
        test_CA.print();
        test_CA.record_CAframe(CAframe_outfile_path);

        test_CA.update(rules);

        cout << "Step " << step << " After Update:" << endl;
        test_CA.print();
    }
}

if (run_CA_selection == 3){
    CellularAutomata test_CA;
    string CAframe_outfile_path = "Test_CAframe_output_3.txt";

    
    // Define the transition states
    vector<int> transitionStates1 = {0, 3}; // Example sequenc
    StraightConditionalRule straightRule1(transitionStates1);
     vector<int> transitionStates2 = {100, 1}; // Example sequenc
    StraightConditionalRule straightRule2(transitionStates2);

    vector<Rule*> rules;
    rules.push_back(&straightRule1);
    rules.push_back(&straightRule2);

    // Setup the CA
    test_CA.setup_dimension(2, 9, 9);
    test_CA.setup_neighborhood(MOORE);
    test_CA.set_boundtype(STATIC, 1);

    // Initialize states
    test_CA.init_CA_stateWprob(0, 0.50);
    std::cout << "Wait for 3 seconds...";
    // Wait for 3 seconds
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "...3";
    test_CA.init_CA_stateWprob(100, 0.50);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    

    // Run the CA for a certain number of steps
    for (int step = 0; step < 2; step++)
    {
        cout << "Step " << step << " Before Update:" << endl;
        test_CA.print();
        test_CA.record_CAframe(CAframe_outfile_path);

        test_CA.update(rules);

        cout << "Step " << step << " After Update:" << endl;
        test_CA.print();
    }
}


    return 0;
}