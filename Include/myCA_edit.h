#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

class Cell {
    private:
        int x; // The x position on the grid / position from center in the neighborhood (important for the Activation-Inhibition rule)
        int y; // The x position on the grid / position from center in the neighborhood (important for the Activation-Inhibition rule)
        int state_t0; // Intitial state of the cell 
        int state_tx; // Updated state of the cell
        std::map<string, double> features; // Map to track what each feature and value
    public:
        Cell(){}
        //add copy constructor for neighborhood
        ~Cell(){}
        //Curtis 
        int setFeature(string feature, double value){} // Method to add/change feature of the cell
        double getFeature(string feature){} // Method to get feature value
        int getState_t0(){} // Method to get current state
        int setState_t0(int state){} // Methof to set current state
        int getState_tx(){} // Method to get new state
        int setState_tx(int state){} // Methof to set new state
        vector<int> getPosition(){} // Method to get x and y positions
        int cell_update(){} // Method to swap state_tx and state_to, to make the new value (tx) the current value (t0)

};

class Rule {
public:
    virtual int apply(Neighborhood &neighborhood, const std::map<string, int>& states_list) = 0;
    virtual ~Rule() {}
};

//Curtis
struct Neighborhood
{   
    public:
    vector<vector<Cell> > subgrid;    // 3D grid structure that stores cell data type
    int dim1;               // Number of rows for subgrid
    int dim2;               // Number of columns for subgrid
    Neighborhood(); //implement construction with the copied features, x and y in reference to the center coord
    ~Neighborhood();
};

class CellularAutomata
{
    private:
        vector<vector<Cell> > grid;    // 3D grid structure that stores cell data type
        std::map<string, int> states; // Map of the possible state values
        vector<string> features; // List of all cell features add for reference and return to user
        int neighbor_type;      // 1 -> Von Neumann neighborhood; 2 -> Moore neighborhood
        int bound_type;         // 3 -> Static; 4 -> Periodic Boundary
        int dim1;               // Number of rows for CA
        int dim2;               // Number of columns for CA
        int message_radius;     // Message passing radius
    public:
        CellularAutomata();
        ~CellularAutomata();
        //add copy constructor
        // Dimension and initial setup for the cellular automaton
        int setup_dimension(int ndims, int dim1, int dim2);
        // Neighborhood type set up for the cellular automaton
        int setup_neighborhood(int neigh_type);
        // Boundary type setup for the cellular automaton
        int set_boundtype(int bound_type, int radius);
        
        //Brandon 
        // Set possible states
        int set_states(std::map<string, int> states);
        // Return list of possible states
        std::map<string, int> list_states();

        // Could use overloading or defualt variables for less individual methods below:
        // Cell features setup for the cellular automaton
        int set_CA_features(string feature, double feat_val); // For setup a global feature in the CA, all Cells have this feature and value
        int set_CA_featuresWprob(string feature, double feat_val, double probability); // For setup a global feature in the CA using a probability, all Cells have this feature and value if prob is true
        
        // Optional (Brandon)
        int set_CA_featuresWconditionT(string feature, double feat_val, string feat_cond, double val_condition); // For setup a global feature in the CA if feature condiditon is true, all Cells have this feature and value if prob is true
        int set_CA_featuresWconditionF(string feature, double feat_val, string feat_cond, double val_condition); // For setup a global feature in the CA if feature condiditon is false, all Cells have this feature and value if prob is true
        int set_Cell_features(string feature, double feat_val, vector<vector<int> > coords); // For setup a feature in the CA for Coords set, all Cells have this feature and value
        int set_Cell_featuresWprob(string feature, double feat_val, double probability, vector<vector<int> > coords); // For setup a feature in the CA using a probability for Coords set, all Cells have this feature and value if prob is true
        int set_Cell_featuresWconditionT(string feature, double feat_val, string feat_cond, double val_condition, vector<vector<int> > coords); // For setup a feature in the CA if feature condiditon is true for Coords set, all Cells have this feature and value if prob is true
        int set_Cell_featuresWconditionF(string feature, double feat_val, string feat_cond, double val_condition, vector<vector<int> > coords); // For setup a feature in the CA if feature condiditon is false for Coords set, all Cells have this feature and value if prob is true
        
        // Intializing Cells State_T0
        int init_CA_state(int stat_t0);
        int init_CA_stateWprob(int stat_t0, double probability);

        // Optional (Brandon) 
        int init_Cell_state(int stat_t0);
        int init_Cell_stateWprob(int stat_t0, double probability,  vector<vector<int> > coords);
        
        
        // Not implemented yet Curtis
        // Retrieve all valid neighbor Cells given cell coordinate
        Neighborhood get_neighborhood(vector<int> coord);

        // Radhika
        // Query the current cell states of the CA
        int query_cellState(string filepath);

        //Brandon
        //Alternatively could combine the three functions below into one method for one loop
        // Records the current frame of the CA
        int record_CAframe(string filepath);
        // Records the current cell states of the CA
        int record_cellState(string filepath);
        
        // Method to swap staes from tx to after recording for each new update
        int swapState();
        // Function that drive the timestep updates use rule function
        int update(Rule& rule)
        {
            for (int i = 0; i < dim1; i++) 
            {
                for (int j = 0; j < dim2; j++) 
                {
                    Neighborhood neighborhood = get_neighborhood({i, j});
                    int newState = rule.apply(neighborhood, states); // Apply the passed-in rule function here
                    grid[i][j].setState_tx(newState); // Directly update the state_tx of the cell
                }
            }
            return 0; // Return success or error code
        }
};

#define VONNEUMANN  1
#define MOORE       2
#define STATIC      3
#define PERIODIC    4
#define MAJORITY    5
#define PARITY      6


// Rule for majority rule that returns update value
class MajorityRule : public Rule {
public:
    int apply(Neighborhood &neighborhood, const std::map<string, int>& states_list) override {
        // Implement majority rule logic
    }
};

// Rule for straight conditional
class StraightConditionalRule : public Rule {
public:
    int apply(Neighborhood &neighborhood, const std::map<string, int>& states_list) override {
        // Implement straight conditional rule logic
    }
};

// Rule for Activation-Inhibition conditional
class ActivationInhibitionRule : public Rule {
private:
    std::map<string, int> long_short_weights;

public:
    ActivationInhibitionRule(const std::map<string, int>& weights) : long_short_weights(weights) {}

    int apply(Neighborhood &neighborhood, const std::map<string, int>& states_list) override {
        // Implement activation-inhibition rule logic
        // You can use long_short_weights here
    }
};

// Rule for conditional transition rule
class ConditionalTransitionRule : public Rule {};

// Rule for parity rule
class ParityRule : public Rule {};