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

#include "DSQ.h"
#include "../Randomizer/RandomizerLocal.h"
#include "../Randomizer/RandomizerArchipelago.h"




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
		const char *envPath = 0;
        const char *appImageDir = 0;

        if (argc >= 5 && strncmp(argv[1], "--name", 6) == 0 && strncmp(argv[3], "--server", 8) == 0) {
            std::string lPassword;
            if (argc >= 7 && strncmp(argv[5], "--password", 10) == 0) {
                lPassword = argv[5];
            } else {
                lPassword = "";
            }
            lRandomizer = new RandomizerArchipelago(argv[4], argv[2], lPassword);
        } else if (argc > 1) {
            lRandomizer = new RandomizerLocal(argv[1]);
        } else {
            std::cerr << "Usage: " << argv[0] << " <local filename>" << std::endl;
            std::cerr << "Usage: " << argv[0] << " --name <Name> --server <ServerIP:Port>[ --password <Room password>]" << std::endl;
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
                     "Aquaria_Randomizer_" + lRandomizer->getUid(), lRandomizer);
            dsql.init();
            dsql.main();
            dsql.shutdown();
        }
        delete(lRandomizer);
		return (0);
	}

