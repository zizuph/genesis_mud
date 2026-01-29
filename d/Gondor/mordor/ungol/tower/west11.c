/*
 * /d/Gondor/mordor/ungol/tower/west11.c
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
    make_torch();    /* add a real torch, not the add_item */
    make_the_room(); /* including several add_items :-)    */

    set_name("Ungol tower, first floor");
    add_name( ({ "room", "passage" }) );

    set_short("The tower at Cirith ungol, first floor, passage");
    set_long(BSN("You are at the first floor in the tower at Cirtih Ungol. " +
        "It is dimly lit with torches flaring in brackets on the walls. " +
        "To the north and east are exits from this gloomy passage. The " +
        "stairs are to the north."));

    add_item(({ "stair", "stairs"}),
        BSN("They are to the north, you cannot see more details on them."));

    add_exit(CIRITH_DIR + "stairs1",  "north");
    add_exit(CIRITH_DIR + "centre12", "east");

    reset_room();
}

void
reset_room()
{
    if (!objectp(orc))
    {
        orc = make_orc(50, 0);
    }
}
