#include "HFunct.h"

using namespace std;

// Classes
PlayerList* playerList = NULL;

// Main Vars
uintptr_t ModuleBaseAddr = GetModBaseAddr();

// Function Decl
_GetClient getClient;
_HudPlayer hudPlayer;
_DoDamage doDamage;
_DoAttack doAttack;
_Quit quit;
_SpawnItems spawnItems;

FunctionAddrs functions = FindAllPatterns();

void NoRecoil(bool toggle) {
    uintptr_t addr = ModuleBaseAddr + 0xCB9F2;
    size_t size = 1;
    std::vector<unsigned char> oriBytes = { 0x49, 0x63, 0x84, 0x24, 0x94, 0x01, 0x00, 0x00 };
    NopBytesToggle(addr, oriBytes, size, toggle);
}

void NoBulletSpead(bool toggle) { // NOT FOR SHOTGUN RN
    uintptr_t addr = ModuleBaseAddr + 0xCBB47;
    size_t size = 1;
    std::vector<unsigned char> oriBytes = { 0x45, 0x8B, 0x44, 0xD5, 0x0C };
    NopBytesToggle(addr, oriBytes, size, toggle);
}

void InfAmmo(bool toggle) {
    playerList = (PlayerList*)(ModuleBaseAddr + 0x324990);
    if (toggle) {
        playerList->PlayerList->LocalPlayer->ChainSawAmmo = 100;
        playerList->PlayerList->LocalPlayer->GrenadeLauncherAmmo = 100;
        playerList->PlayerList->LocalPlayer->LauncherAmmo = 100;
        playerList->PlayerList->LocalPlayer->MiniGunAmmo = 100;
        playerList->PlayerList->LocalPlayer->PistolAmmo = 100;
        playerList->PlayerList->LocalPlayer->RifleAmmo = 100;
        playerList->PlayerList->LocalPlayer->ShotgunAmmo = 100;
    }
}

void RapidFire(bool toggle) {
    playerList = (PlayerList*)(ModuleBaseAddr + 0x324990);
    if (toggle) {
        playerList->PlayerList->LocalPlayer->GunFireRate = 50;
    }
}

void GodMode(bool toggle) { // no work :( cant even code a godmode :(
    //int plrState = playerList->PlayerList->LocalPlayer->PlayerState;
    if (toggle) {
        //if (plrState != 4294967295) {
        //    playerList->PlayerList->LocalPlayer->PlayerState = 1;
        //}
        playerList->PlayerList->LocalPlayer->PlayerHealth = 80085;
    }
    else {
        //playerList->PlayerList->LocalPlayer->PlayerState = 0;
    }
}

void SetFov(int newFOV) {
    *(int*)(ModuleBaseAddr + 0x31E794) = newFOV;
}

EntClass* GetEnt(int id) {
    PlayerList* playerList = (PlayerList*)(ModuleBaseAddr + 0x324990);
    uintptr_t entList = (uintptr_t)(playerList->PlayerList);
    if (id != 0) {
        return (EntClass*)*(uintptr_t*)(entList + (id * 8)); //ent offset 8
    }
    return nullptr;
}

EntClass* GetClosestEnemy() {
    PlayerList* playerList = (PlayerList*)(ModuleBaseAddr + 0x324990);
    int gameMode = *(int*)(ModuleBaseAddr + 0x297E84);
    int playerCount = *(int*)(ModuleBaseAddr + 0x324F74);
    int botCount = *(int*)(ModuleBaseAddr + 0x324F74) - 1;

    int index = 1;
    float distance = 100000;

    if (botCount != 0) {
        if (gameMode == FFA) {
            for (int i = 0; i < playerCount; i++) {
                EntClass* ent = GetEnt(i);
                if (i == 0) {
                    continue;
                }
                if (!ent) {
                    continue;
                }
                if (ent->Health < 0) {
                    continue;
                }
                if (playerList->PlayerList->LocalPlayer->pos1.Distance(ent->pos1) < distance) {
                    distance = playerList->PlayerList->LocalPlayer->pos1.Distance(ent->pos1);
                    index = i;
                }
            }
        }
    }
    else {
        return nullptr;
    }
    return GetEnt(index);
}

void Aimbot() {
    playerList = (PlayerList*)(ModuleBaseAddr + 0x324990);
    EntClass* target = GetClosestEnemy();
    if (target != nullptr) {
        Vector3 src = playerList->PlayerList->LocalPlayer->pos1;
        Vector3 dst = target->pos1;

        float yaw = -atan2f(dst.x - src.x, dst.y - src.y) / (float)M_PI * 180;
        float pitch = asinf((dst.z - src.z) / src.Distance(dst)) * 180 / (float)M_PI;

        playerList->PlayerList->LocalPlayer->viewAngles.x = yaw;
        playerList->PlayerList->LocalPlayer->viewAngles.y = pitch;
        Sleep(5);
    }
}

__int64 GetLocalPlayer() {
    hudPlayer = (_HudPlayer)(ModuleBaseAddr + functions.HudPlayerAddr);
    __int64 localPlr = hudPlayer();
    return localPlr;
}

void ForceSpawnItems(bool toggle) {
    spawnItems = (_SpawnItems)(ModuleBaseAddr + functions.SpawnItems);
    if (toggle) {
        spawnItems(true);
    } else {
        spawnItems(false);
    }
}

void QuitGame() {
    quit = (_Quit)(ModuleBaseAddr + functions.Quit);
    quit();
}

void ForceAttack(bool toggle) {
    doAttack = (_DoAttack)(ModuleBaseAddr + functions.DoAttack);
    doAttack(toggle);
}

void KillAllPlayers() { // need to respawn after killing
    doDamage = (_DoDamage)(ModuleBaseAddr + functions.DoDamage);
    getClient = (_GetClient)(ModuleBaseAddr + functions.GetClientAddr);
    int playerCount = *(int*)(ModuleBaseAddr + 0x324F74);
    __int64 localplr = GetLocalPlayer();
    for (int i = 0; i < playerCount; i++) {
        EntClass* ent = GetEnt(i);
        if (ent != NULL) {
            doDamage(100, i, localplr, true);
        }
    }
}