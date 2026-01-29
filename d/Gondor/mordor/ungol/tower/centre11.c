/*
 * /d/Gondor/mordor/ungol/tower/centre11.c
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
 * Prototype
 */
void reset_room();

/*
 * Global variables
 */
object orc1; /* There are orcs guarding this tower   */
object orc2; /* Many orcs and they are all after you */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_the_room(); /* including several add_items :-)    */

    set_name("Ungol tower, first floor");
    add_name( ({ "room", "hallway" }) );

    set_short("The tower at Cirith ungol, first floor, hallway");
    set_long(BSN("You are at the first floor in the tower at Cirtih Ungol. " +
        "This room is in a hallway somewhere in the heart of the tower " +
        "It is dimly lit with torches flaring in brackets on the walls. " +
        "To the north and south are exits leading to and from this hallway."));

    add_exit(CIRITH_DIR + "centre10", "north");
    add_exit(CIRITH_DIR + "centre12", "south");
}

void
reset_room()
{
    if (!objectp(orc1))
    {
        orc1 = make_orc(95, 0);
    }
    if (!objectp(orc2))
    {
        orc2 = make_orc(55, 0);
    }
}
