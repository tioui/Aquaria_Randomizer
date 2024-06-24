# Linux installation

Please note that you can also use an AppImage to use the Randomizer. The AppImage is easyier to use. For the AppImage installation, see here: [install_appimage.md](install_appimage.md)

To play the Aquaria randomizer, you need to own a copy of the original Aquaria game. The game can be bought in almost every online game sellers (GOG, Steam, etc.)

First, you should copy the original Aquaria folder game. The original game use 4 .so files (`libgcc_s.so.1`, `libopenal.so.1`, `libSDL-1.2.so.0` and `libstdc++.so.6`) that are old and will not work with the randomizer. So to keep the original game working, you should copy the game folder elsewhere for the randomizer and remove the 4 .so file.

Untar the Aquaria randomizer release and copy all extracted files in the Aquaria game folder (the one you copy before). The extracted files are those:
- aquaria_randomizer
- randomizer_files (directory)
- usersettings.xml
- cacert.pem

If there is a conflict between file in the original game folder and the extracted files, you should override the original files with the one of the extracted randomizer files.

Then, you should use your system package manager to install liblua5, libogg, libvorbis, libopenal libsdl2 and libwxWidgets.
On Debian base system (like Ubuntu), you can use the following command:

```bash
sudo apt install liblua5.1-0-dev libogg-dev libvorbis-dev libopenal-dev libsdl2-dev libssl-dev libwxgtk3.0-gtk3-dev
```

Note that on the latest Debian system, you should use `libwxgtk3.2-gtk3-dev` instead of `libwxgtk3.2-dev`.

Once the randomizer is installed you can launch it. For details about the execution options, see: [execution_linux.md](execution_linux.md)

