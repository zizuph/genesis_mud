/*
 * /d/Gondor/mordor/ungol/tower/west01.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance.
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/tower/stdtower";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/*
 * Prototypes
 */
void reset_room();

/*
 * Global variables
 */
object orc; /* mean orcs guard the tower */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_torch();    /* no add_item torch for we have a real one. */
    make_the_room(); /* including several add_items :-)           */

    set_name("Ungol tower, ground level");
    add_name( ({ "room", "hall", "hallway", "passage" }) );

    set_short("The tower at Cirith ungol, ground level, prison hallway");
    set_long(BSN("You are at ground level in the tower at Cirith Ungol. " +
        "This room is probaly hewn out of the rocks of the mountain. You " +
        "are in a prison hall which continues to the west and east. To the " +
        "north are several small cells where prisoners, captured here, are " +
        "held until they are send further for questioning or punishment. " +
        "Several torches shed a little light on the walls."));

    add_item( ({ "cell", "cells", "prison", "prisons" }),
        BSN("To the north you see several doors, leading to small cells " +
        "where prisoner of the orcs might be locked up. In the doors are " +
        "small spy-holes to look at the prisoners in the cells. To the " +
        "east this hall continues with more cells."));
    add_item( ({ "hole", "holes", "spy-hole", "spy-holes", "spy hole",
        "spy holes" }),
        BSN("They are small holes in the doors to the prison cells. When " +
        "you look though the holes, you cannot see whether there are " +
        "prisoners in the cells, for they are too dark and when you move " +
        "your head for the hole, you block the little light from the toches " +
        "in this dark passage."));

    make_door(CIRITH_DIR + "west00", "north", 2);

    add_exit(CIRITH_DIR + "centre01", "east");
    add_exit(CIRITH_DIR + "west04",   "west");

    reset_room();
}

void
reset_room()
{
    if (!objectp(orc))
    {
        orc = make_orc(45, random(2)); /* 50% chance to get a whip */
    }
}
