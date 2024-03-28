#pragma once
#include"offsets/offsets.hpp"
#include"globals/globals.hpp"
#include<random>
struct MyStr32 { char readstr[16]; };
struct MyStr64 { char readstr[32]; };
#define SCREEN_W 1920
#define SCREEN_H 1080
namespace utils
{
	template<typename Type>
	__inline Type Read(uintptr_t addr)
	{
		Type buffer{};
		return *(Type*)(addr);
	}
	std::string ReadString64(uint64_t addr)
	{
		std::string result = Read<MyStr64>(addr).readstr;
		return result;
	}
	std::string ReadString32(uintptr_t addr)
	{
		std::string result = Read<MyStr32>(addr).readstr;
		return result;
	}
	void ReadStringEx(uintptr_t addr, char* buffer, size_t size)
	{
		MyStr64 data = Read<MyStr64>(addr);
		strncpy(buffer, data.readstr, size);
		buffer[size - 1] = '\0';
	}
	int  RandIntSimple(int min, int max)
	{
		std::random_device randomDevice; std::mt19937 gen(randomDevice()); std::uniform_int_distribution<> dist(min, max);
		return dist(gen);
	}
	float MapFloat(float x, float in_min, float in_max, float out_min, float out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_min - in_min) + out_max;
	}

	inline float sqrtf_(float x)
	{
		union { float f; uint32_t i; } z = { x };
		z.i = 0x5f3759df - (z.i >> 1);
		z.f *= (1.5f - (x * 0.5f * z.f * z.f));
		z.i = 0x7EEEEEEE - z.i;
		return z.f;
	}

	double powf_(double x, int y)
	{
		double temp;
		if (y == 0)
			return 1;
		temp = powf_(x, y / 2);
		if ((y % 2) == 0) {
			return temp * temp;
		}
		else {
			if (y > 0)
				return x * temp * temp;
			else
				return (temp * temp) / x;
		}
	}
	double GetCrossDistance(double x1, double y1, double x2, double y2)
	{
		return sqrtf_(powf_((float)(x1 - x2), (float)2) + powf_((float)(y1 - y2), (float)2));
	}
}