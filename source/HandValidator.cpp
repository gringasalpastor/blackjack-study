#include "HandValidator.h"

#include "HandDisplay.h"

// constants
const char* HandValidator::handActions[4] = {"Hit", "Stand", "Double", "Split"};

const int HandValidator::hardHand[6][10] = {
    {HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Stand, HandValidator::Stand,
     HandValidator::Stand, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand,
     HandValidator::Stand, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand,
     HandValidator::Stand, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand,
     HandValidator::Stand, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand,
     HandValidator::Stand, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand,
     HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand}

};
const int HandValidator::doubleHand[4][10] = {
    {HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit,
     HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Hit, HandValidator::Double, HandValidator::Double, HandValidator::Double,
     HandValidator::Double, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Double, HandValidator::Double, HandValidator::Double, HandValidator::Double,
     HandValidator::Double, HandValidator::Double, HandValidator::Double, HandValidator::Double, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Double, HandValidator::Double, HandValidator::Double, HandValidator::Double,
     HandValidator::Double, HandValidator::Double, HandValidator::Double, HandValidator::Double, HandValidator::Double}

};
const int HandValidator::pairedHand[10][10] = {
    {HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split,
     HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split},

    {HandValidator::Hit, HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split,
     HandValidator::Split, HandValidator::Split, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split,
     HandValidator::Split, HandValidator::Split, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Split,
     HandValidator::Split, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Double, HandValidator::Double, HandValidator::Double, HandValidator::Double,
     HandValidator::Double, HandValidator::Double, HandValidator::Double, HandValidator::Double, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split,
     HandValidator::Split, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split,
     HandValidator::Split, HandValidator::Split, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split,
     HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split},

    {HandValidator::Stand, HandValidator::Split, HandValidator::Split, HandValidator::Split, HandValidator::Split,
     HandValidator::Split, HandValidator::Stand, HandValidator::Split, HandValidator::Split, HandValidator::Stand},

    {HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand,
     HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand},

};

const int HandValidator::softHand[7][10] = {
    {HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Double,
     HandValidator::Double, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Double,
     HandValidator::Double, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Double, HandValidator::Double,
     HandValidator::Double, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Double, HandValidator::Double,
     HandValidator::Double, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Hit, HandValidator::Double, HandValidator::Double, HandValidator::Double,
     HandValidator::Double, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Hit, HandValidator::Stand, HandValidator::Double, HandValidator::Double, HandValidator::Double,
     HandValidator::Double, HandValidator::Stand, HandValidator::Stand, HandValidator::Hit, HandValidator::Hit},

    {HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand,
     HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand, HandValidator::Stand}};

HandValidator::HandValidator() {}

const char* HandValidator::actionToString(HandValidator::Action a) { return handActions[a]; }
