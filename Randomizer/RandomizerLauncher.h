/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Fri, 26 Apr 2024 22:54:43 +0000
 * @license     : MIT
 * A launcher for the game
 */

#ifndef AQUARIA_RANDOMIZER_LAUNCHER_H
#define AQUARIA_RANDOMIZER_LAUNCHER_H

#include <wx/wx.h>
#include "Randomizer.h"
#include "RandomizerLauncherFrame.h"

class RandomizerLauncher : public wxApp {
public:
    /**
     * Initialisation of the Launcher
     *
     * @return Always true
     */
    bool OnInit() override;

    /**
     * Retreive the generated randomizer.
     * @return The randomizer
     */
    Randomizer *getRandomizer();
private:
    /**
     * The Window of the launcher.
     */
    RandomizerLauncherFrame *frame;
};


#endif //AQUARIA_RANDOMIZER_LAUNCHER_H
