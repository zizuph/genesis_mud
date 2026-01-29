/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c106", "north");
    add_exit(ROOMS_DIR + "c105", "northwest");
	add_exit(ROOMS_DIR + "c107", "northeast");
	add_exit(ROOMS_DIR + "c108", "west");
	add_exit(ROOMS_DIR + "c110", "southwest");
	add_exit(ROOMS_DIR + "c112", "southeast");
}
