#include <vector>

using namespace std;

class CelluarAutomata
{
    public:
        vector<vector<vector<double>>> grid;    // 3D grid structure that stores double data type
        int neighbor_type;                      // 1 -> Von Neumann neighborhood; 2 -> Moore neighborhood
        int bound_type;                         // 3 -> Static; 4 -> Periodic Boundary
        int dim1;
        int dim2;
        int n_feats;

        CelluarAutomata(int n, int m, int periodic_boundary, int neighbor_type);
        ~CelluarAutomata();

};
#define VONNEUMANN  1
#define MOORE       2
#define STATIC      3
#define PERIODIC    4

// Dimension and initial setup for the cellular automaton
int CA_setup_dimension(CelluarAutomata &CA, int ndims, int dim1, int dim2);

// Neighborhood type set up for the cellular automaton
int CA_setup_neighborhood(CelluarAutomata &CA,int neigh_type);

// Boundary type setup for the cellular automaton
int CA_setup_boundtype(CelluarAutomata &CA,int bound_type, int radius);

// Cell states setup for the cellular automaton
int CA_setup_cell_states(CelluarAutomata CA, int nstates);

// Probability x of cell entering state x when initialized
int CA_init_cond(CelluarAutomata CA,int x_state, double prob);

// Rewrite probability x of cell entering state x when initialized
int CA_init_cond_rewrite(CelluarAutomata CA,int x_state, double probability);

// Set up rule for the cells
void CA_setup_rule(CelluarAutomata CA,int rule_type);

// Set up rule for the cells with probability
void CA_setup_rule_wprob(CelluarAutomata CA,int rule_type, double probability);