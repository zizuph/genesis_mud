/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{

	add_exit(ROOMS_DIR + "c44", "north");
	add_exit(ROOMS_DIR + "c53", "southwest");
	add_exit(ROOMS_DIR + "c60", "southeast");
}
