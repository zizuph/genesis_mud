/*
 * /d/Gondor/mordor/ungol/tower/centre12.c
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
 * This function defines the room.
 */
void
create_room()
{
    make_the_room(); /* including several add_items :-)    */

    set_name("Ungol tower, first floor");
    add_name( ({ "room", "passage" }) );

    set_short("The tower at Cirith ungol, first floor, passage");
    set_long(BSN("You are at the first floor in the tower at Cirtih Ungol. " +
        "It is dimly lit with torches flaring in brackets on the walls. " +
        "The silence in this room frightens you. To the west, north and " +
        "east are exits leading to and from this gloomy passage."));

    add_exit(CIRITH_DIR + "west11",   "west");
    add_exit(CIRITH_DIR + "east12",   "east");
    add_exit(CIRITH_DIR + "centre11", "north");
}
