/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c177", "north");
	add_exit(ROOMS_DIR + "c176", "northeast");
	add_exit(ROOMS_DIR + "c173", "east");
	add_exit(ROOMS_DIR + "c178", "northwest");

}
