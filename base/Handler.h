#pragma once
#include "register.h"
#include "rpc.h"
#include "common.hpp"


class discordhandler {
public:
    void Init();
    void Tick();
    void Shutdown();
    void DiscordInstructional();
};

discordhandler* GetDiscord();
