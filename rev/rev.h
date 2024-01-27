#pragma once
#include "../utils/helper.h"

//GameFunctions
typedef __int64(_cdecl* _HudPlayer)(); // returns - LocalPlayer
typedef __int64(_cdecl* _GetClient)(int id); // returns - LocalPlayer / Ents
typedef void(_cdecl* _SpawnItems)(bool force); // respawns items on map
typedef void(_cdecl* _DoAttack)(bool toggle); // forces local player to shoot / attack
typedef void(_cdecl* _DoDamage)(int damage, __int64 target, __int64 actor, bool local); // applys damage to a player max 100 - may have to run more than once (armor). Must call respawn for all killed ents after
typedef void(_cdecl* _Quit)(); // safely exits the game 

//Player and Ent Structs and Weapon Stuff

class PlrClass {
public:
	Vector3 pos1;
	float VelocityX;
	float VelocityZ;
	float VelocityY;
	float FrictionX;
	float FrictionZ;
	float FrictionY;
	char unknown1[0xC];
	Vector3 pos2;
	Vector2 viewAngles;
	char unknown2[0x4];
	int PlayerSpeed;
	char unknown3[0x4];
	int PlayerCamOffset;
	char unknown4[0x12C];
	int PlayerHealth;
	char unknown5[0x4];
	int PlayerShield;
	int TypeOfShield;
	int QuadDamageEventTime;
	int CurrentGun;
	int GunFireRate;
	int ChainSawAmmo;
	int ShotgunAmmo;
	int MiniGunAmmo;
	int LauncherAmmo;
	int RifleAmmo;
	int GrenadeLauncherAmmo;
	int PistolAmmo;
	char unknown6[0x1D];
	int PlayerState;
	char unknown7[0x28];
	int isPlayerShooting;
	char unknown8[0x72];
	int PlayerNameHolder;
};

class EntClass {
public:
	Vector3 pos1; //0x0000
	float VelocityZ; //0x000C
	float FrictionX; //0x0010
	float FrictionY; //0x0014
	char pad_0018[24]; //0x0018
	Vector3 pos2; //0x0030
	Vector2 viewAngles; //0x003C
	char pad_0044[4]; //0x0044
	float EntSpeed; //0x0048
	char pad_004C[308]; //0x004C
	int32_t Health; //0x0180
	char pad_0184[4]; //0x0184
	int32_t Sheild; //0x0188
	int32_t SheildType; //0x018C
	int32_t QuadDamageTime; //0x0190
	int32_t CurrentGun; //0x0194
	char pad_0198[4]; //0x0198
	int32_t ChainsawAmmo; //0x019C
	int32_t ShotgunAmmo; //0x01A0
	int32_t MinigunAmmo; //0x01A4
	int32_t LanucherAmmo; //0x01A8
	int32_t RifleAmmo; //0x01AC
	int32_t GrenadeLauncherAmmo; //0x01B0
	int32_t PistolAmmo; //0x01B4
	char pad_01B8[196]; //0x01B8
	char Name[15]; //0x027C
};

class EntPlrList {
public:
	class PlrClass* LocalPlayer; //0x0000
	class EntClass* Ent1; //0x0008
};

class PlayerList {
public:
	char pad_0000[24]; //0x0000
	class EntPlrList* PlayerList; //0x0018
};

enum Guns { // taken from game source
	GUN_FIST = 0,
	GUN_SG,
	GUN_CG,
	GUN_RL,
	GUN_RIFLE,
	GUN_GL,
	GUN_PISTOL,
	GUN_FIREBALL,
	GUN_ICEBALL,
	GUN_SLIMEBALL,
	GUN_BITE,
	GUN_BARREL,
	NUMGUNS
};

enum gameModes {
	SINGLEPLAYERMODE2 = -3,
	SINGLEPLAYERMODE1 = -2,
	DEMOPLAYBACKMODE = -1,
	FFA = 0,
	COOP,
	TEAM,
	INSTAKILL,
	INSTAKILLTEAM,
	NOITEMS,
	NOITEMSTEAM,
	RANDOMGUNS,
	RANDOMGUNSTEAM,
	CAPTUREPOINT,
	CAPTUREPOINTREGEN,
	CAPTURETHEFLAG,
	NORMALCAPTUREFLAG,
	PROTECTFLAG,
	INSTAPROTECTFLAG,
	HOLDFLAG,
	INSTAHOLDFLAG,
	ECAPTURETHEFLAG,
	EPROTECTFLAG,
	EHOLDFLAG,
	COLLECTDEATHS,
	INSTACOLLECTDEATHS,
	ECOLLECTDEATHS,
};