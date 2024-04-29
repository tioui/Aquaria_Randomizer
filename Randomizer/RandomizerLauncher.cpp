/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Fri, 26 Apr 2024 22:54:43 +0000
 * @license     : MIT
 * A launcher for the game
 */

#include "RandomizerLauncher.h"

#include <filesystem>

/**
 * Initialisation of the Launcher
 *
 * @return Always true
 */
bool RandomizerLauncher::OnInit() {
    std::filesystem::path lFilepath = std::string("randomizer_files");
    if (!std::filesystem::is_directory(lFilepath)) {
        error = true;
        messageBox("Randomizer error", "The randomizer_files directory is not found. Closing.");
    } else {
        error = false;
        frame = new RandomizerLauncherFrame();
        frame->Show();
    }
    return true;
}

/**
 * True if an error occured at creation
 * @return true if an error occured.
 */
bool RandomizerLauncher::hasError() const {
    return error;
}

/**
 * Retreive the generated randomizer.
 * @return The randomizer
 */
Randomizer *RandomizerLauncher::getRandomizer() {
    return frame->getRandomizer();
}

