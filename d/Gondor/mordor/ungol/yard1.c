/*
 * /d/Gondor/mordor/ungol/yard1.c
 *
 * This is the courtyard surrounding the tower at Cirith Ungol.
 *
 * /Mercade 27 july 1993
 */

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/mordor/ungol/tower_desc.c"

#define TOWER_DIR UNGOL_DIR + "tower/"

void
create_room()
{
    set_name("courtyard");
    add_name("yard");
    add_name("court");

    set_short("Courtyard near the tower at Cirith Ungol.");
    set_long(BSN("The courtyard lies in deep shadow, but you can see that " +
        "pavement has a deep dark colour. You are near a great tower, in " +
        "which many orcs dwell. From this tower, those orcs guard this " +
        "entrance to the nameless land. Very few people have even been here " +
        "and even less returned alive from this place. At the foot of the " +
        "tower, to the north, a large door is half open and a red light " +
        "comes through. The courtyard continues to the northeast and to the " +
        "southeast, you see a gate in the wall surrounding the yard."));

    ADD_ITEM_TOWER;
    add_item( ({ "wall", "walls" }), BSN("Both the walls of the tower and " +
        "wall surrounding the courtyard are very smooth. They are made of " +
        "dark stone and look very strong. The wall surrounding the court " +
        "is battlemented."));
    add_item( ({ "gate", "arch" }), BSN("To the southeast you see the gate " +
        "in the wall surrounding this courtyard. It looks like a great arch " +
        "and to your astonishment you don't see any guards or even a fence " +
        "in the opening. You feel that there must be something guarding the " +
        "gate though."));
    add_item( ({ "blood", "dark blood" }), BSN("The stones you are walking " +
        "are slippery with all the dark blood from the numerous orcs that " +
        "were slain here in a battle between two rivaling groups of orcs."));
    add_item( ({ "stone", "stones", "pavement", "tile", "tiles" }),
        BSN("The pavement is tiled with stone tiles. It looks slippery with " +
        "dark blood. Many orcs were probably slain here."));
    add_item( ({ "entrance", "door" }), BSN("At the foot of the tower, you " +
        "see a great door. It must be the entrance of the tower. The door " +
        "is made of solid wood and secured with iron bands. The hinges are " +
        "rusty and the door probably hasn't move in a long time."));

    add_cmd_item( ({ "door" }), ({ "open", "close" }),
        BSN("The door is old and rusty. It won't budge."));
    add_cmd_item( ({ "wall", "walls", "tower" }), ({ "climb" }),
        BSN("The walls of the tower and the walls surrounding the courtyard " +
        "are so smooth that you see no way to climb them."));

    add_exit(UNGOL_DIR + "yard2",  "northeast", "@@check_slippery");
    add_exit(MORGUL_DIR + "vale/inner3",  "southeast", "@@check_slippery");
    add_exit(TOWER_DIR + "east02", "north",     "@@check_slippery");
}

/*
 * The pavement is slippery with blood of the numerous orcs that are slain
 * here. You might slip if you aren't too careful :-)
 */
int
check_slippery()
{
    /* 10 percent chance to slip */
    if (random(10))
    {
        return 0;
    }

    write(BSN("You slip on the pavement in the courtyard that is slippery " +
        "with dark blood."));
    LSAY(" slips on the pavement in the courtyard that is slippery with " +
        "dark blood.", TP);

    return 1;
}
