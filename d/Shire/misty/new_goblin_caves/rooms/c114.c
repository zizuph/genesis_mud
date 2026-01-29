/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c110", "northwest");
	add_exit(ROOMS_DIR + "c111", "north");
	add_exit(ROOMS_DIR + "c113", "west");
	add_exit(ROOMS_DIR + "c196", "east");
}
