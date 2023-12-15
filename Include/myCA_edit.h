

#pragma once    // Ensures that this file is only included once
                // during compilation
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class Cell {
    private:
        int x; // The x position on the grid / position from center in the neighborhood (important for the Activation-Inhibition rule)
        int y; // The x position on the grid / position from center in the neighborhood (important for the Activation-Inhibition rule)
        int state_t0; // Intitial state of the cell 
        int state_tx; // Updated state of the cell

    public:
        Cell();
        //add copy constructor for neighborhood
        ~Cell();
        int getState_t0() const; // Method to get current state
        int setState_t0(int state); // Methof to set current state
        int getState_tx() const; // Method to get new state
        int setState_tx(int state); // Methof to set new state

        vector<int> getPosition() const; // Method to get x and y positions

        int cell_update(); // Method to swap state_tx and state_to, to make the new value (tx) the current value (t0)
        // Implemented to fulfill requirements for map in neighborhood
        bool operator<(const Cell& other) const;
        void set_x(int x);
        void set_y(int y);
        int get_x() const;
        int get_y() const;
};

struct Neighborhood
{   
    public:
    map<Cell, int> subgrid; // Store neighboring cells and their distances
    int dim;               // Number of cells in the subgrid
    Cell center_cell;       // Copy of the center cell of the neighborhood 
};

class Rule {
public:
    virtual int apply(Neighborhood &neighborhood) = 0;
    virtual ~Rule() {}
};

//Curtis


class CellularAutomata
{
    private:
        vector<vector<Cell>> grid;    // 3D grid structure that stores cell data type
        std::map<string, int> states; // Map of the possible state values
        int neighbor_type;      // 1 -> Von Neumann neighborhood; 2 -> Moore neighborhood
        int bound_type;         // 3 -> Static; 4 -> Periodic Boundary
        int dim1;               // Number of rows for CA
        int dim2;               // Number of columns for CA
        int message_radius;     // Message passing radius

        Cell boundary_cell;     // Place holder cell that act as the boundary


    public:
        CellularAutomata();
        ~CellularAutomata();
        // Dimension and initial setup for the cellular automaton
        int setup_dimension(int ndims, int dim1, int dim2);
        // Neighborhood type set up for the cellular automaton
        int setup_neighborhood(int neigh_type);
        // Boundary type setup for the cellular automaton
        int set_boundtype(int bound_type, int radius);
        
        // Set possible states
        int set_states(std::map<string, int> states);
        // Return list of possible states
        std::map<string, int> list_states() const;

        // Intializing Cells State_T0
        int init_CA_state(int stat_t0);
        int init_CA_stateWprob(int stat_t0, double probability);

        int init_Cell_state(int stat_t0, vector<vector<int> > coords);
        int init_Cell_stateWprob(int stat_t0, double probability,  vector<vector<int> > coords);
        
        // Retrieve all valid neighbor Cells given cell coordinate
        Neighborhood get_neighborhood(vector<int> coord);

        // Query the current cell states of the CA
        std::map<int, int> query_cellState();
        int record_cellState(string filepath);

        //Alternatively could combine the three functions below into one method for one loop
        // Records the current frame of the CA
        int record_CAframe(string filepath) const;
        // Records the current cell states of the CA
        //int record_CellState(string filepath) const;
        
        // Method to swap staes from tx to after recording for each new update
        int swapState();
        // Function that drive the timestep updates using a vector of rules
        int update(vector<Rule*>& rules);       
        // Print the CA to console for debugging
        void print() const;
};

#define VONNEUMANN  1
#define MOORE       2
#define STATIC      3
#define FIXED       4
#define PERIODIC    5
#define MAJORITY    6
#define PARITY      7


// Rule for majority rule that returns update value
class MajorityRule : public Rule {
public:
    int apply(Neighborhood &neighborhood) override {
        // Map for storing frequency of states
        std::map<int, int> frequencyMap;

        // Iterate through each cell in the neighborhood map
        for (const auto &cellEntry : neighborhood.subgrid) {
            const Cell &cell = cellEntry.first;
            frequencyMap[cell.getState_t0()]++;
            // cout<<"Increments frequency of state "<<cell.getState_t0()<<" while searching position ("<<cell.get_x()<<","<<cell.get_y()<<")"<<endl;
        }

        // Determine the state with the maximum frequency
        int maxFrequencyValue = 0;
        int maxFrequency = 0;
        for (const auto &entry : frequencyMap) {
            if (entry.second > maxFrequency) {
                maxFrequency = entry.second;
                maxFrequencyValue = entry.first;
            }
        }

        return maxFrequencyValue;
    }
};

// Rule for straight conditional transition
class StraightConditionalRule : public Rule {
    private:
        vector<int> transition_states; // ordered list of states

    public:
        // Constructor to include a transistion state list
        StraightConditionalRule(const vector<int>& transition_state_list) 
            : transition_states(transition_state_list) {}

