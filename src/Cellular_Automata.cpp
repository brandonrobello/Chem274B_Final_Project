// This file is the source file for Cellular Automata
#include <iostream>

#include "mygrids.h"

// Dimension and initial setup for the cellular automaton, reserves space for the cellular automaton vectors
int CA_setup_dimension(CelluarAutomata &CA, int ndims, int dim1, int dim2, int n_feats)
{
    if ((ndims != 1 && ndims != 2) || dim1 <= 0 || (ndims == 2 && dim2 <= 0) || n_feats <= 0) {
        cout<<"Invalid dimensions !"<<endl;
        return -1; // Return error code for invalid dimensions
    }

    // Resize the grid based on the dimensions
    CA.grid.resize(dim1);
    for (int i = 0; i < dim1; ++i) {
        if (ndims == 1) {
            CA.grid[i].resize(1); // Single column in 1D
            CA.grid[i][0].resize(n_feats); // Resize each cell according to feature dimension
        } 
        else { // ndims == 2
            CA.grid[i].resize(dim2);
            for (int j = 0; j < dim2; ++j) {
                CA.grid[i][j].resize(n_feats);
            }
        }
    }
    // Successful setup
    CA.dim1 = dim1;
    CA.dim2 = dim2;
    CA.n_feats = n_feats;

    cout<<"Successfully setup grid with size ("<<dim1<<","<<dim2<<") with "<<n_feats<<" features for each cell"<<endl;
    return 0;
}

// Neighborhood type set up for the cellular automaton
int CA_setup_neighborhood(CelluarAutomata &CA,int neighbor_type)
{
     // Von Neumann neighborhood type
    if (neighbor_type == VONNEUMANN) {
        cout<<"Successfully setup grid with Von Neumann neighborhood type"<<endl;
        CA.neighbor_type = neighbor_type;
        return 0;
    }
    // Moore neighborhood type
    else if (neighbor_type == MOORE) {
        cout<<"Successfully setup grid with Moore neighborhood type"<<endl;
        CA.neighbor_type = neighbor_type;
        return 0;
    }
    // Invalid neighborhood type
    else {
        cout<<"Invalid neighbor type!"<<endl;
        return -1;
    }
}

// Boundary type setup for the cellular automaton
int CA_setup_boundtype(CelluarAutomata &CA,int bound_type, int radius)
{
     // Static boundary type
    if (bound_type == STATIC) {
        cout<<"Successfully setup grid with static boundaries"<<endl;
        CA.bound_type = bound_type;
        return 0;
    }
    // Periodic boundary type
    else if (bound_type == PERIODIC) {
        cout<<"Successfully setup grid with periodic boundaries"<<endl;
        CA.bound_type = bound_type;
        return 0;
    }
    // Invalid neighborhood type
    else {
        cout<<"Invalid boundary type!"<<endl;
        return -1;
    }
}
// Cell states setup for the cellular automaton
// nth_feature: indicates the feature index to update the value with
// val: value that will be used to update the cells
int CA_setup_cell_states(CelluarAutomata &CA, vector<vector<int>> coords, int nth_feature, int val)
{
    if (nth_feature >= CA.n_feats) {
        cout<<"Invalid feature index!"<<endl;
        return -1;
    }
    for (int i = 0; i < CA.dim1; ++i) {
        for (int j = 0; j < CA.dim2; ++j) {
            CA.grid[i][j][nth_feature] = val;
        }
    }
    return;
}

// Probability x of cell entering state x when initialized
int CA_init_cond(CelluarAutomata CA,int x_state, double prob);

// Rewrite probability x of cell entering state x when initialized
int CA_init_cond_rewrite(CelluarAutomata CA,int x_state, double probability);

// Set up rule for the cells
void CA_setup_rule(CelluarAutomata CA,int rule_type);

// Set up rule for the cells with probability
void CA_setup_rule_wprob(CelluarAutomata CA,int rule_type, double probability);