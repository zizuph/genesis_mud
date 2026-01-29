/*
 * /d/Gondor/mordor/ungol/tower/west02.c
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

#define SLEEPING_ORC  "/d/Gondor/mordor/npc/sleeping_orc.c"

/*
 * Prototype
 */
void reset_room();

/*
 * Global variables
 */
object orc1; /* An orc guarding the room */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_torch();    /* Don't get the add_item torch    */
    make_the_room(); /* including several add_items :-) */

    set_name("Ungol tower, ground level");
    add_name("room");

    set_short("The tower at Cirith ungol at the ground level");
    set_long(BSN("This is a dark room on the mountain side of the tower, " +
        "here at Cirith Ungol. This room is probably used by orcs to sleep " +
        "if they are of guard for you see some bunks here. Some torches are " +
        "flaring in their brackets, giving some light to this place."));

    add_item( ({ "floor", "ground" }),
        BSN("The stone floor is rather dusty. Against one of the walls are " +
        "some straw mattresses for the orcs that are on duty."));
    add_item( ({ "bunk", "bunks", "straw", "mattress", "straw mattress",
        "mattresses", "straw mattresses", "straw bunk", "straw bunks" }),
        BSN("There are a number of straw mattresses laying against one of " +
        "the walls in this room. The bunks are use by orcs that are on " +
        "duty. Apparently they aren't guard the prisons in shifts."));
    add_item("something", BSN("Your guess is as good as mine. ;-)"));

    add_cmd_item( ({ "down", "bunk", "straw", "mattress", "on bunk",
        "on straw", "on mattress" }), ({ "lie", "sleep" }),
        BSN("For a moment you think about lying down on one of the straw " +
        "matresses, but then see something crawl away from under the bunk " +
        "you were looking at and your desire to lie down disappears " +
        "completely."));

    add_exit(CIRITH_DIR + "centre03", "east");
    add_exit(CIRITH_DIR + "west06",   "west");

    reset_room();
}

void
reset_room()
{
    if (!objectp(orc1))
    {
        orc1 = clone_object(SLEEPING_ORC);
        orc1->make_the_orc(70);
        orc1->move(TO);
    }
}

/*
 * This function tells a sleeping orc that there is a bunk to sleep on.
 */
int
query_bunk()
{
    return 1;
}
