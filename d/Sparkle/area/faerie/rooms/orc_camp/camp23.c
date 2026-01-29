/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "A tall tower stands north of here.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    reset_room();

    set_short("South of a tall tower");
    set_long(camp_desc1(extra_line));

    add_item(({"tall tower"}),
        "The tall tower rises in the center of the tent. It is taller than any other tower and dominates the camp.\n");

    add_exit(OC_DIR + "undert", "north");
    add_exit(OC_DIR + "camp19", "northwest");
    add_exit(OC_DIR + "camp27", "southeast");
}


public void
init()
{
    ::init();

}
void
reset_room()
{
    create_orcs(ORC_SCOUT, WANDER);
}
