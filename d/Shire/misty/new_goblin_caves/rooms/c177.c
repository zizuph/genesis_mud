/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c181", "north");
	add_exit(ROOMS_DIR + "c173", "southeast");
	add_exit(ROOMS_DIR + "c172", "south");
	add_exit(ROOMS_DIR + "c182", "northeast");
	add_exit(ROOMS_DIR + "c176", "east");
	add_exit(ROOMS_DIR + "c178", "west");
	add_exit(ROOMS_DIR + "c180", "northwest");

}
