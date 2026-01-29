#include "defs.h"

inherit NECOURTBASE;

public void
create_room()
{
    create_long();
    create_courtyard();    

    add_exit(RUIN + "ne_court_c", "north");
    add_exit(RUIN + "ne_court_e", "northeast");
    add_exit(RUIN + "ne_court_se", "east");
    add_exit(RUIN + "ne_court_sw", "west");
    add_exit(RUIN + "ne_court_w", "northwest");
}
