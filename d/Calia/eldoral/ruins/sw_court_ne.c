#include "defs.h"

inherit SWCOURTBASE;

void
create_room()
{
    create_long();
    create_courtyard();

    add_exit(RUIN + "sw_court_n", "west");
    add_exit(RUIN + "sw_court_e", "south");
    add_exit(RUIN + "sw_court_c", "southwest");
}
