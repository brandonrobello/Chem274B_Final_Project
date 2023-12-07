#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

class CellularAutomata
{
    public:
        vector<vector<vector<int>>> grid;    // 3D grid structure that stores double data type
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

// Cell states setup for the cellular automaton
int CA_setup_cell_states(CellularAutomata &CA, vector<vector<int>> coords, int nth_feature, int val);

// Probability x of cell entering state x when initialized
int CA_init_cond(CellularAutomata &CA, vector<int> coord, int nth_feature, double prob, int val);

// Set up rule for the cells
int CA_setup_rule(CellularAutomata &CA,int rule_type);

// Set up rule for the cells with probability
int CA_setup_rule_wprob(CellularAutomata &CA,int rule_type, double prob);

// Retrieve all valid neighbor coordinates given a cell coordinate
vector<vector<int>> get_neighborhood(CellularAutomata &CA, vector<int> coord);

// Message passing update function for the majority rule
int majority_rule_update(CellularAutomata &CA, vector<int> coord, int nth_feature);
