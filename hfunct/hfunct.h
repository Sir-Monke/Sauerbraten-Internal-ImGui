#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "../rev/rev.h"
#include "../utils/helper.h"

#define M_PI 3.14159265358979323846

//Player
void KillAllPlayers();
void Aimbot();
void NoRecoil(bool toggle);
void NoBulletSpead(bool toggle);
void RapidFire(bool toggle);
void InfAmmo(bool toggle);
void GodMode(bool toggle);
void SetFov(int newFOV);
//Map
void ForceSpawnItems(bool toggle);
//Game
//Ents
//Other
void QuitGame();