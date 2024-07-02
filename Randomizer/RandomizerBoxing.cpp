//
// Used to store a Randomizer
// Created by Louis M on 24-07-02.
//

#include "RandomizerBoxing.h"

/**
* Constructor of `this`
*/
RandomizerBoxing::RandomizerBoxing(){
    randomizer = nullptr;
}

/**
* Assign the Randomizer inside the box
* @param aRandomizer The randomizer to assign.
*/
void RandomizerBoxing::setRandomizer(Randomizer *aRandomizer){
    randomizer = aRandomizer;
}

/**
* Return the randomizer inside the box.
* @return the randomizer
*/
Randomizer *RandomizerBoxing::getRandomizer(){
    return randomizer;
}