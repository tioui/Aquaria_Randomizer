/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Fri, 26 Apr 2024 22:54:43 +0000
 * @license     : MIT
 * A launcher for the game
 */

#ifndef AQUARIA_RANDOMIZER_LAUNCHER_H
#define AQUARIA_RANDOMIZER_LAUNCHER_H

#include "RandomizerBoxing.h"
#include <wx/wx.h>
#include "Randomizer.h"
#include "RandomizerLauncherFrame.h"

class RandomizerLauncher : public wxApp {
public:

    /**
     * Constructor for the Launcher
     *
     * @param userFolderName The folder to store the launcher.xml save file
     * @param boxing The box to store the generated randomizer
     */
    explicit RandomizerLauncher(const std::string& userFolderName, RandomizerBoxing *boxing);

    /**
     * Initialisation of the Launcher
     *
     * @return Always true
     */
    bool OnInit() override;

    /**
     * True if an error occured at creation
     * @return true if an error occured.
     */
    bool hasError() const;
private:
    /**
     * The Window of the launcher.
     */
    RandomizerLauncherFrame *frame{};

    /**
     * True if an error occured at creation
     */
    bool error{};

    /**
     * The preference directory of the user
     */
    std::string userDataFolder;

    /**
     * The boxing used to store the generated randomizer
     */
    RandomizerBoxing *randomizerBoxing;
};


#endif //AQUARIA_RANDOMIZER_LAUNCHER_H
