#include "defs.h"

inherit SWCOURTBASE;

void
create_room()
{
    create_long();
    create_courtyard();

    add_exit(RUIN + "sw_court_ne", "north");
    add_exit(RUIN + "sw_court_se", "south");
    add_exit(RUIN + "sw_court_s", "southwest");
    add_exit(RUIN + "sw_court_c", "west");
    add_exit(RUIN + "sw_court_n", "northwest");
}
