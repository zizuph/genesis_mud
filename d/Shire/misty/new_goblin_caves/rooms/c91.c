/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
	add_exit(ROOMS_DIR + "c90", "northeast");
	add_exit(ROOMS_DIR + "c92", "northwest");
}
