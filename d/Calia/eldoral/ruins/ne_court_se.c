#include "defs.h"

inherit NECOURTBASE;

public void
create_room()
{
    create_long();
    create_courtyard();

    add_exit(RUIN + "ne_court_e", "north");
    add_exit(RUIN + "e_tunnel_1", "south");
    add_exit(RUIN + "ne_court_s", "west");
    add_exit(RUIN + "ne_court_c", "northwest");
}
