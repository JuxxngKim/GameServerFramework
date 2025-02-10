#pragma once

namespace sf
{
	class GameServerApp
	{
	public:
		GameServerApp();
		~GameServerApp();

	public:
		int Run();

	private:
		bool LoadConfig();
		bool ServiceRunByCommand();
		bool Initialize();
		bool RunLoop();

	};
}