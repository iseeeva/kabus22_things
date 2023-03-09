#include <Windows.h>//GetAsyncKeyState.
#include <chrono>//We will use chrono for the elapsed time.

//Discord SDK Stuff.

#include "include/discord_rpc.h"
#include "include/discord_register.h"
#include "kabus_discord.h"

#pragma region Discord::SetupDiscord

char* Discord::Config::app_id = "";
bool Discord::Config::rpc_initized = false;
bool Discord::Config::rpc_in_use = false;

void Discord::SetupDiscord()
{
	if (Discord::Config::rpc_in_use)
	{
		DiscordEventHandlers handlers;
		memset(&handlers, 0, sizeof(handlers));
		Discord_Initialize(Discord::Config::app_id, &handlers, 1, "0");
	}
	else
	{
		Discord_Shutdown();
	}
}

#pragma endregion

#pragma region Discord::UpdateDiscord

char* Discord::RPC_Config::state = "Karakter Yok";
char* Discord::RPC_Config::details = "RPC Baslatiliyor";
int64_t Discord::RPC_Config::startTimestamp = NULL;
int64_t Discord::RPC_Config::endTimestamp = NULL;
char* Discord::RPC_Config::largeImageKey = "";
char* Discord::RPC_Config::largeImageText = "";
int8_t Discord::RPC_Config::instance = 1;

void Discord::UpdateDiscord()
{
	static int64_t StartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	if (Discord::Config::rpc_in_use)
	{
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));

		discordPresence.state = Discord::RPC_Config::state;
		discordPresence.details = Discord::RPC_Config::details;

		Discord::RPC_Config::startTimestamp = StartTime;
		discordPresence.startTimestamp = Discord::RPC_Config::startTimestamp;

		discordPresence.endTimestamp = Discord::RPC_Config::endTimestamp;
		discordPresence.largeImageText = Discord::RPC_Config::largeImageText;
		discordPresence.largeImageKey = Discord::RPC_Config::largeImageKey;
		discordPresence.instance = Discord::RPC_Config::instance;

		Discord_UpdatePresence(&discordPresence);
	}
	else
	{
		Discord_ClearPresence();
	}
}

#pragma endregion

int Discord::DiscordRPC()
{
	if(Discord::Config::rpc_initized == false){
		Discord::Config::rpc_in_use = true;
		Discord::SetupDiscord();
		Discord::Config::rpc_initized = true;
	}

	Discord::UpdateDiscord();

	return getchar();
}