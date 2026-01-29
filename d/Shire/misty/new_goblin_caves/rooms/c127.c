/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c125", "west");
	add_exit(ROOMS_DIR + "c128", "north");
	add_exit(ROOMS_DIR + "c139", "east");
	
}
