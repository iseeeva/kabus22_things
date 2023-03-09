#pragma once

#include <stdint.h>

class Discord {

public:

	static int DiscordRPC();
	static void SetupDiscord();
	static void UpdateDiscord();

	class Config {
	public:
		static char* app_id;
		static bool rpc_in_use;
		static bool rpc_initized;
	};

	class RPC_Config {
	public:
		static char* state;
		static char* details;
		static int64_t startTimestamp;
		static int64_t endTimestamp;
		static char* largeImageKey;
		static char* largeImageText;
		static int8_t instance;
	};

};