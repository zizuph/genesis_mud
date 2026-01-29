/*
 * /d/Gondor/mordor/ungol/tower/east14.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance.
 *
 * /Mercade, 26 October 1993
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
        "To the north is a room that is used for working and to the south " +
        "is another exit from this passage."));

    make_door(CIRITH_DIR + "east13", "north", 2);

    add_exit(CIRITH_DIR + "east15", "south");
}
