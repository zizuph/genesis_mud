/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c175", "southeast");
	add_exit(ROOMS_DIR + "c176", "south");
	add_exit(ROOMS_DIR + "c177", "southwest");
	add_exit(ROOMS_DIR + "c183", "northwest");

}
