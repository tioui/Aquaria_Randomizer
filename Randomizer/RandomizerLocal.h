/**
 * @author      : Louis Marchand (prog@tioui.com)
 * @created     : mercredi feb 15, 2024 21:30:04 EST
 * @license     : MIT
 * Class that encapsulate local randomization functionalities
 */

#include "Randomizer.h"

/**
 * A randomizer using a local JSON file to randomize
 */
class RandomizerLocal : public Randomizer {

public:

    /**
     * Constructor for using a local json file
     * @param filename The json filename
     */
    explicit RandomizerLocal(const std::string& filename);

    /**
     * Destructor of the current object
     */
    ~RandomizerLocal() override;

    /**
     * Activate a randomizer check
     * @param check The check to activate
    */
    void activateCheck(std::string check) override;

    /**
     * Lunched at each game loop iteration
     */
    void update() override;

private:

    /**
     * Randomizer version
     */
    int version;

    /**
     * Replacement of every checks.
     */
    std::vector<int> *checksReplacement;

};