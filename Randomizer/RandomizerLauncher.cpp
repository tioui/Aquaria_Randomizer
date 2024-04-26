/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Fri, 26 Apr 2024 22:54:43 +0000
 * @license     : MIT
 * A launcher for the game
 */

#include "RandomizerLauncher.h"

/**
 * Initialisation of the Launcher
 *
 * @return Always true
 */
bool RandomizerLauncher::OnInit() {
    frame = new RandomizerLauncherFrame();
    frame->Refresh();
    frame->Show();
    return true;
}

/**
 * Retreive the generated randomizer.
 * @return The randomizer
 */
Randomizer *RandomizerLauncher::getRandomizer() {
    return frame->getRandomizer();
}

