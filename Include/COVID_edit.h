#pragma once

#include "myCA_edit.h"
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

#define EMPTY           0
#define HEALTHY         1
#define HEALTHY_VACCED  2
#define INFECTED        3
#define RECOVERED       4

class recoveryRule: public Rule {
private:
    std::map<std::string, int> infection_period_tracker;
    double recoverRate;

public:
    //onstructor
    recoveryRule(double Rate) : recoverRate(Rate) {}; // Seed the random number generator
    
    /// Rule application  
    int apply(Neighborhood &neighborhood) override {
        Cell centerCell = neighborhood.center_cell;

        if (centerCell.getState_t0() == 3) { // Assuming 3 is the infected state
            vector<int> CCpos = centerCell.getPosition();
            int x = CCpos[0];
            int y = CCpos[1];

            // Casting the x,y position of the center cell that == 3 
            std::string identifier = std::to_string(x) + "," + std::to_string(y);

            infection_period_tracker[identifier]++;

            int multiplier = infection_period_tracker[identifier];
            double Period_RR = recoverRate * multiplier;

            double randomValue = static_cast<double>(rand()) / RAND_MAX;
            if (randomValue <= Period_RR) {
                return RECOVERED; 
                infection_period_tracker.erase(identifier); // Remove tracker from list after recovery
            }
        }

        return centerCell.getState_t0(); // Return the current state if no change
    }
};


class VaccinationRule : public Rule {

    private:

        double vaccination_prob_;
        int seed = 1;

    public:

        VaccinationRule(double vaccination_prob):vaccination_prob_(vaccination_prob) {}

        int apply(Neighborhood &neighborhood) override {
            
            int current_state = neighborhood.center_cell.getState_t0();
            // Skip cell updating if it's currently not healthy unvacced
            if (current_state != HEALTHY) {
                return current_state;
            }

            // Probability
            double randomValue = static_cast<double>(rand()) / RAND_MAX;
            
            
            if (randomValue <= vaccination_prob_) {
                // If probability satisfies, change the state to healthy vaccinated
                return HEALTHY_VACCED;
            }
            else {
                return current_state;
            }
        }
};


class InfectionRule: public Rule {

    private:

        double infecion_rate_;
        double immunity_multiplier_;

    public:

        InfectionRule(double infecion_rate, double immunity_multiplier):infecion_rate_(infecion_rate), immunity_multiplier_(immunity_multiplier) {}

        int apply(Neighborhood &neighborhood) override{

            int current_state = neighborhood.center_cell.getState_t0();

            // Skip for empty and infected cells
            if (current_state == EMPTY || current_state == INFECTED) {
                return current_state;
            }

            int infected_count = 0;

            for (const auto &cellEntry : neighborhood.subgrid) {

                const Cell &cell = cellEntry.first; // Gets the cell

                int cell_state = cell.getState_t0();// Gets the state of the cell

                if (cell_state == INFECTED) {
                    infected_count++;
                }
            }
                        
            // Probability
            //srand(static_cast<unsigned int>(time(0)));
            double randomValue = static_cast<double>(rand()) / RAND_MAX;

            if (current_state == HEALTHY){
                if (randomValue <= infected_count*infecion_rate_) {
                    return INFECTED;
                }
                else {
                    return current_state;
                }
            }
            // Additional immunity multiplier for vaccinated cells
            if (current_state == HEALTHY_VACCED){
                if (randomValue <= infected_count*infecion_rate_*immunity_multiplier_) {
                    return INFECTED;
                }
                else {
                    return current_state;
                }
            }
            return 0;
        }
};


class ReinfectionRule : public Rule {

    private:

        double reinfection_rate_;
        double recovery_immunity_;

    public:

        ReinfectionRule(double reinfection_rate, double recovery_immunity):reinfection_rate_(reinfection_rate), recovery_immunity_(recovery_immunity) {}

        int apply(Neighborhood &neighborhood) override {
            
            int current_state = neighborhood.center_cell.getState_t0();

            // Skip updating for non-recovered cells
            if (current_state != RECOVERED) {
                return current_state;
            }
            
            int infected_count = 0;

            for (const auto &cellEntry : neighborhood.subgrid) {

                const Cell &cell = cellEntry.first; // Gets the cell

                int cell_state = cell.getState_t0();// Gets the state of the cell
                
                if (cell_state == INFECTED) {
                    infected_count++;
                }
            }

            // Probability
            //srand(static_cast<unsigned int>(time(0)));
            double randomValue = static_cast<double>(rand()) / RAND_MAX;

            // Compute probability, update if the prob satisfies
            if (randomValue <= infected_count * reinfection_rate_ * recovery_immunity_) {
                return INFECTED;
            }
            else {
                return current_state;
            }
        }
};















/*
 if (centerCell.getState_t0() == 3){
            for (const auto &cellEntry : neighborhood.subgrid){
                int nieghborCounter = 0;
                int current_state = cellEntry.first.getState_t0();
                if (current_state == 3){
                    nieghborCounter++;
                }
            }

            int newState = 
        }

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






vector<int> CCpos = neighborhood.center_cell.getPosition();
            int x = CCpos[0];
            int y = CCpos[1];

            cout << "current cell" << x <<","<< y << "|Random Value:" << randomValue << "|Vac Prob:" << vaccination_prob_ <<endl;    




*/