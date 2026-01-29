/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c176", "north");
	add_exit(ROOMS_DIR + "c174", "east");
	add_exit(ROOMS_DIR + "c171", "southwest");
	add_exit(ROOMS_DIR + "c172", "west");
	add_exit(ROOMS_DIR + "c177", "northwest");

}
