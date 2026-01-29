/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c67", "north","@@climb_up@@");
    add_exit(ROOMS_DIR + "c105", "south");
}
