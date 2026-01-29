/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
	add_exit(ROOMS_DIR + "c66", "north");
	add_exit(ROOMS_DIR + "c68", "east");
	add_exit(ROOMS_DIR + "c104", "south","@@climb_down@@");
}
