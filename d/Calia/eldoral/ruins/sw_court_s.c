#include "defs.h"

inherit SWCOURTBASE;

void
create_room()
{
    create_long();
    create_courtyard();

    add_exit(RUIN + "sw_court_c", "north");
    add_exit(RUIN + "sw_court_e", "northeast");
    add_exit(RUIN + "sw_court_se", "east");
    add_exit(RUIN + "sw_court_sw", "west");
    add_exit(RUIN + "sw_court_w", "northwest");
}
