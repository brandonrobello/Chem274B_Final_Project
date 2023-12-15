#include <fstream>
#include "myCA_edit.h"
#include "COVID.h"

SIRRule::SIRRule(double vacc_rate, double mask_rate) : vaccination_rate(vacc_rate), mask_wearing_rate(mask_rate) {}

int SIRRule::apply(Neighborhood &neighborhood, const std::map<string, int>& states_list) {
    int current_state = neighborhood.subgrid[boundary_cell]; // Current state of the central cell

    // Count the number of infected neighbors
    int infected_count = 0;
    for (const auto& cellEntry : neighborhood.subgrid) {
        if (cellEntry.first.getState_t0() == states_list.at("I")) {
            infected_count++;
        }
    }

    // Apply SIR (susceptible (S), infected (I), or recovered (R)) model rules with vaccination and mask-wearing factors
    if (current_state == states_list.at("S") && infected_count > 0) {
        // Susceptible cell gets infected based on infection probability
        if ((double)rand() / RAND_MAX > vaccination_rate * (1.0 - mask_wearing_rate)) {
            return states_list.at("I");
        } else {
            return states_list.at("S"); // Vaccinated or mask-wearing individuals resist infection
        }
    } else if (current_state == states_list.at("I")) {
        // Implement recovery logic, e.g., after a certain number of time steps
        return states_list.at("R");
    } else {
        return current_state; // No change for recovered or unaffected cells
    }
}
