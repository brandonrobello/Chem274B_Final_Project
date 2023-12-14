// This file is the source file for Cellular Automata
#include <fstream>
#include "myCA_edit.h"

// Consturctor and Destructor for the cellular automata
CellularAutomata::CellularAutomata(){}
CellularAutomata::~CellularAutomata(){}

// Dimension and initial setup for the cellular automaton, reserves space for the cellular automaton vectors
int CellularAutomata::setup_dimension(int ndims, int dim1, int dim2)
{
    if ((ndims != 1 && ndims != 2) || dim1 <= 0 || (ndims == 2 && dim2 <= 0)) {
        cout<<"Invalid dimensions !"<<endl;
        return -1; // Return error code for invalid dimensions
    }

    // Resize the grid based on the dimensions
    grid.resize(dim1);
    for (int i = 0; i < dim1; ++i) {
        if (ndims == 1) {
            grid[i].resize(1); // Single column in 1D
            // CA.grid[i][0].resize(n_feats); // Resize each cell according to feature dimension
        } 
        else { // ndims == 2
            grid[i].resize(dim2);
            //for (int j = 0; j < dim2; ++j) {
                // CA.grid[i][j].resize(n_feats);
            //}
        }
    }
    // Successful setup
    this->dim1 = dim1;
    this->dim2 = dim2;

    cout<<"Successfully setup CA with size ("<<dim1<<","<<dim2<<")"<< endl;
    return 0;
}

// Neighborhood type set up for the cellular automaton
int CellularAutomata::setup_neighborhood(int neighbor_type)
{
     // Von Neumann neighborhood type
    if (neighbor_type == VONNEUMANN) {
        cout<<"Successfully setup CA with Von Neumann neighborhood type"<<endl;
        this->neighbor_type = neighbor_type;
        return 0;
    }
    // Moore neighborhood type
    else if (neighbor_type == MOORE) {
        cout<<"Successfully setup CA with Moore neighborhood type"<<endl;
        this->neighbor_type = neighbor_type;
        return 0;
    }
    // Invalid neighborhood type
    else {
        cout<<"Invalid neighbor type!"<<endl;
        return -1;
    }
}

// Boundary type setup for the cellular automaton
int CellularAutomata::set_boundtype(int bound_type, int radius)
{
    if (radius <= 0) {
        cout<<"Message passing radius has to be a positive value!"<<endl;
        return -1;
    }
    this->message_radius = radius;
    cout<<"Successfully setup CA with message passing radius of "<< radius <<endl;
     // Static boundary type
    if (bound_type == STATIC) {
        cout<<"Successfully setup CA with static boundaries"<<endl;
        this->bound_type = bound_type;
        return 0;
    }
    // Periodic boundary type
    else if (bound_type == PERIODIC) {
        cout<<"Successfully setup CA with periodic boundaries"<<endl;
        this->bound_type = bound_type;
        return 0;
    }
    // Invalid neighborhood type
    else {
        cout<<"Invalid boundary type!"<<endl;
        return -1;
    }
}

// Set possible discrete states of grid's Cells
int CellularAutomata::set_states(std::map<string, int> states)
{
    // sanity check / already existing states?

    this->states = states;
    return 0;
}

// Return list of possible states
std::map<string, int> CellularAutomata::list_states() const
{

    // sanity check / already existing states?

    return this->states;
}

// Cell features setup for the cellular automaton
int CellularAutomata::set_CA_features(string feature, double feat_val) 
{
       // sanity check / already existing states?

    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            grid[i][j].setFeature(feature, feat_val);
        }
    }
    cout << "Successfully set feature " << feature << " with value " << feat_val << " for all cells." << endl;
    return 0;
}

// Cell features setup with probability for the cellular automaton
int CellularAutomata::set_CA_featuresWprob(string feature, double feat_val, double probability) 
{
    // Default value?

        // sanity check / already existing states?


    srand(time(NULL)); // Seed for random number generation

    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            double randomValue = (double)rand() / RAND_MAX;
            if (randomValue <= probability) {
                grid[i][j].setFeature(feature, feat_val);
            }
        }
    }
    cout << "Successfully set feature " << feature << " with value " << feat_val << " based on probability " << probability << "." << endl;
    return 0;
}

// Intializing Cells State_T0
int CellularAutomata::init_CA_state(int stat_t0) 
{
       // sanity check / already existing states?
       // Default value

    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            grid[i][j].setState_t0(stat_t0);
            grid[i][j].set_x(i);
            grid[i][j].set_y(j);
        }
    }
    cout << "Initialized all cells to state " << stat_t0 << "." << endl;
    return 0;
}

