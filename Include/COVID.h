#pragma once

#include "myCA_edit.h"

#define EMPTY 0
#define INF_NOMASK 1
#define INF_MASKED 2
#define HEALTHY_NOMASK 3
#define HEALTHY_MASKED 4

class CovidSusceptibilityRule: public Rule {

    public:
        // This function will aggregate information from the neighboring cells, and output a "suscetibility" value
        int apply(Neighborhood &neighborhood) override{

            double susceptibility_value = 0; // susceptibility_value that will be returned
            int count_1;
            int count_2;
            int old_state = neighborhood.center_cell.getState_t0();

            if (old_state == EMPTY || old_state == INF_NOMASK || old_state == INF_MASKED) {
                // If the cell is already infected or empty, skip the update
                return old_state;
            }
            // Map for storing frequency of states
            for (const auto &cellEntry : neighborhood.subgrid) {

                const Cell &cell = cellEntry.first; // Gets the cell

                int cell_state = cell.getState_t0();// Gets the state of the cell
                // int radius = cellEntry.second;      // Gets the distance of this neighbor
                if (cell_state == INF_NOMASK) {
                    count_1 ++;
                }
                if (cell_state == INF_MASKED) {
                    count_2 ++;
                }
            }

            susceptibility_value += count_1*0.3 + count_2*0.1;

            // Use random number generator to decides update
            srand(static_cast<unsigned int>(time(0)));
            double randomValue = static_cast<double>(rand()) / RAND_MAX;

            if (randomValue <= susceptibility_value) {
                // Set the person to infected
                if (old_state == HEALTHY_MASKED) {
                    return INF_MASKED;
                }
                return INF_NOMASK;
            }
            return old_state;
        }
};