# macOS installation

To play the Aquaria randomizer, you need to own a copy of the original Aquaria game. The game can be bought in almost every online game sellers (GOG, Steam, etc.)

First, you will need to get your hand on a folder of the original Aquaria game. Only the game ressources (music, voice, images, etc.) are necessary; so it does not
need to be a macOS version (Linux or Windows should do). Since the game does not have a macOS version on GOG or Steam (so, you cannot download the game on those platform), you will need to use
another way of getting the folder. There is a lot of way this step can be done (download if from another computer that uses another OS, using an app like Parallelle, Whisky,
Crossover,etc.)

Untar the Aquaria randomizer release and copy all extracted files in the Aquaria game folder (the one you copy before). The extracted files are those:
- aquaria_randomizer
- aquaria_randomizer_launch
- randomizer_files
- usersettings.xml
- cacert.pem

If there is a conflict between file in the original game folder and the extracted files, you should override the original files with the one of the extracted randomizer files.

TODO: Be sure nothing have to be installed to make the randomizer work (like wxwidgets).

The randomizer should worked now. But the way macOS (or finder) start executable file,if you simply double click on the `aquaria_randomizer` file, the game will not work.
This is because the game cannot see the ressources of the Aquaria foldre because it does not search on the correct folder (it search the ressources on the user home folder).
So, a script named `aquaria_randomizer_launch` can be used to launch the game correctly.
 
Once the randomizer is installed you can launch it. For details about the execution options, see: [execution_linux.md](execution_linux.md)

