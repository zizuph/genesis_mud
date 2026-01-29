/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c01", "north");
    add_exit(ROOMS_DIR + "c03", "west");
	add_exit(ROOMS_DIR + "c11", "southeast");
	add_exit(ROOMS_DIR + "c10", "south");
}
