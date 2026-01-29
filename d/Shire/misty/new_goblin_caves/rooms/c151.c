/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c149", "north");
	add_exit(ROOMS_DIR + "c150", "west");
	add_exit(ROOMS_DIR + "c152", "southwest");

}
