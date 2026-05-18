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

You also have to install homebrew and the wxwidgets library to make the randomizer work:

1) Open a terminal from spotlight using the shortcut `Cmd + Space`, typing `Terminal` and pressing `Enter`.
2) In the terminal and type this command and follow the instructions (it is recommended to use `copy+paste` here):
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
You will have to enter your user password multiple times (continue typing the password even if no character is printed on the terminal; press `Enter` when done). Also, press `Enter` to confirm the installation of "Xcode Command Line Tools". The downloading can be quite long; you will have to be patient.

3) Then, install the libraries:
```
/opt/homebrew/bin/brew install wxwidgets
```
If you get an error `no such file or directory`, try this one:
```
/usr/local/bin/brew install wxwidgets
```

That's all. The randomizer should work now. You can not try to launch it. For details about the execution options, see: [execution_macos.md](execution_macos.md)


