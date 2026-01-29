/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c182", "north");
	add_exit(ROOMS_DIR + "c174", "southeast");
	add_exit(ROOMS_DIR + "c173", "south");
	add_exit(ROOMS_DIR + "c172", "southwest");
	add_exit(ROOMS_DIR + "c175", "east");
	add_exit(ROOMS_DIR + "c177", "west");
	add_exit(ROOMS_DIR + "c181", "northwest");

}
