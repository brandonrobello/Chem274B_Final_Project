#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
using namespace std;
#include "myCA_edit.h"







int main()
{
    CellularAutomata test_CA_majority;
    MajorityRule majorityrule;
    string CAframe_outfile_path = "Test_CAframe_output.txt";
    string CellState_outfile_path = "Test_frameCellState_output.txt";


    test_CA_majority.setup_dimension(2, 9, 9);

    test_CA_majority.setup_neighborhood(MOORE);

    test_CA_majority.set_boundtype(STATIC, 1);

    test_CA_majority.init_CA_state(0);

    test_CA_majority.init_CA_stateWprob(2, 0.25);

    for (int step = 0; step < 2; step++)
    {
        cout << "step " << step << " Frame:" << endl;
        test_CA_majority.print();
        test_CA_majority.record_CAframe(CAframe_outfile_path);
        test_CA_majority.update(majorityrule);
        test_CA_majority.swapState();
        cout << "After update and swap, Frame:" << endl;
                test_CA_majority.print();

    }


return 0;
}
