/*
 * The orchard of the NMG
 * By Finwe, February 2006
 */

#include "defs.h"

inherit ORCHARD_BASE;

string extra_line = "They look large and ready to eat.";

void
create_orchard_room()
{
    set_short("An orchard in the mountains");
    set_long(orch_descr3(extra_line));

    set_add_mountain();
    add_std_herbs("forest");
    reset_room();

    add_exit(CAVE_DIR + "orch05", "south");
    add_exit(CAVE_DIR + "orch03", "east");

}

public void
init()
{
    ::init();
}

void
reset_room()
{
    set_searched(0);
}
