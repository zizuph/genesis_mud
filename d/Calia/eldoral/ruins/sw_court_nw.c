#include "defs.h"

inherit SWCOURTBASE;

void
create_room()
{
    create_long();
    create_courtyard();

    add_exit(RUIN + "w_tunnel_1", "north");
    add_exit(RUIN + "sw_court_n", "east");
    add_exit(RUIN + "sw_court_c", "southeast");
    add_exit(RUIN + "sw_court_w", "south");
}
