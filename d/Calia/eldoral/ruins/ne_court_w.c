#include "defs.h"

inherit NECOURTBASE;

public void
create_room()
{
    create_long();
    create_courtyard();    

    add_exit(RUIN + "ne_court_nw", "north");
    add_exit(RUIN + "ne_court_n", "northeast");
    add_exit(RUIN + "ne_court_c", "east");
    add_exit(RUIN + "ne_court_s", "southeast");
    add_exit(RUIN + "ne_court_sw", "south");
}
