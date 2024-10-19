#include "register.h"
#include"rpc.h"
#include <chrono>
#include "Handler.h"
#include "invoker/Natives.hpp"
#include "Self.h"
#pragma comment(lib, "discord-rpc.lib")

discordhandler g_Discord;

void discordhandler::Init() {
    DiscordEventHandlers handlers;
    std::memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize("1200814010866606080", &handlers, 1, "0");
}

void discordhandler::Tick() {


    DiscordRichPresence discordPresence;
    std::memset(&discordPresence, 0, sizeof(discordPresence));

    discordPresence.largeImageKey = "copie_de_v";
    discordPresence.smallImageKey = "gta";
    discordPresence.smallImageText = "V1.0.2";
    discordPresence.largeImageText = "sans_titre83";
    discordPresence.details = "Virtual Engine Service";
    if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
        discordPresence.state = "Playing in online";
    }
    else {
        discordPresence.state = "Playing in story mode";
    }
    discordPresence.instance = 1;
    Discord_UpdatePresence(&discordPresence);
}

void discordhandler::Shutdown() {
    Discord_ClearPresence();
    Discord_Shutdown();
}
void discordhandler::DiscordInstructional()
{
    if (GetAsyncKeyState(VK_F7) & 1)
    {
        DiscordInstruct();
    }
}

discordhandler* GetDiscord() { return &g_Discord; }