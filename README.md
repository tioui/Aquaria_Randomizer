Aquaria Randomizer
==================

> [!WARNING]
> Warning: this project is presently in beta.

This repository is a clone of the Aquaria game repository
(https://github.com/AquariaOSE/Aquaria) and has been modified to be used as
a Randomizer.

Generating a local randomize JSON file
--------------------------------------

You can generate a local JSON randomizer file at this address: https://aquariarandomizer.tioui.com/

What are the current checks managed by the randomizer
-----------------------------------------------------

Every songs (and forms), li, transportation turtles, sing bulbs, Mithalas urns, Sunken City crates,
collectable treasures and the third cooking plate are the checks.

> [!NOTE] 
> Note that every recipes in the randomizer can be found in the checks.

> [!NOTE]
> Also note that it is not possible to get a new recipe from anywhere other than
the checks.

Compilation
===========

Compilation on Linux Ubuntu
---------------------------

First, be sure to have the needed libraries
```bash
sudo apt install build-essential cmake liblua5.1-0-dev libogg-dev libvorbis-dev libopenal-dev libsdl2-dev git
```

Then, clone the project with the --recursive flag some place

```bash
git clone --recursive https://github.com/tioui/Aquaria_Randomizer.git
cd Aquaria_Randomizer
```

Then, launch the compilation.

```bash
mkdir build
cd build
cmake -DAQUARIA_USE_SDL2=1 ..
make
```

The executable will be the `aquaria_randomizer` executable.

Compilation on Windows
----------------------

I use Mingw32 include in MSYS2 to compile. Here is the commands:

```bash
mkdir build
cd build
/mingw32/bin/cmake -DOPENAL_LIBRARY=../ExternalLibs/AL/lib/win32 -DOPENAL_INCLUDE_DIR=../ExternalLibs/AL/inclue -DAQUARIA_USE_SDL2=1 -DCMAKE_BUILD_TYPE=Release -DWIN32_TRUE=1 -DMSYS=1 -DOPENSSL_TOOLCHAIN="" -G "Unix Makefiles" ..
make
```

Compilation on Mac OS X
-----------------------

I don't know. If you succeed, tell me. I accept pull request.

Installation and execution
==========================

Windows
-------

First, you should copy the original Aquaria folder game. The randomizer will possibly modify the game so that
the original game will stop working. Copying the folder will guarantee that the original game keeps on working.
Also, in Windows, the save files are stored in the Aquaria folder. So copying the Aquaria folder for every Multiworld
game you play will make sure that every game has their own save game.

Then you need to transfert those files and directories of the current repository in the Aquaria game folder:
- aquaria_randomizer.exe -> from your build folder (see above)
- OpenAL32.dll -> from `ExternalLibs/AL/lib/win32
- wrap_oal.dll -> `ExternalLibs/AL/lib/win32`
- override -> by renaming the `files` folder
- SDL2.dll -> from `ExternalLibs/SDL2/lib/win32`
- usersettings.xml
- cacert.pem

If there is a conflict between file in the original game folder and the unzipped files, you should override
the original files with the one of the unzipped randomizer.

Finally, to launch the randomizer, you must use the command line interface (you can open the command line interface
by writing `cmd` in the address bar of the Windows file explorer).

Here is the command line to use to start the local randomizer (with a randomized json file):

```bash
aquaria_randomizer.exe aquaria_randomized.json
```

Here is the command line to use to start the multiworld randomizer (with an Archipelago server):

```bash
aquaria_randomizer.exe --name YourName --server theServer:thePort
```

or, if the room has a password:

```bash
aquaria_randomizer.exe  --name YourName --server theServer:thePort --password thePassword
```

Linux
-----

First, you should copy the original Aquaria folder game. The randomizer will possibly modify the game so that
the original game will stop working. Copying the folder will guarantee that the original game keeps on working.

Untar the Aquaria randomizer release and copy all extracted files in the Aquaria game folder. The extracted
files are those:
- aquaria_randomizer -> from your build folder (see above)
- override (directory) -> by renaming the `files` folder
- usersettings.xml
- cacert.pem

If there is a conflict between file in the original game folder and the extracted files, you should override
the original files with the one of the extracted randomizer files.

Then, you should use your system package manager to install liblua5, libogg, libvorbis, libopenal and libsdl2.
On Debian base system (like Ubuntu), you can use the following command:

```bash
sudo apt install liblua5.1-0-dev libogg-dev libvorbis-dev libopenal-dev libsdl2-dev
```

Also, if there is some `.so` files in the Aquaria original game folder (`libgcc_s.so.1`, `libopenal.so.1`,
`libSDL-1.2.so.0` and `libstdc++.so.6`), you should remove them from the Aquaria Randomizer game folder. Those are
old libraries that will not work on the recent build of the randomizer.

To launch the local randomizer (with a randomized json file), just launch in command line:

```bash
./aquaria_randomizer aquaria_randomized.json
```

To launch the multiworld randomizer (with an archipelago server), just launch in command line:

```bash
./aquaria_randomizer --name YourName --server theServer:thePort
```

or, if the room has a password:

```bash
./aquaria_randomizer --name YourName --server theServer:thePort --password thePassword
```

Note: If you have a permission denied error when using the command line, you can use this command line to be
sure that your executable has executable permission:

```bash
chmod +x aquaria_randomizer
```


Original Aquaria README
=======================


This folder contains all Aquaria sources and necessary build scripts.
However, it does *not* contain any graphical file nor sound. If you
want to play the game, you first need to buy the original
full-featured version (http://www.bit-blot.com/aquaria/) and install
it. Once you have done that, you need to build the files in this
folder (see below for how to do that) and copy the resulting files to
the place where you installed the original full-featured version.

In case of problems, you can get support via IRC:
#bitblot @ irc.esper.net.


[1] BUILDING
------------

Follow these steps to build Aquaria. 

1- Install required dependencies first. This includes a C++ compiler
  and a handful of libraries. Here is a list of the Debian names for
  some of these dependencies:

build-essential cmake liblua5.1-0-dev libogg-dev libvorbis-dev
libopenal-dev libsdl1.2-dev

For Lua, libogg, and libvorbis the included versions can be used instead,
thus a system-wide install of these libs is not required.

2- Create a sub-directory 'cmake-build' and move into it

$ mkdir cmake-build
$ cd cmake-build

3- run cmake

$ cmake ..

Alternatively, if you want to specifiy compile-time options:
(See also [2] SETUP further down)

$ ccmake ..


4- If you miss some dependencies, install them and run cmake again.
   Due to windows lacking package management, it is recommended
   to set all AQUARIA_INTERNAL_* cmake variables to TRUE for win32
   builds, or for self-contained linux builds.

5- run make

$ make

6- If everything went well, the 'aquaria' binary is now in the
   current directory (cmake-build).



[2] SETUP
---------

First, be sure you have an existing installation of Aquaria.
This can be a Windows, Linux, or Mac OSX version, doesn't matter.

Take this directory tree, showing the mandatory subdirs:

Aquaria  <--- this is the directory you want!
 |
 +--- data
 +--- gfx
 +--- mus
 +--- scripts
 +--- sfx
 +--- vox
 +--- ...

There are three ways to setup Aquaria, you may choose the one that
fits your intentions most:


****
*** If you just want to get the thing working right now ***
*** and don't care much about updating frequently       ***
****

After building, copy the executable to your aquaria root directory.
Then copy all files inside the repo's "files" directory
to your Aquaria root dir, replacing everything that exists.

You should *not* remove any file from the Aquaria installation, just
replace some of them with the versions included in the repo.

/!\ Be careful if you do this on a Mac with finder because
    it replaces whole folders instead of just merging the new files in.
    You have been warned.

Lastly, if you want to play the included default mods,
copy game_scripts/_mods over your local _mods directory.



****
*** If you want to hack on Aquaria or update frequently: ***
****

* Linux/OSX: 
Set the AQUARIA_DATA_PATH environment variable to the installation
directory as described above. E.g. add this line to your ~/.profile:

  export AQUARIA_DATA_PATH=~/games/Aquaria

Alternatively, set the AQUARIA_DEFAULT_DATA_DIR compile time option
when building with cmake.

Then, go to $AQUARIA_DATA_PATH and create a symlink
to the updated files directory:

  cd ~/games/Aquaria
  ln -s ~/code/Aquaria-repo/files override

This will make sure that whenever you update the repo, the updated datafiles
from the repo will be loaded instead of those that ship with the game.

Lastly, if you want to play the included default mods,
copy game_scripts/_mods over your local _mods directory.



* Windows:

You'll probably want to install something like this for symlink/junction support:
--> http://schinagl.priv.at/nt/hardlinkshellext/hardlinkshellext.html
(You don't have to, but it's rather tedious to update everything by hand)

Take all subdirs from the Aquaria root directory, and copy them into
path/to/Aquaria-repo/bin, or whereever your compiler will output its executable.
If you are able to, better create junctions to save space.

Note that this will become your main working directory.

Unfortunately you will have to use junctions to link the updated files.
Create a junction in path/to/Aquaria-repo/bin that points to
path/to/Aquaria-repo/files.
Otherwise, if you don't use junctions, copy the files dir by hand should they change.
You can either name it "override" and drop it into bin, or simply copy & replace
its contents into bin if you don't mind keeping your data clean.

Lastly, if you want to play the included default mods,
copy game_scripts/_mods over your local _mods directory.



****
*** If you're a Linux package maintainer ***
****

I assume there is a package for e.g. the Humble Bundle version available;
you'll want to make sure that the game path is fixed and the same
on all user's installs when you set the following cmake options.

Set the AQUARIA_DEFAULT_DATA_DIR cmake option to the game data dir
as described above.
Make sure your package includes all files from the repo's "files" directory.
Set the AQUARIA_EXTRA_DATA_DIR cmake option to the directory where these
extra files will be installed by the package.

An example can be found here:
https://aur.archlinux.org/packages/aquaria-git/

Using this package as data dependecy:
https://aur.archlinux.org/packages/aquaria-data-hib/

You also need to make sure that the mod scripts in ~/.Aquaria/_mods/*/scripts/
are updated with those from the repo's game_scripts/_mods directory.


If this doesn't apply to your setup, ask. [email, github, IRC, ...]






[SDL 1.2 ONLY -- LINUX RUMBLE SUPPORT]
---------------------------------------

SDL 1.2 does not support rumble features, even though Linux does. This
feature will be added in SDL 1.3, which is still a long time coming.

In the meantime there is a hackish rumble implementation for Linux that
needs environment variables to be set that map joysticks via their indices
to event devices. E.g. to map the first joystick to the event device
"/dev/input/event6" you need to run aquaria like this:

$ export AQUARIA_EVENT_JOYSTICK0=/dev/input/event6
$ aquaria

Because aquaria is a single player game you never need to map another joystick
than the first one. Also keep in mind that your joystick event device has
another path. E.g. I use this command to run aquaria:

$ export AQUARIA_EVENT_JOYSTICK0=/dev/input/by-id/usb-©Microsoft_Corporation_Controller_0709960-event-joystick
$ aquaria