// Intializing Cells State_T0 with probability
int CellularAutomata::init_CA_stateWprob(int stat_t0, double probability) 
{
   // sanity check / already existing states?
       // Default value

    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    for (int i = 0; i < dim1; ++i) {
        for (int j = 0; j < dim2; ++j) {
            double randomValue = static_cast<double>(rand()) / RAND_MAX;
            if (randomValue <= probability) {
                grid[i][j].setState_t0(stat_t0);
            }
        }
    }
    cout << "Initialized cell states to " << stat_t0 << " based on probability " << probability << "." << endl;
    return 0;
}
// Intializing specific Cells State_T0
int CellularAutomata::init_Cell_state(int stat_t0, vector<vector<int>> coords) {
    for (const auto& coord : coords) {
        int x = coord[0];
        int y = coord[1];

        // Boundary check for the coordinates
        if (x < 0 || x >= dim1 || y < 0 || y >= dim2) {
            cout << "Invalid out-of-bounds coordinate: (" << x << ", " << y << ")" << endl;
            return -1;
        }

        grid[x][y].setState_t0(stat_t0);
    }
    cout << "Initialized specified cells to state " << stat_t0 << "." << endl;
    return 0;
}

// Intializing specific Cells State_T0 with probability 
int CellularAutomata::init_Cell_stateWprob(int stat_t0, double probability, vector<vector<int>> coords) {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    for (const auto& coord : coords) {
        int x = coord[0];
        int y = coord[1];

        // Boundary check for the coordinates
        if (x < 0 || x >= dim1 || y < 0 || y >= dim2) {
            cout << "Invalid out-of-bounds coordinate: (" << x << ", " << y << ")" << endl;
            return -1;
        }

        double randomValue = static_cast<double>(rand()) / RAND_MAX;
        if (randomValue <= probability) {
            grid[x][y].setState_t0(stat_t0);
        }
    }
    cout << "Initialized specified cells to state " << stat_t0 << " based on probability " << probability << "." << endl;
    return 0;
}

// Get neighborhood function
Neighborhood CellularAutomata::get_neighborhood(vector<int> coord)
{
    // Boudnary check already performed in update functions
    int x = coord[0];
    int y = coord[1];


    int radius = this->message_radius;
    map<Cell, int> subgrid;
    int count;

    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            // Skip center cell
            // Skip corner neighbors for Von Neumann neighborhood type
            int current_radius = abs(dx) + abs(dy);
            if ((dx == 0 && dy == 0) || (this->neighbor_type == VONNEUMANN && current_radius > radius)) {
                continue;
            }
            // Get neighbor coordinate
            int nx = x + dx;
            int ny = y + dy;

            // Adjust for periodic boundaries
            if (this->bound_type == PERIODIC) {
                nx = (nx + this->dim1) % this->dim1;
                ny = (ny + this->dim2) % this->dim2;
            }

            // Index out of bounds situation for fixed neighborhood type
            if ((nx < 0 || nx >= this->dim1 || ny < 0 || ny >= this->dim2) && this->neighbor_type == FIXED) {
                subgrid[this->grid[nx][ny]] = current_radius;
                count++;
            }
            // Add valid coordinate to result vector
            if (nx >= 0 && nx < this->dim1 && ny >= 0 && ny < this->dim2) {
                subgrid[this->grid[nx][ny]] = current_radius;
                // cout<<"The neighbor at position (" << nx << ","<<ny<<")"<<endl;
                count++;
            }
        }
    }
    // Initialize neighborhood
    Neighborhood neighbor;
    neighbor.subgrid = subgrid;
    neighbor.dim = count;

    return neighbor;
}

// Query the current cell states of the CA
// int query_cellState(string filepath);

// Records the current frame of the CA
int CellularAutomata::record_CAframe(string filepath) const{
    ofstream outfile(filepath, ios::app); // Opens file in append mode

    if (!outfile.is_open()) {
        perror(("Error opening file " + filepath).c_str());
        return -1;
    }

    if (outfile.tellp() == 0) {
        outfile << dim1 << "\t" << dim2 << endl; // Write dimensions if file is empty
    }

    for (int x = 0; x < dim1; x++) {
        for (int y = 0; y < dim2; y++) {
            outfile << grid[x][y].getState_t0() << "\t";
        }
    }
    outfile << endl; // New line for next frame
    outfile.close();
    return 0;
}

void CellularAutomata::print() const{
    for (int x = 0; x < dim1; x++) {
        for (int y = 0; y < dim2; y++) {
            cout<< grid[x][y].getState_t0() << "\t";
        }
        cout  << endl; // New line for next row
    }
}

// Records the current cell states of the CA
/*
int CellularAutomata::record_CellState(string filepath) const{
    ofstream outfile(filepath, ios::app);

    if (!outfile.is_open()) {
        perror(("Error opening file " + filepath).c_str());
        return -1;
    }

    if (outfile.tellp() == 0) {
        outfile << dim1 << "\t" << dim2 << endl;
    }

    for (int x = 0; x < dim1; x++) {
        for (int y = 0; y < dim2; y++) {
            outfile << grid[x][y].getState_t0() << "\t";
        }
    }
    outfile << endl;
    outfile.close();
    outfile << endl; // New line for next frame

    return 0;
}
*/

// Method to swap staes from tx to after recording for each new update
int CellularAutomata::swapState() {
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
            // Swap state_tx and state_t0 for each cell
            grid[i][j].cell_update();
        }
    }
    return 0; // Return 0 to indicate successful execution
}

