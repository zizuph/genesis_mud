/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c183", "northeast");
	add_exit(ROOMS_DIR + "c177", "southeast");
	add_exit(ROOMS_DIR + "c178", "south");

}
