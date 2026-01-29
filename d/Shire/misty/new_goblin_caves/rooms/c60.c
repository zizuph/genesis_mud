/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
	add_exit(ROOMS_DIR + "c52", "northwest");
	add_exit(ROOMS_DIR + "c61", "south");
	add_exit(ROOMS_DIR + "c74", "southeast");
}
