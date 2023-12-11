// Implementation of Cellular Automata Cell Class
#include "myCA_edit.h"

Cell::Cell() {}
Cell::~Cell() {}

// Cell feature setter
int Cell::setFeature(string feature, double value)
{
    auto it = features.find(feature);
    // If feature exists
    if (it == features.end()) {
        cout<<"Feature not found!"<<endl;
        return -1;
    }
    it -> second = value;
}

// Cell feature getter
double Cell::getFeature(string feature) const
{
    auto it = features.find(feature);
    // If feature exists
    if (it == features.end()) {
        cout<<"Feature not found!"<<endl;
        return -1;
    }
    return it -> second;
}

// Cell state t0 getter
int Cell::getState_t0() const
{
    return this->state_t0;
}
// Cell state t0 setter
int Cell::setState_t0(int state)
{
    this->state_t0 = state;
    return 1;
}

// Cell state tx getter
int Cell::getState_tx() const
{
    return this->state_tx;
}
// Cell state tx setter
int Cell::setState_tx(int state)
{
    this->state_tx = state;
    return 1;
}

// x and y position getter
vector<int> Cell::getPosition() const
{
    return vector<int>{this->x, this->y};
}

// Method to swap state_tx and state_to, to make the new value (tx) the current value (t0)
int Cell::cell_update()
{
    swap(this->state_t0, this->state_tx);
}
