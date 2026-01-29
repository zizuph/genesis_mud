/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c131", "north");
	add_exit(ROOMS_DIR + "c115", "west");
	add_exit(ROOMS_DIR + "c129", "south");

}
