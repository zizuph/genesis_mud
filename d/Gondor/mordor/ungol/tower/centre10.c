/*
 * /d/Gondor/mordor/ungol/tower/centre10.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance.
 *
 * /Mercade, 23 October 1993
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
    make_torch();    /* get a torch, skip the add_item one */
    make_the_room(); /* including several add_items :-)    */

    set_name("Ungol tower, first floor");
    add_name( ({ "room", "passage" }) );

    set_short("The tower at Cirith ungol, first floor, passage");
    set_long(BSN("You are at the first floor in the tower at Cirith Ungol. " +
        "At first glance there is nothing special in this room. To the " +
        "west, east and south you see two gloomy rooms."));

    make_door(CIRITH_DIR + "west10", "west", 1);
    make_door(CIRITH_DIR + "east10", "east", 1);

    add_exit(CIRITH_DIR + "centre11", "south");
}
