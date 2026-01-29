/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c06", "northwest");
    add_exit(ROOMS_DIR + "c04", "northeast");
	add_exit(ROOMS_DIR + "c08", "southwest");
}
