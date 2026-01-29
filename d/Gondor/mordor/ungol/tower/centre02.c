/*
 * /d/Gondor/mordor/ungol/tower/centre02.c
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
object orc1; /* mean orcs guard the tower      */
object orc2; /* there are several orcs here    */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_torch();    /* we don't want a torch and an add_item torch */
    make_the_room(); /* including several add_items :-) */

    set_name("Ungol tower, ground level");
    add_name( ({ "room", "hall", "hallway", "passage" }) );

    set_short("The tower at Cirith ungol, ground level, long passage");
    set_long(BSN("You are at ground level in the tower at Cirith Ungol. " +
        "This room is approximately located in the centre of the tower. " +
        "You are in a gloomy passage. To the north is another passage. This " +
        "passage continues to the west and east. To the south is another " +
        "room, though the darkness prevents you to see much in it."));

    add_exit(CIRITH_DIR + "stairs0",  "west");
    add_exit(CIRITH_DIR + "east02",   "east");
    add_exit(CIRITH_DIR + "centre01", "north");
    add_exit(CIRITH_DIR + "centre03", "south");

    reset_room();
}

void
reset_room()
{
    if (!objectp(orc1))
    {
        orc1 = make_orc(100);
    }
    if (!objectp(orc2))
    {
        orc2 = make_orc(60);
    }
}
