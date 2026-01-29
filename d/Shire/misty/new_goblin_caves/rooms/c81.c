/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
	add_exit(ROOMS_DIR + "c80", "south");
	add_exit(ROOMS_DIR + "c82", "southeast");
}
