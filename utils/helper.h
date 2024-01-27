#pragma once
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>
#include <math.h>

struct FunctionAddrs {
	DWORD HudPlayerAddr;
	DWORD GetClientAddr;
	DWORD SpawnItems;
	DWORD SwitchPlayerModel;
	DWORD DoAttack;
	DWORD DoDamage;
	DWORD Quit;
};

void WriteToMemory(uintptr_t addressToWrite, char* valueToWrite, int byteNum);
void NopBytesToggle(uintptr_t addr, const std::vector<unsigned char>& oriBytes, size_t size, bool restore);
uintptr_t GetModBaseAddr();
FunctionAddrs FindAllPatterns();
uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);


struct Vector2 { float x, y; };
class Vector3 {
public:
	float x, y, z;
	Vector3() {};
	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
	Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
	Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
	Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float Length() const { return sqrtf(x * x + y * y + z * z); }
	Vector3 Normalize() const { return *this * (1 / Length()); }
	float Distance(const Vector3& o) { Vector3 self(this->x, this->y, this->z); Vector3 diff = self - o; return sqrt((diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z)); }
};

struct Vector4 {
	float x, y, z, w;
};