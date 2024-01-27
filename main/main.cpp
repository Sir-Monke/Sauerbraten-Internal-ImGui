#include "main.h"

bool bIsVisible = true;
//Player
bool bAimbot = false, bNoRecoil = false, bRapidFire = false, bFovBigBig = false, bGodMode = false, bInfiAmmo = false, bNoBulletSpread = false;
//World
bool bForceItems = false;

void MainHack() {
    if (GetAsyncKeyState(VK_F4) & 1) {
        bIsVisible = !bIsVisible;
    }
    if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
        bAimbot = !bAimbot;
    }
    if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
        bGodMode = !bGodMode;
    }
    if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
        bNoRecoil = !bNoRecoil;
    }
    if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
        bRapidFire = !bRapidFire;
    }
    if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
        bInfiAmmo = !bInfiAmmo;
    }
    if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
        bNoBulletSpread = !bNoBulletSpread;
    }
    if (GetAsyncKeyState(VK_NUMPAD7) & 1) {
        bFovBigBig = !bFovBigBig;
    }
    if (GetAsyncKeyState(VK_NUMPAD8) & 1) {
        bForceItems = !bForceItems;
    }

    //  Player
    //GodMode
    if (bGodMode) {
        GodMode(true);
    } else {
        GodMode(false);
    }
    //Fov Big Big
    if (bFovBigBig) {
        SetFov(160);
    } else {
        SetFov(100);
    }
    //Rapid Fire
    if (bRapidFire) {
        RapidFire(true);
    } else {
        RapidFire(false);
    }
    //No Recoil
    if (bNoRecoil) {
        NoRecoil(true);
    } else {
        NoRecoil(false);
    }
    //Aimbot
    if (bAimbot) {
        Aimbot();
    }
    //Infi Ammo
    if (bInfiAmmo) {
        InfAmmo(true);
    } else {
        InfAmmo(false);
    }
    //Bullet Spread
    if (bNoBulletSpread) {
        NoBulletSpead(true);
    } else {
        NoBulletSpead(false);
    }

    //  World
    //Spawn Items
    if (bForceItems) {
        ForceSpawnItems(true);
    } else {
        ForceSpawnItems(false);
    }
}

void TextCentered(std::string text) {
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth = ImGui::CalcTextSize(text.c_str()).x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text(text.c_str());
}

void RenderMenu() {
    ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    if (bIsVisible) {
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(500, 275));
        ImGui::Begin("Big Booty Bitches", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        
        //Title
        TextCentered("Memory MNKE 2.0");

        //Info
        ImGui::Separator();
        TextCentered("[F4] To Toggle - [Num 0] To Quit");

        // Left Window Player Cheats
        ImGui::BeginChild("Left", ImVec2(ImGui::GetWindowSize().x / 2, 200), true);
        TextCentered("Player Cheats");
        ImGui::Separator();
        ImGui::Checkbox("Aimbot      [Num 1]", &bAimbot);
        ImGui::Checkbox("Godmode     [Num 2]", &bGodMode);
        ImGui::Checkbox("NoRecoil    [Num 3]", &bNoRecoil);
        ImGui::Checkbox("Rapid Fire  [Num 4]", &bRapidFire);
        ImGui::Checkbox("Infi Ammo   [Num 5]", &bInfiAmmo);
        ImGui::Checkbox("Spread      [Num 6]", &bNoBulletSpread);
        ImGui::Checkbox("Big Big FOV [Num 7]", &bFovBigBig);
        ImGui::EndChild();

        // Right Window World/Other Cheats
        ImGui::SameLine();
        ImGui::BeginChild("Right", ImVec2(ImGui::GetWindowSize().x / 2 - 24, 100), true);
        TextCentered("World/Other Cheats");
        ImGui::Separator();
        ImGui::Checkbox("Spawn Items [Num 8]", &bForceItems);
        ImGui::EndChild();

        //About
        ImGui::Separator();
        TextCentered("Made By Professional Acustic KanyeEast#3965");

        ImGui::End();
    }
}