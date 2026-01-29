#include "defs.h"

inherit SWCOURTBASE;

void
create_room()
{
    create_long();
    create_courtyard();

    add_exit(RUIN + "sw_court_nw", "north");
    add_exit(RUIN + "sw_court_n", "northeast");
    add_exit(RUIN + "sw_court_c", "east");
    add_exit(RUIN + "sw_court_s", "southeast");
    add_exit(RUIN + "sw_court_sw", "south");
}
