/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Fri, 26 Apr 2024 22:54:43 +0000
 * @license     : MIT
 * A launcher for the game
 */

#include "RandomizerLauncher.h"

#include <filesystem>

RandomizerLauncher::RandomizerLauncher(std::string aUserFolderName) {
    error = false;
    #if defined(BBGE_BUILD_UNIX)
        const char *envr = getenv("HOME");
        if (envr == NULL)
            envr = ".";  // oh well.
        const std::string home(envr);

        createDir(home);  // just in case.
        #ifdef BBGE_BUILD_MACOSX
            const std::string prefix("Library/Application Support/");
        #else
            const std::string prefix(".");
        #endif
        userDataFolder = home + "/" + prefix + aUserFolderName;
        createDir(userDataFolder);
    #else
        userDataFolder = ".";
    #endif
}

/**
 * Initialisation of the Launcher
 *
 * @return Always true
 */
bool RandomizerLauncher::OnInit() {
    std::filesystem::path lFilepath = std::string("randomizer_files");
    if ((!getenv("APPIMAGE")) && !std::filesystem::is_directory(lFilepath)) {
        error = true;
        messageBox("Randomizer error", "The randomizer_files directory is not found. Closing.");
    } else {

        frame = new RandomizerLauncherFrame(userDataFolder);
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

