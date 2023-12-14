#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <utility>
#include <vector>
#include <fstream>
# include "myCA_edit.h"

using namespace std;

class SIRRule : public Rule {
private:
    double vaccination_rate;
    double mask_wearing_rate;

public:
    SIRRule(double vacc_rate, double mask_rate);
    int apply(Neighborhood &neighborhood, const std::map<string, int>& states_list, int boundary_cell) override;
};