// Function that drive the timestep updates use rule function
int CellularAutomata::update(Rule& rule) {
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
            Neighborhood neighborhood = get_neighborhood({i, j});
            int newState = rule.apply(neighborhood, states);
            // cout<<"The state of cell ("<<i<<","<<j<<") was updated from "<<grid[i][j].getState_t0()<<" to "<<newState<<endl;
            grid[i][j].setState_tx(newState);
        }
    }
    return 0;
}




/*
// Message passing update function for the majority rule
int majority_rule(CellularAutomata &CA, vector<int> coord)
{
    // Grab the passed in coordiante and perform sanity check
    int x = coord[0];
    int y = coord[1];

    if (x >= CA.dim1 || x < 0 || y >= CA.dim2 || y < 0) {
        cout<<"Invalid coordinate or feature index!"<<endl;
        return -1;
    }
    // Get the neighbors of coordinate
    vector<vector<int> > neighbors = get_neighborhood(CA, coord);

    // Map for storing frequency
    map<int, int> frequencyMap;
    for (const auto &neighbor_coord : neighbors) {
        int neighbor_x = neighbor_coord[0];
        int neighbor_y = neighbor_coord[1];
        frequencyMap[CA.grid[neighbor_x][neighbor_y].state_t0]++;
    }
    // Get the value with the maximum frequency
    int maxFrequencyValue = 0;
    int maxFrequency = 0;
    for (const auto &entry : frequencyMap) {
        if (entry.second > maxFrequency) {
            maxFrequency = entry.second;
            maxFrequencyValue = entry.first;
        }
    }
    // Return cell value the highest frequency value
    return maxFrequencyValue;
}


// Retrieve all valid neighbor coordinates given a cell coordinate
// vector<vector<int> > get_neighborhood(CellularAutomata &CA, vector<int> coord)
// {
//     // Boudnary check already performed in update functions
//     int x = coord[0];
//     int y = coord[1];

//     int radius = CA.message_radius;
//     vector<vector<int> > res; // Result vector for storing all valid neighbor coordinates

//     for (int dx = -radius; dx <= radius; ++dx) {
//         for (int dy = -radius; dy <= radius; ++dy) {
//             // Skip center cell
//             // Skip corner neighbors for Von Neumann neighborhood type
//             if ((dx == 0 && dy == 0) || (CA.neighbor_type == VONNEUMANN && abs(dx) + abs(dy) > radius)) {
//                 continue;
//             }
//             // Get neighbor coordinate
//             int nx = x + dx;
//             int ny = y + dy;

//             // Adjust for periodic boundaries
//             if (CA.bound_type == PERIODIC) {
//                 nx = (nx + CA.dim1) % CA.dim1;
//                 ny = (ny + CA.dim2) % CA.dim2;
//             }

//             // Add valid coordinate to result vector
//             if (nx >= 0 && nx < CA.dim1 && ny >= 0 && ny < CA.dim2) {
//                 res.push_back({nx, ny});
//             }
//         }
//     }
//     return res;
// }

// Probability x of cell entering state x when initialized
int CA_init_state(CellularAutomata &CA, double prob, int val)
{
    
    srand(static_cast<unsigned int>(time(0)));
    
    // Walk over grid 
    for (int x = 0; x < CA.dim1; x++)
    for (int y = 0; y < CA.dim2; y++) 
    {
        // Generate a random number between 0 and 1
        double randomValue = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    
        // Set the value based on probability
        if (randomValue <= prob) {CA.grid[x][y].state_t0 = val;}
        // Set a default state for when randomValue > prob
        else { CA.grid[x][y].state_t0 = 0;}
    }
    return 0;
}

// Cell features setup for the cellular automaton
// feature: indicates the feature index to update the value with
// val: value that will be used to update the cells
int CA_setup_cell_features(CellularAutomata &CA, vector<vector<int> > coords, string feature, int val)
{
    // Ssanity check for feature index value
    //if (nth_feature >= CA.n_feats || nth_feature < 0) {
    //    cout<<"Invalid feature index!"<<endl;
    //    return -1;
    //}
    for (const vector<int> &coord : coords) {
        int x = coord[0];
        int y = coord[1];
        // Boundary check for the coordinates
        if (x >= CA.dim1 || x < 0 || y >= CA.dim2 || y < 0) {
            cout<<"Invalid coordinate out of bounds!"<<endl;
            return -1;
        }
        //CA.grid[x][y][nth_feature] = val; // Update cell's nth feature with new value
        CA.grid[x][y].features[feature] = val;
    }
    cout<<"Successfully setup cell states's feature "<< feature << " with value " << val <<endl;
    return 0;
}



// Probability x of cell entering state x when initialized
int CA_init_cond(CellularAutomata &CA, vector<int> coord, string feature, double prob, int val)
{
    // Ssanity check for feature index value
    // if (nth_feature >= CA.n_feats || nth_feature < 0) {
    //    cout<<"Invalid feature index!"<<endl;
    //    return -1;
    //}
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
        CA.grid[x][y].features[feature] = val;
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
*/