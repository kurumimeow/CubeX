#include <cstdint>

class Inventory
{
public:
	char pad_0000[236]; //0x0000
	int32_t health; //0x00EC
	int32_t armor; //0x00F0
	char pad_00F4[20]; //0x00F4
	int32_t pistol_round; //0x0108
	char pad_010C[12]; //0x010C
	int32_t gun_round; //0x0118
	char pad_011C[8]; //0x011C
	int32_t dpistol_round; //0x0124
	char pad_0128[4]; //0x0128
	int32_t pistol_ammo; //0x012C
	char pad_0130[12]; //0x0130
	int32_t gun_ammo; //0x013C
	char pad_0140[4]; //0x0140
	int32_t grenade; //0x0144
	int32_t dpistol_ammo; //0x0148
	char pad_014C[756]; //0x014C
}; //Size: 0x0440
static_assert(sizeof(Inventory) == 0x0440);

extern Inventory* g_inventory;
