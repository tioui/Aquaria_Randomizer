Aquaria Randomizer
==================

> [!WARNING]
> Warning: this project is presently in beta.

This repository is a clone of the Aquaria game repository
(https://github.com/AquariaOSE/Aquaria) and has been modified to be used as
a Randomizer.

Generating a local randomize JSON file
--------------------------------------

An HTML page that can generate randomize JSON file can be found in the `Randomizer_generator/local` directory.

Alternatively, you can use the online generator [here](https://tioui.com/aquaria_randomizer_generator/).


What are the current checks managed by the randomizer
-----------------------------------------------------

For now, every Sing bulbs, Mithalas urns, Sunken City crates, collectable treasures
and the third cooking plate are the checks.

> [!NOTE] 
> Note that every recipes in the randomizer can be found in the checks.

> [!NOTE]
> Also note that it is not possible to get a recipe from anywhere other than
the checks.


What it the modifications done to the game
------------------------------------------

- Recipes have to be learned by check before being cooked (by getting dishes).
- Every dishes can be learn in checks.
- Before you get the recipe, ennemies drop ingredients used to create the dish.
- Once you get the recipe, ennemies can drop the dish.
- In the veil bottom area, a swamp cake (close to the health upgrade) and a special bulb (in the spirit path) has been swapped.
- In the Naija's home, there is Fish Oil on the ground instead of Hearty Soup.
- Adaptation make to checks so that every dishes are found in checks:
  - Adding a poisonloaf in the empty urn in the cathedral right area
  - Replacing the 4 fleas in an urn of the cathedral right area by poison soup
  - Replacing Plant Leafs in a bulb by a Buttery Sea Loaf in the Open Water Top Left area.
  - Replacing the open water skeleton path bulb with 2 baby deep shrimp in it with a Tasty Cake.
  - Replacing the cathedral left area urn with a toad in it with a Rainbow Soup.
  - Replacing the abyss right area bulb with an Hatchet Fish in it with a Tasty roll.
  - Replacing a bulb containing Plant leafs in the Sun Temple by a Magic Soup.
  - Replacing the content of 2 bulbs that contain 2 Plant Leafs in Mithalas City by Vedha Sea Crisp.
  - Replacing one of the icecream bulb in the Ice cave by a Veggie Ice Cream.
  - Replacing one of the icecream bulb in the Ice cave by a Berry Ice Cream.
  - Replacing the Crab Cake bulb in a bulb of the Bubble Cave by a Cold Soup.
  - Replacing a bulb containing 2 plant leafs by a Zuuna's Perogi.
  - Replacing a 4 Plant Leafs bulb in the final boss area by a Vedha's Cure-All
  - Replacing a 4 Eel Oils bulb in the final boss area by a Loaf Of Life.

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

Good luck with that! If you succeed, tell me. I accept pull request.

Compilation on Mac OS X
-----------------------

I don't know. If you succeed, tell me. I accept pull request.

Installation
============

To install the executable you need an official Aquaria installation directory. The installation will
occured in the official Aquaria directory.

1. Copy the `aquaria_randomizer` executable in the official Aquaria directory (in the root);
```bash
cp -p build/aquaria_randomizer /path/to/aquaria/dir/
```
2. Copy the `files` directory as an `override`
```bash
cp -rp files /path/to/aquaria/dir/override
```

You should now be able to launch the randomizer with
```bash
cd /path/to/aquaria/dir
./aquaria_randomizer aquaria_randomized.json
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
