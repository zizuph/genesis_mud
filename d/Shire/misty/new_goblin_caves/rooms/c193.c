/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c192", "north");
	add_exit(ROOMS_DIR + "c194", "west");
	add_exit(ROOMS_DIR + "c161", "northwest");


}
