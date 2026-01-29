/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c180", "north");
	add_exit(ROOMS_DIR + "c172", "southeast");
	add_exit(ROOMS_DIR + "c177", "east");
	add_exit(ROOMS_DIR + "c179", "southwest");

}
