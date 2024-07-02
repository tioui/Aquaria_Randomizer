/*
Copyright (C) 2007, 2010 - Bit-Blot

This file is part of Aquaria.

Aquaria is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <iostream>
#include <filesystem>
#include <RandomizerBoxing.h>

#include "DSQ.h"
#include "../Randomizer/RandomizerLocal.h"
#include "../Randomizer/RandomizerArchipelago.h"

#ifndef RANDOMIZER_NO_LAUNCHER
#include "../Randomizer/RandomizerLauncher.h"
#endif


#ifdef BBGE_BUILD_WINDOWS
	#include <shellapi.h>
#endif


#if defined(BBGE_BUILD_WINDOWS) && !defined(BBGE_BUILD_SDL)
	int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
						HINSTANCE	hPrevInstance,		// Previous Instance
						LPSTR		lpCmdLine,			// Command Line Parameters
						int			nCmdShow)			// Window Show State
	{
		#ifdef _DEBUG
			_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); 
			_CrtSetReportMode ( _CRT_ERROR, _CRTDBG_MODE_DEBUG);
		#endif

        std::string dsqParam = GetCommandLine();

#else

	extern "C" int main(int argc,char *argv[])
	{
        Randomizer *lRandomizer = nullptr;
        std::string dsqParam = ""; // fileSystem
        std::string extraDataDir = "";
        std::string appImageExtraDir = "";
        const char *envPath = nullptr;
        const char *appImageDir = nullptr;
        setlocale(LC_ALL, ".UTF8");
        if ((!getenv("APPIMAGE")) && argc > 1) {
            std::filesystem::path lFilepath = std::string("randomizer_files");
            if (!std::filesystem::is_directory(lFilepath)) {
                std::cerr << "The randomizer_files directory is not found. Closing." << std::endl;
                exit(1);
            }
        }

        if (argc >= 5 && strncmp(argv[1], "--name", 6) == 0 && strncmp(argv[3], "--server", 8) == 0) {
            std::string lPassword;
            bool lSelfMessage = false;
            bool lDeathLink = false;
            int lMessageIndex = 5;
            if (argc >= 7 && strncmp(argv[5], "--password", 10) == 0) {
                lPassword = argv[6];
                lMessageIndex = 7;
            } else {
                lPassword = "";
            }
            if (argc >= lMessageIndex + 2 && strncmp(argv[lMessageIndex], "--message", 9) == 0) {
                lSelfMessage =  strncmp(argv[lMessageIndex + 1], "self", 4) == 0;
                lMessageIndex = lMessageIndex + 2;
            }
            if (argc >= lMessageIndex + 1 && strncmp(argv[lMessageIndex], "--deathlink", 1) == 0) {
                lDeathLink = true;
                lMessageIndex = lMessageIndex + 1;
            }
            lRandomizer = new RandomizerArchipelago(argv[4], argv[2], lPassword, lSelfMessage, lDeathLink);
        } else if (argc == 2 && strncmp(argv[1], "--help", 6) != 0) {
            lRandomizer = new RandomizerLocal(argv[1]);
#ifndef RANDOMIZER_NO_LAUNCHER
        } else if (argc == 1) {
            RandomizerBoxing * lBoxing = new RandomizerBoxing();
            RandomizerLauncher *lLauncher = new RandomizerLauncher("Aquaria_Randomizer", lBoxing);
            wxApp::SetInstance( lLauncher );
            wxEntryStart( argc, argv );
            wxTheApp->CallOnInit();
            if (!lLauncher->hasError()) {
                wxTheApp->OnRun();
            }
            lRandomizer = lBoxing->getRandomizer();
            delete lBoxing;
            wxTheApp->OnExit();
            wxEntryCleanup();
            if (lRandomizer == nullptr) {
                exit(0);
            }
#endif
        } else {
#ifndef RANDOMIZER_NO_LAUNCHER
            std::cerr << "Usage: " << argv[0] << std::endl;
#endif
            std::cerr << "Usage: " << argv[0] << " <local filename>" << std::endl;
            std::cerr << "Usage: " << argv[0] <<
                      " --name <Name> --server <ServerIP:Port>[ --password <Room password>]" <<
                      "[ --message self][ --deathlink]" << std::endl;
            std::cerr.flush();
            exit(1);
        }
        if (lRandomizer->hasError()) {
            std::cerr << lRandomizer->getErrorMessage() << std::endl;
            std::cerr.flush();
            exit(1);
        }


#ifdef BBGE_BUILD_UNIX
		envPath = getenv("AQUARIA_DATA_PATH");
		if (envPath)
		{
			dsqParam = envPath;
		}
        appImageDir = getenv("APPIMAGE");
        if (appImageDir)
        {
            std::filesystem::path appImagePath = appImageDir;
            appImageExtraDir = appImagePath.parent_path();
        }
#endif
#ifdef AQUARIA_DEFAULT_DATA_DIR
		if(!envPath)
			dsqParam = AQUARIA_DEFAULT_DATA_DIR;
#endif
#ifdef AQUARIA_EXTRA_DATA_DIR
		extraDataDir = AQUARIA_EXTRA_DATA_DIR;
#endif

#endif

        if (lRandomizer){
            DSQ dsql(dsqParam, extraDataDir, appImageExtraDir,
                     "Aquaria_Randomizer", lRandomizer, lRandomizer->getUid());
            dsql.init();
            dsql.main();
            dsql.shutdown();
        }
        delete(lRandomizer);
		return (0);
	}

