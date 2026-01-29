/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "A tall tower stands to the south.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    reset_room();
    set_add_tower();
    set_short("North of a tall tower");
    set_long(camp_desc4(extra_line));

    add_item(({"tall tower"}),
        "The tall tower rises in the center of the tent. It is taller than any other tower and dominates the camp.\n");
    add_exit(OC_DIR + "camp10", "north");
    add_exit(OC_DIR + "undert", "south");
    add_exit(OC_DIR + "camp16", "east");
    add_exit(OC_DIR + "camp14", "west");
}


public void
init()
{
    ::init();

}
void
reset_room()
{
    create_orcs(ORC_SOLDIER, WANDER);
}
