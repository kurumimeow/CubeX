#include <cstdint>

struct Vector3 {
	float x;
	float y;
	float z;
};

class Player
{
public:
	void* vtable;
	Vector3 N00000050; //0x0004
	Vector3 velocity; //0x0010
	Vector3 N00000052; //0x001C
	Vector3 pos; //0x0028
	float yaw; //0x0034
	float pitch; //0x0038
	float roll; //0x003C
	char pad_0040[236]; //0x0040
}; //Size: 0x012C
static_assert(sizeof(Player) == 0x012C);

extern Player* g_localPlayer;
