#include "defs.h"

inherit SWCOURTBASE;

public void
create_pillars()
{
    int i;

    for (i = 0; i < 12; i++)
        clone_object(OBJ + "pillar")->move(TO);
}

public void
create_room()
{
    set_long("You are at the heart of a courtyard in " +
        "the ruins of " + VBFC_ME("castle_name") + ", " +
        "amidst a series of " +
        "obelisks standing at several points of a " +
        "pattern of concentric circles laid in " +
        "blocks of black stone on the grey ground of " +
        "the courtyard. " +
        "Walls surround the courtyard on all sides, " +
        "and several means of entrance are apparent; " +
        "an archway leads out into the forest to the " +
        "southwest, in the northwest and southeast " +
        "corners tunnels delve beneath the ruins, " +
        "and a stairway ascends the east wall. " +
        "To the general northeast rises a " +
        "series of crumbling towers, walls and " +
        "ramparts that comprise the inner castle.\n\n");
    
    create_courtyard();
    create_pillars();

    add_exit(RUIN + "sw_court_n", "north");
    add_exit(RUIN + "sw_court_ne", "northeast");
    add_exit(RUIN + "sw_court_e", "east");
    add_exit(RUIN + "sw_court_se", "southeast");
    add_exit(RUIN + "sw_court_s", "south");
    add_exit(RUIN + "sw_court_sw", "southwest");
    add_exit(RUIN + "sw_court_w", "west");
    add_exit(RUIN + "sw_court_nw", "northwest");
}
