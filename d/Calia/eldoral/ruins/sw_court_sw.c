#include "defs.h"

inherit SWCOURTBASE;

void
create_room()
{
    create_long();
    create_courtyard();

    add_exit(RUIN + "sw_court_w", "north");
    add_exit(RUIN + "sw_court_c", "northeast");
    add_exit(RUIN + "sw_court_s", "east");
    add_exit(RUIN + "in_south_arch", "south");
}
