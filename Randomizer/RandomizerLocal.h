/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Wed feb 15, 2024 21:30:04 EST
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
    void activateLocation(std::string check) override;


private:

    /**
     * Randomizer version
     */
    int version;

    /**
     * Replacement of every items with count.
     */
    std::vector<itemReplacement*> *itemsReplacement;

    /**
     * Add a number of item in the `itemsRemplacement` list
     * @param item The item to add
     * @param count The number of item to add
     */
    void addItemReplacement(int item, int count) const;

};