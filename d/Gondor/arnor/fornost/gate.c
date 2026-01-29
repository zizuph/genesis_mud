/*
 *      /d/Gondor/arnor/fornost/gate.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
 */
#pragma strict_types

inherit "/d/Gondor/arnor/fornost/fornost.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_fornost()
{
    set_short("at the gate of the ruins of Fornost");

    add_grass();
    add_rubble();
    add_ruins();
    add_stones();

    add_item(({ "gate", "east guardtower" }), 
    "There is nothing worth looking at remaining.\n");
    add_item("west guardtower", 
    "You wonder what makes this tower being in better shape than "+
    "the eastern one.\n");
    add_item("rubble", "Waste fragments of stones.\n");
    add_item(({"piles","pile","material","reddish brown material"}), BSN(
    "Brushing some of the reddish brown material away with your hand, "+
    "you discover a dull metallic gleam. These must have been the hinges "+
    "for the great gates of Fornost, and made of strong stuff indeed, "+
    "to have lasted these long years! "));

    add_exit(FORNOST_DIR + "street", "north", 0, 3);
    add_exit(FORNOST_DIR + "l_tower", "northeast", 0, 3);
    add_exit(FORNOST_DIR + "dike", "south", 0, 3);
}

string
set_arnor_long()
{
    string desc;

    desc = "The tumbled remains of the gate and watchtowers of "+
    "Fornost. To the east sits a circular pile of rubble, standing barely "+
    "three feet high, it is all that remains of the eastern guardtower. "+
    "To the west stands a mostly intact guardtower, although the walls "+
    "end suddenly as it has no roof. Rubble lies at your feet, the broken "+
    "remains of many great stone archways and catwalks. A few piles of "+
    "a reddish brown material lie near the remains of each tower. ";
    desc += query_arnor_time();

    return BSN(desc);
}
