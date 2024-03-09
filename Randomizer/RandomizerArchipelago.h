/**
 * @author      : Louis Marchand (prog@tioui.com)
 * @created     : Fri, 08 Mar 2024 19:51:46 +0000
 * @license     : MIT
 * Class that encapsulate local randomization functionalities
 */

#include "Randomizer.h"

/**
 * A randomizer for the Archipelago system
 */


class RandomizerArchipelago : public Randomizer {

public:

    /**
     * Constructor that connect to an Archipelago server
     * @param server The address and port of the Archipelago server
     * @param name The player name on the archipelago server
     * @param password The password of the room on the archipelago server
     */
    explicit RandomizerArchipelago(const std::string& server, const std::string& name, const std::string& password);

    /**
     * Destructor of the current object
     */
    ~RandomizerArchipelago();

    /**
     * Activate a randomizer check
     * @param check The check to activate
    */
    void activateCheck(std::string check) override;

};

