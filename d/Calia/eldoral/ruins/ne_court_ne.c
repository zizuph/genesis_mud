#include "defs.h"

inherit NECOURTBASE;

public void
create_room()
{
    create_long();
    create_courtyard();

    add_exit(RUIN + "in_north_arch", "north");
    add_exit(RUIN + "ne_court_e", "south");
    add_exit(RUIN + "ne_court_c", "southwest");
    add_exit(RUIN + "ne_court_n", "west");
}
 