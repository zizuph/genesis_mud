/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "There is a tall tower to the east.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    reset_room();
    
    set_short("West of a tall tower");

    add_item(({"tall tower"}),
        "The tall tower rises in the center of the tent. It is taller than any other tower and dominates the camp.\n");

    set_long(camp_desc5(extra_line));

    add_exit(OC_DIR + "camp14", "north");
    add_exit(OC_DIR + "undert", "east");
    add_exit(OC_DIR + "camp18", "west");
    add_exit(OC_DIR + "camp23", "southeast");
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
