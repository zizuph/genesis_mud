#include "defs.h"

inherit NECOURTBASE;

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
    set_long("Here in the center of the northeast courtyard of " +
        VBFC_ME("castle_name") + 
        ", a series of obelisks stand at several points of " +
        "a pattern of concentric circles laid in blocks of black stone " +
        "on the grey ground of the courtyard. The obelisks appear to " +
        "be pillars of some sort, almost monoliths. To the north and " +
        "east the outer walls of the castle stand, and there appears " +
        "to be what's left of an archway built into the easternmost " +
        "part of the north wall. Actually, it's little more than a ragged " +
        "breach where that portion of the wall collapsed completely now. " +
        "To the general southwest rises a series of crumbling towers, " +
        "walls and ramparts that comprise the inner castle.\n\n");

    create_courtyard();    
    create_pillars();

    add_exit(RUIN + "ne_court_n", "north");
    add_exit(RUIN + "ne_court_ne", "northeast");
    add_exit(RUIN + "ne_court_e", "east");
    add_exit(RUIN + "ne_court_se", "southeast");
    add_exit(RUIN + "ne_court_s", "south");
    add_exit(RUIN + "ne_court_sw", "southwest");
    add_exit(RUIN + "ne_court_w", "west");
    add_exit(RUIN + "ne_court_nw", "northwest");
}
