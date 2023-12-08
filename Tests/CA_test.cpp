#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
using namespace std;
#include "myCA.h"







int main()
{
    CellularAutomata test_CA_t0;
    string outfile_path = "Test_CA_output.txt";

    CA_setup_dimension(test_CA_t0, 2, 9, 9, 1);

    CA_setup_neighborhood(test_CA_t0, 1);

    CA_setup_boundtype(test_CA_t0, 3, 1);

    CA_init_state(test_CA_t0, 0.50, 1);

    CA_Engine(test_CA_t0, 10, outfile_path);

return 0;
}
