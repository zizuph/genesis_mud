/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    reset_room();

    set_short("Near the center of the camp");
    set_long(camp_desc3(extra_line));

    add_item(({"tall tower"}),
        "The tall tower rises in the center of the tent. It is taller than any other tower and dominates the camp.\n");

    add_exit(OC_DIR + "camp09", "north");
    add_exit(OC_DIR + "camp19", "south");
    add_exit(OC_DIR + "camp15", "east");
    add_exit(OC_DIR + "camp13", "west");
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
