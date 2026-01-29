#include "defs.h"

inherit SWCOURTBASE;

void
create_room()
{
    create_long();
    create_courtyard();

    add_exit(RUIN + "sw_court_e", "north");
    add_exit(RUIN + "sw_court_c", "northwest");
    add_exit(RUIN + "sw_court_s", "west");
    add_exit(RUIN + "s_tunnel_1", "east");
    add_exit(RUIN + "sw_court_stairs", "up");
}
