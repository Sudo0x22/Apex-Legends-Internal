#pragma once
#include<cstdint>
#include "recv_table.hpp"
struct HighlightFuncBits
{
	uint8_t funcbits[4];
};
struct HighlightParam
{
	float param[3];
};
struct HighlightMode
{
	uint8_t func[4];
};
struct PlayerInfo_t
{
	const char* player_name;
	int current_health;
	void* player_addr;
	size_t player_size;
};

struct Bone_t
{
	uint8_t pad1[0xCC];
	float x;
	uint8_t pad2[0xC];
	float y;
	uint8_t pad3[0xC];
	float z;
};

struct Matrix_t
{
	float matrix[16];
};

class ClientClass_t
{
public:
	const char* GetName() { return m_pNetworkName; }
public:
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass_t* m_pNext;
};
