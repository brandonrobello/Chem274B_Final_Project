#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

class Cell {
public:
    int x; // The x position on the grid
    int y; // The x position on the grid
    int state_t0; // Intitial state of the cell
    int state_tx; // Updated state of the cell
    std::map<string, int> features; // Map to track what each feature and value


    Cell(){}
    ~Cell(){}
};

class CellularAutomata
{
    public:
        vector<vector<Cell> > grid;    // 3D grid structure that stores double data type
        std::map<string, int> states; // Map of the possible state values
        int neighbor_type;      // 1 -> Von Neumann neighborhood; 2 -> Moore neighborhood
        int bound_type;         // 3 -> Static; 4 -> Periodic Boundary
        int dim1;               // Number of rows for CA
        int dim2;               // Number of columns for CA
        int n_feats;            // Number of features for each cell
        int message_radius;     // Message passing radius
        int rule_type;          // Rule type of the cellular automata

        CellularAutomata();
        ~CellularAutomata();

};

#define VONNEUMANN  1
#define MOORE       2
#define STATIC      3
#define PERIODIC    4
#define MAJORITY    5
#define PARITY      6

// Dimension and initial setup for the cellular automaton
int CA_setup_dimension(CellularAutomata &CA, int ndims, int dim1, int dim2, int n_feats);

// Neighborhood type set up for the cellular automaton
int CA_setup_neighborhood(CellularAutomata &CA,int neigh_type);

// Boundary type setup for the cellular automaton
int CA_setup_boundtype(CellularAutomata &CA,int bound_type, int radius);

// Cell features setup for the cellular automaton
int CA_setup_cell_features(CellularAutomata &CA, vector<vector<int> > coords, string feature, int val);

// Probability x of cell entering state x when initialized
int CA_init_cond(CellularAutomata &CA, vector<int> coord, string feature, double prob, int val);

// Set up rule for the cells
int CA_setup_rule(CellularAutomata &CA,int rule_type);

// Set up rule for the cells with probability
int CA_setup_rule_wprob(CellularAutomata &CA,int rule_type, double prob);

// Retrieve all valid neighbor coordinates given a cell coordinate
vector<vector<int> > get_neighborhood(CellularAutomata &CA, vector<int> coord);

// Message passing update function for the majority rule
int majority_rule(CellularAutomata &CA, vector<int> coord);

// Probability x of cell entering state x when initialized
int CA_init_state(CellularAutomata &CA, double prob, int val);

// CA_Tracker = records the last frame of the CA and swaps state
int CA_record_swapState(CellularAutomata& CA, string filepath);

// The CA Engine that drive the timestep updates
int CA_Engine(CellularAutomata &CA, int n_steps, string outfile_path);