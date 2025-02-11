#include "GameServerApp.h"
#include "pch.h"
#include "FileSystem.h"

namespace sf
{
	GameServerApp::GameServerApp()
	{
	}

	GameServerApp::~GameServerApp()
	{
	}

	int GameServerApp::Run()
	{
		if (!LoadConfig()) return -2;
		if (!ServiceRunByCommand()) return -3;

		return 0;
	}

	bool GameServerApp::LoadConfig()
	{
		return true;
	}

	bool GameServerApp::ServiceRunByCommand()
	{
		auto args = FileSystem::CommandLineToArgv();

		return true;
	}

	bool GameServerApp::Initialize()
	{
		return true;
	}

	bool GameServerApp::RunLoop()
	{
		return true;
	}
}

