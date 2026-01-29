/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c169", "south");
	add_exit(ROOMS_DIR + "c171", "east");
	add_exit(ROOMS_DIR + "c172", "northeast");

}
