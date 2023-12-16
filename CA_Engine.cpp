#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
using namespace std;
#include "myCA.h"




// CA_Tracker = records the last frame of the CA and swaps state
int CA_record_swapState(CellularAutomata& CA, string filepath)
{
    fstream outfile;

    // Opens a file stream for writing, using the provided file path
    outfile.open(filepath,ios::app);

    // Check if the file stream was opened successfully
    if (!outfile.is_open())
    { 
        perror(("Error opening file " + filepath).c_str());
        return -1; // Return -1 to indicate failure in opening the file
    }

    
    // Check if file is empty (file pointer at position 0 means empty file)
    if (outfile.tellp() == 0)
    {
        // Write the dimensions of the Cellular Automata grid to the file
        outfile << CA.dim1 << "\t" << CA.dim2 << endl;
    }

    // Iterate over each cell in the grid
    for(int x = 0; x < CA.dim1; x++)
    for(int y = 0; y < CA.dim2; y++)
    {
        // Write the value of the specified intial state for each cell to the file
        // Separate each value with a tab character for readability
        outfile << CA.grid[x][y].state_t0 << "\t";

        // Swap new frame value
        CA.grid[x][y].state_t0 = CA.grid[x][y].state_tx;
    }
    // End line before next frame
    outfile << endl;

    // Close the file stream
    outfile.close();
    return 0; // Return 0 to indicate successful execution
}

// The CA Engine that drive the timestep updates
int CA_Engine(CellularAutomata &CA, int n_steps, string outfile_path)
{
    // Update the CA for n_steps and record
    for(int i = 0; i < n_steps; i++)
    {   // Walk over each cell and apply rule
        for(int x = 0; x < CA.dim1; x++)
        {
            for(int y = 0; y < CA.dim2; y++)
            {
            // Current coordinate to explore
            vector<int> coord{x,y};

            // get current tx neighborhood from CA
            //vector<vector<Cell> > neighborhood = CA_t0.get_neighborhood(coord);

            // *******Enforce predefined rule******* Define Rule ID or passing function to engine
            int update_value = majority_rule(CA, coord);

            // Update state_tx
            CA.grid[coord[0]][coord[1]].state_tx = update_value;
            
            }
        }
        
    // Record last frame & swap new frame
    CA_record_swapState(CA, outfile_path);
    
    }
    // Record last updated frame
    CA_record_swapState(CA, outfile_path);

    cout<<"CA_Engine Successfully ran "<< n_steps << " steps and recorded frames to " << outfile_path <<endl;
    
    return 0;
}
