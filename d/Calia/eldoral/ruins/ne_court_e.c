#include "defs.h"

inherit NECOURTBASE;

public void
create_room()
{
    create_long();
    create_courtyard();

    add_exit(RUIN + "ne_court_ne", "north");
    add_exit(RUIN + "ne_court_se", "south");
    add_exit(RUIN + "ne_court_s", "southwest");
    add_exit(RUIN + "ne_court_c", "west");
    add_exit(RUIN + "ne_court_n", "northwest");
}