        int apply(Neighborhood &neighborhood) override {
            const Cell& centerCell = neighborhood.center_cell; // Use the center cell
            int currentState = centerCell.getState_t0();

            // Iterate through the transition states to find the next state
            for (size_t i = 0; i < transition_states.size(); ++i) {
                if (transition_states[i] == currentState) {
                    // If current state is found, return the next state in the vector
                    return (i < transition_states.size() - 1) ? transition_states[i + 1] : transition_states[0];
                }
            }

            // Default behavior if state not found in transition_states
            return currentState; 
        }

        // Function to set the straight conditional transition list
        void changeTransitionStateList(const vector<int>& transition_state_list){
            this->transition_states = transition_state_list;
        }
};


// Rule for conditional transition based on a neighbor's state
class NeighborConditionalRule : public Rule {
    private:
        int trigger_state; // State of the cell that triggers the change
        int neighbor_target_state; // Target state of the neighbor to cause the change
        int new_state; // New state to transition to

    public:
        //+ Constructor to include a trigger state, neighbor_target_state, and new_state
        NeighborConditionalRule(int trigger_state, int neighbor_target_state, int new_state)
            : trigger_state(trigger_state), neighbor_target_state(neighbor_target_state), new_state(new_state) {}

        int apply(Neighborhood &neighborhood) override {
            const Cell& centerCell = neighborhood.center_cell;
            int currentState = centerCell.getState_t0();

            // Check if the center cell is in the trigger state
            if (currentState == trigger_state) {
                // Check the states of neighboring cells
                for (const auto& neighborEntry : neighborhood.subgrid) {
                    const Cell& neighborCell = neighborEntry.first;
                    int neighborState = neighborCell.getState_t0();

                    // If a neighbor is in the target state, change the state of the center cell
                    if (neighborState == neighbor_target_state) {
                        return new_state;
                    }
                }
            }

            // If no change is required, return the current state
            return currentState;
        }
};

// Rule for Activation-Inhibition conditional
class ActivationInhibitionRule : public Rule {
private:
    double activationThreshold;  // Threshold for a cell to become active
    double inhibitionThreshold;  // Threshold for a cell to become inactive
    int activeState;             // State that represents an active cell
    int inactiveState;           // State that represents an inactive cell
    int inhibitoryState;         // State that contributes to the inhibition of a cell
    std::map<int, double> distanceWeights; // Weights associated with neighbor distances

public:
    // Constructor: Initializes the thresholds, states, and distance weights.
    ActivationInhibitionRule(double activationThreshold, double inhibitionThreshold,
                             int activeState, int inactiveState, int inhibitoryState,
                             std::map<int, double> distanceWeights)
        : activationThreshold(activationThreshold), inhibitionThreshold(inhibitionThreshold),
          activeState(activeState), inactiveState(inactiveState), inhibitoryState(inhibitoryState),
          distanceWeights(distanceWeights) {}

    // Calculates the activation and inhibition effects on a cell based on the states of its neighbors.
    int apply(Neighborhood &neighborhood) override {
        double activeWeightedSum = 0;
        double inhibitoryWeightedSum = 0;

        // Iterate over the neighborhood, calculating weighted sums for activation and inhibition.
        for (const auto &neighbor : neighborhood.subgrid) {
            const Cell &cell = neighbor.first;
            int distance = neighbor.second;

            double weight = distanceWeights.count(distance) > 0 ? distanceWeights[distance] : 1.0; // Use default weight if not specified.

            // Increase weighted sums based on neighbor states and distance weights.
            if (cell.getState_t0() == activeState) {
                activeWeightedSum += weight;
            } else if (cell.getState_t0() == inhibitoryState) {
                inhibitoryWeightedSum += weight;
            }
        }

        // Determine the cell's next state based on the activation/inhibition thresholds.
        if (activeWeightedSum > activationThreshold && inhibitoryWeightedSum < inhibitionThreshold) {
            return activeState;  // Cell becomes active.
        } else if (inhibitoryWeightedSum > inhibitionThreshold) {
            return inactiveState;  // Cell becomes inactive.
        }

        // If neither condition is met, return the current state.
        return neighborhood.center_cell.getState_t0();
    }

    // setDistanceWeights: Updates the distanceWeights map to change influence dynamics.
    void setDistanceWeights(const std::map<int, double>& newWeights) {
        distanceWeights = newWeights;
    }
};



// Rule for parity transition
class ParityRule : public Rule {
private:
    int targetState; // The state to check for in neighbors
    int newStateEven; // New state if the count is even
    int newStateOdd; // New state if the count is odd

public:
    // Constructor
    ParityRule(int targetState, int newStateEven, int newStateOdd)
        : targetState(targetState), newStateEven(newStateEven), newStateOdd(newStateOdd) {}

    int apply(Neighborhood &neighborhood) override {
        // Count neighbors in the target state
        int count = 0;
        for (const auto &cellEntry : neighborhood.subgrid) {
            if (cellEntry.first.getState_t0() == targetState) {
                count++;
            }
        }

        // Calculate parity (0 for even, 1 for odd)
        int parity = count % 2;

        // Return the new state based on the parity
        return parity == 0 ? newStateEven : newStateOdd;
    }

    // Setters and getters
    void setTargetState(int state) {
        this->targetState = state;
    }

    int getTargetState() const {
        return this->targetState;
    }
};