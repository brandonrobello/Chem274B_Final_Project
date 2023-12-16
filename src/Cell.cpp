// Implementation of Cellular Automata Cell Class
#include "myCA_edit.h"

Cell::Cell() {}
Cell::~Cell() {}

// Cell state t0 getter
int Cell::getState_t0() const
{
    return this->state_t0;
}
// Cell state t0 setter
int Cell::setState_t0(int state)
{
    this->state_t0 = state;
    return 0;
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
    return 0;
}

// x and y position getter
vector<int> Cell::getPosition() const
{
    return vector<int>{this->x, this->y};
}

// Method to swap state_tx and state_to, to make the new value (tx) the current value (t0)
void Cell::cell_update()
{
    this->state_t0 = this->state_tx;
}


void Cell::set_x(int x) 
{
    this->x = x;
}

void Cell::set_y(int y) 
{
    this->y = y;
}

int Cell::get_x() const {return this->x;}

int Cell::get_y() const {return this->y;}


bool Cell::operator<(const Cell& other) const 
{
    if (x != other.x) return x < other.x;
    return y < other.y;
}