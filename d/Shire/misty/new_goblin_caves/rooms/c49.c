/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
	add_exit(ROOMS_DIR + "c48", "southeast");
	add_exit(ROOMS_DIR + "shop", "northeast");
	add_exit(ROOMS_DIR + "c51", "southwest");

}
