/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c185", "northwest");
	add_exit(ROOMS_DIR + "c187", "southeast");
	add_exit(ROOMS_DIR + "c136", "west");


}
