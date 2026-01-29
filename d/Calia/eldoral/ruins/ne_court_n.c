#include "defs.h"

inherit NECOURTBASE;

public void
create_room()
{
    create_long();
    create_courtyard();    

    add_exit(RUIN + "ne_court_ne", "east");
    add_exit(RUIN + "ne_court_e", "southeast");
    add_exit(RUIN + "ne_court_c", "south");
    add_exit(RUIN + "ne_court_w", "southwest");
    add_exit(RUIN + "ne_court_nw", "west");
}
