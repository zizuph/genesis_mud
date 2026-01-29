/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c31", "north");
    add_exit(ROOMS_DIR + "c40", "south","@@climb_down@@");

}
