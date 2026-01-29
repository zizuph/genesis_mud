#include "defs.h"

inherit NECOURTBASE;

public void
create_room()
{
    create_long();
    create_courtyard();    

    add_exit(RUIN + "ne_court_n", "east");
    add_exit(RUIN + "ne_court_c", "southeast");
    add_exit(RUIN + "ne_court_w", "south");
    add_exit(RUIN + "n_tunnel_1", "west");
}
