/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c17", "northeast");
	add_exit(ROOMS_DIR + "c21", "south");
	add_exit(ROOMS_DIR + "c14", "northwest");

}
