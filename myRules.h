

#include "myCA_edit.h"


class Rule {
public:
    virtual int apply(Neighborhood &neighborhood, const std::map<string, int>& states_list) = 0;
    virtual ~Rule() {}
};

// Rule for majority rule that returns update value
class MajorityRule : public Rule {
public:
    int apply(Neighborhood &neighborhood, const std::map<string, int>& states_list) override {
        // Map for storing frequency of states
        std::map<int, int> frequencyMap;

        // Iterate through each cell in the neighborhood map
        for (const auto &cellEntry : neighborhood.subgrid) {
            const Cell &cell = cellEntry.first;
            frequencyMap[cell.getState_t0()]++;
        }

        // Determine the state with the maximum frequency
        int maxFrequencyValue = 0;
        int maxFrequency = 0;
        for (const auto &entry : frequencyMap) {
            if (entry.second > maxFrequency) {
                maxFrequency = entry.second;
                maxFrequencyValue = entry.first;
            }
        }

        return maxFrequencyValue;
    }
};

// Rule for straight conditional
class StraightConditionalRule : public Rule {
public:
    int apply(Neighborhood &neighborhood, const std::map<string, int>& states_list) override {
        // Implement straight conditional rule logic
    }
};

// Rule for Activation-Inhibition conditional
class ActivationInhibitionRule : public Rule {
private:
    std::map<string, int> long_short_weights;

public:
    ActivationInhibitionRule(const std::map<string, int>& weights) : long_short_weights(weights) {}

    int apply(Neighborhood &neighborhood, const std::map<string, int>& states_list) override {
        // Implement activation-inhibition rule logic
        // You can use long_short_weights here
    }
};

// Rule for conditional transition rule
class ConditionalTransitionRule : public Rule {};

// Rule for parity rule
class ParityRule : public Rule {};