//
// Used to store a Randomizer
// Created by Louis M on 24-07-02.
//

#ifndef RANDOMIZERBOXING_H
#define RANDOMIZERBOXING_H

#include "Randomizer.h"

class RandomizerBoxing {
public:

    /**
    * Constructor of `this`
    */
    RandomizerBoxing();

    /**
    * Assign the Randomizer inside the box
    * @param randomizer The randomizer to assign.
    */
    void setRandomizer(Randomizer *randomizer);

    /**
    * Return the randomizer inside the box.
    * @return the randomizer
    */
    Randomizer *getRandomizer();

private:

    Randomizer *randomizer;
};



#endif //RANDOMIZERBOXING_H
