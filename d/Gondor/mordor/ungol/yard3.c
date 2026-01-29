/*
 * /d/Gondor/mordor/ungol/yard3.c
 *
 * This is the courtyard surrounding the tower at Cirith Ungol.
 *
 * /Mercade 27 july 1993
 */

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/mordor/ungol/tower_desc.c"

void
create_room()
{
    set_name("courtyard");
    add_name("yard");
    add_name("court");

    set_short("Courtyard near the tower at Cirith Ungol.");
    set_long(BSN("This part of the courtyard is a dead end. To the west is " +
        "the great tower and to the north is a mountain wall. From the " +
        "tower, many orcs guard this entrance to the nameless land. Very " +
        "few people have even been here and even less returned alive from " +
        "this place. The courtyard continues to the southeast."));

    ADD_ITEM_TOWER;
    add_item( ({ "wall", "walls" }), BSN("Both the walls of the tower and " +
        "wall surrounding the courtyard are very smooth. They are made of " +
        "dark stone and look very strong. The wall surrounding the court " +
        "is battlemented."));
    add_item( ({ "gate", "arch" }), BSN("To the south you see the gate " +
        "in the wall surrounding this courtyard. It looks like a great arch " +
        "and to your astonishment you don't see any guards or even a fence " +
        "in the opening. You feel that there must be something guarding the " +
        "gate though."));
    add_item( ({ "stone", "stones", "pavement", "tile", "tiles" }),
        BSN("The pavement is tiled with stone tiles. This part of the yard " +
        "is quite bare and you don't see anything special here."));

    add_cmd_item( ({ "wall", "walls", "tower" }), ({ "climb" }),
        BSN("The walls of the tower and the walls surrounding the courtyard " +
        "are so smooth that you see no way to climb them."));

    add_exit(UNGOL_DIR + "yard2", "southeast");
}
