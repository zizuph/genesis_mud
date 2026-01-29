/*
 * /d/Gondor/mordor/ungol/tower/west13.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance.
 *
 * /Mercade, 11 October 1993
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
object orc1; /* mean orcs guard the tower            */
object orc2; /* there are two orcs here to play with */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_torch();    /* put here to get no add_item for torch */
    make_the_room(); /* including several add_items :-)       */

    set_name("Ungol tower, first floor");
    add_name( ({ "room", "kitchen", "storage" }) );

    set_short("The tower at Cirith ungol, first floor, kitchen");
    set_long(BSN("You are at the first floor in the tower at Cirith Ungol. " +
        "It is dimly lit with torches flaring in brackets on the walls. " +
        "There is nothing special in this room. To the south you see " +
        "something that vaguely resembles to a kitchen and to the north and " +
        "east you see two other gloomy rooms."));

    make_door(CIRITH_DIR + "stairs1", "east", 1);

    add_exit(CIRITH_DIR + "west12",  "north");
    add_exit(CIRITH_DIR + "west14",  "south");

    reset_room();
}

void
reset_room()
{
    if (!objectp(orc1))
    {
        orc1 = make_orc(50);
    }
    if (!objectp(orc2))
    {
        orc2 = make_orc(60);
    }
}
