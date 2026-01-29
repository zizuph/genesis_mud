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

#define UNDER_GATE  "/d/Gondor/mordor/obj/undergate_tower.c"

/*
 * Global variables
 */
object orc; /* an orc, guarding the gate */

/*
 * Prototype
 */
void reset_room();

/*
 * This function defines the room.
 */
void
create_room()
{
    make_the_room(); /* including several add_items :-)     */

    set_name("Ungol tower, ground level");
    add_name("room");

    set_short("The tower at Cirith ungol at the ground level");
    set_long(BSN("This is a dark room on the mountain side of the tower, " +
        "here at Cirith Ungol. To the east is the main hall, a wide echoing " +
        "passage. Some torches are flaring in their brackets, giving some " +
        "light to this place. From this point you cannot see what is in " +
        "the rooms north and south of here. To the west is a great arched " +
        "door, probably leading to a system of caves in the mountain."));

    add_item( ({ "hall", "hallway", "passage" }),
        BSN("The main hall is to the east. The exit of this great tower " +
        "can be found there."));

    clone_object(UNDER_GATE)->move(TO);

    add_exit(CIRITH_DIR + "stairs0", "east");
    add_exit(CIRITH_DIR + "west04",  "north");
    add_exit(CIRITH_DIR + "west06",  "south");

    reset_room();
}

/*
 * Reset room gets a new orc if the other one is dead.
 */
void
reset_room()
{
    if (!objectp(orc))
    {
        orc = make_orc(120, 1); /* Add this orc a nice whip */
    }
}
