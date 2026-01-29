/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c114", "west");
	add_exit(ROOMS_DIR + "c197", "southeast");

}
