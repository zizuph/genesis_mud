/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c18", "east");
	add_exit(ROOMS_DIR + "c16", "southwest");

}
