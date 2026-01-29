/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c116", "north");
	add_exit(ROOMS_DIR + "c117", "west");
	add_exit(ROOMS_DIR + "c119", "east");

}
