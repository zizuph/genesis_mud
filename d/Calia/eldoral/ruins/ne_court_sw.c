#include "defs.h"

inherit NECOURTBASE;

public void
create_room()
{
    create_long();
    create_courtyard();    

    add_exit(RUIN + "ne_court_w", "north");
    add_exit(RUIN + "ne_court_c", "northeast");
    add_exit(RUIN + "ne_court_s", "east");
    add_exit(RUIN + "ne_court_stairs", "up");
}
