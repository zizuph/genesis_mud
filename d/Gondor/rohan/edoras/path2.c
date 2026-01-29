#pragma strict_types

inherit "/d/Gondor/common/lib/town.c";

#include "/d/Gondor/defs.h"

public void    reset_room();

static object  Child;

private int npccheck() { return (TP->query_npc()); }

void
create_room()
{
    set_hillside("west");
    set_height(1);
    set_road(1);
    set_density(3);
    set_extraline("There is a wooden house to the west. From the smell you " +
    "realise it must be a stable. To the east lies the Edoras Guild of " +
    "Adventurers. The gates of Edoras are to the northeast and Kingsroad " +
    "continues upwards around the hill to the southeast.");

    add_exit(EDORAS_DIR + "rooms/edtransport", "west",      0, 0);
    add_exit(EDORAS_DIR + "rooms/guild",       "east",      npccheck);
    add_exit(EDORAS_DIR + "ingate",            "northeast", 0);
    add_exit(EDORAS_DIR + "path3",             "southeast", 0); 

    make_the_room();
    reset_room();
}

public void
reset_room()
{
    if (!objectp(Child))
    {
        Child = clone_object(EDORAS_DIR + "npc/child");
        Child->arm_me();
        Child->move_living("down", TO);
    }
}



