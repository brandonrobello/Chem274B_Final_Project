// This file is the source file for Cellular Automata
#include "myCA.h"

// Consturctor and Destructor for the cellular automata
CellularAutomata::CellularAutomata(){}
CellularAutomata::~CellularAutomata(){}

// Dimension and initial setup for the cellular automaton, reserves space for the cellular automaton vectors
int CA_setup_dimension(CellularAutomata &CA, int ndims, int dim1, int dim2, int n_feats)
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

    cout<<"Successfully setup CA with size ("<<dim1<<","<<dim2<<") with "<<n_feats<<" features for each cell"<<endl;
    return 0;
}

// Neighborhood type set up for the cellular automaton
int CA_setup_neighborhood(CellularAutomata &CA,int neighbor_type)
{
     // Von Neumann neighborhood type
    if (neighbor_type == VONNEUMANN) {
        cout<<"Successfully setup CA with Von Neumann neighborhood type"<<endl;
        CA.neighbor_type = neighbor_type;
        return 0;
    }
    // Moore neighborhood type
    else if (neighbor_type == MOORE) {
        cout<<"Successfully setup CA with Moore neighborhood type"<<endl;
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
int CA_setup_boundtype(CellularAutomata &CA,int bound_type, int radius)
{
    if (radius <= 0) {
        cout<<"Message passing radius has to be a positive value!"<<endl;
        return -1;
    }
    CA.message_radius = radius;
    cout<<"Successfully setup CA with message passing radius of "<< radius <<endl;
     // Static boundary type
    if (bound_type == STATIC) {
        cout<<"Successfully setup CA with static boundaries"<<endl;
        CA.bound_type = bound_type;
        return 0;
    }
    // Periodic boundary type
    else if (bound_type == PERIODIC) {
        cout<<"Successfully setup CA with periodic boundaries"<<endl;
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
int CA_setup_cell_states(CellularAutomata &CA, vector<vector<int>> coords, int nth_feature, int val)
{
    // Ssanity check for feature index value
    if (nth_feature >= CA.n_feats || nth_feature < 0) {
        cout<<"Invalid feature index!"<<endl;
        return -1;
    }
    for (const vector<int> &coord : coords) {
        int x = coord[0];
        int y = coord[1];
        // Boundary check for the coordinates
        if (x >= CA.dim1 || x < 0 || y >= CA.dim2 || y < 0) {
            cout<<"Invalid coordinate out of bounds!"<<endl;
            return -1;
        }
        CA.grid[x][y][nth_feature] = val; // Update cell's nth feature with new value
    }
    cout<<"Successfully setup cell states's feature "<< nth_feature << " with value " << val <<endl;
    return 0;
}

// Probability x of cell entering state x when initialized
int CA_init_cond(CellularAutomata &CA, vector<int> coord, int nth_feature, double prob, int val)
{
    // Ssanity check for feature index value
    if (nth_feature >= CA.n_feats || nth_feature < 0) {
        cout<<"Invalid feature index!"<<endl;
        return -1;
    }
    int x = coord[0];
    int y = coord[1];
    // Boundary check for the coordinates
    if (x >= CA.dim1 || x < 0 || y >= CA.dim2 || y < 0) {
        cout<<"Invalid out of bounds coordinate!"<<endl;
        return -1;
    }
    
    srand(static_cast<unsigned int>(time(0)));
    // Generate a random number between 0 and 1
    double randomValue = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

    // Set the value based on probability
    if (randomValue <= prob) {
        CA.grid[x][y][nth_feature] = val;
    }
    return 0;
}

// Set up rule for the cells
int CA_setup_rule(CellularAutomata &CA, int rule_type)
{
    // Invalid rule type
    if (rule_type != MAJORITY && rule_type != PARITY) {
        cout<<"Invalid rule type!"<<endl;
        return -1;
    }
    CA.rule_type = rule_type;
    return 0;
}

// Set up rule for the cells with probability
int CA_setup_rule_wprob(CellularAutomata &CA, int rule_type, double prob)
{
    // Invalid rule type
    if (rule_type != MAJORITY && rule_type != PARITY) {
        cout<<"Invalid rule type!"<<endl;
        return -1;
    }
    srand(static_cast<unsigned int>(time(0)));
    // Generate a random number between 0 and 1
    double randomValue = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    if (randomValue <= prob) {
        CA.rule_type = rule_type;
    }
    return 0;
}

// Message passing update function for the majority rule
int majority_rule_update(CellularAutomata &CA, vector<int> coord, int nth_feature)
{
    // Grab the passed in coordiante and perform sanity check
    int x = coord[0];
    int y = coord[1];

    if (x >= CA.dim1 || x < 0 || y >= CA.dim2 || y < 0 || nth_feature < 0) {
        cout<<"Invalid coordinate or feature index!"<<endl;
        return -1;
    }

    int radius = CA.message_radius;
    // Map for storing frequency
    map<int, int> frequencyMap;

    for (int d = 1; d <= radius; ++d) {
        // Get the coordinate values for the 4 directions
        int left = x - d;
        int right = x + d;
        int top = y - d;
        int bottom = y + d;

        if (CA.bound_type == PERIODIC) {
            // Modify the 4 values for periodic boundary type
            left = (left + CA.dim1) % CA.dim1;
            right = (right + CA.dim1) % CA.dim1;
            top = (top + CA.dim2) % CA.dim2;
            bottom = (bottom + CA.dim2) % CA.dim2;
        }
        // Create a vector storing to be added coordinates
        vector<vector<int>> to_be_added;
        if (CA.neighbor_type == VONNEUMANN) {
            // Only add north, south, west, east for Von Neumann neighbor rule
            to_be_added = {{left, y}, {right, y}, {x, top}, {x, bottom}};
        }
        else {
            // Add all adjacent cells for Moore neighbor rule
            to_be_added = {{left, y}, {right, y}, {x, top}, {x, bottom}, {left, top}, 
                            {left, bottom}, {right, top}, {right, bottom}};
        }
        // Loop through all the coordinates in the to_be_added vector, and record the frequency
        for (const auto &coord : to_be_added) {
            
            int x_coord = coord[0];
            int y_coord = coord[1];
            
            if (x_coord >= CA.dim1 || x_coord < 0 || y_coord >= CA.dim2 || y_coord < 0) {
                continue; // Continue if coordinate is out of bounds
            }
            // Add one count to that specific value
            frequencyMap[CA.grid[x_coord][y_coord][nth_feature]]++;
        }
    }

    int maxFrequencyValue = 0;
    int maxFrequency = 0;
    for (const auto &entry : frequencyMap) {
        if (entry.second > maxFrequency) {
            maxFrequency = entry.second;
            maxFrequencyValue = entry.first;
        }
    }
    // Update cell value the highest frequency value
    CA.grid[x][y][nth_feature] = maxFrequencyValue;
}