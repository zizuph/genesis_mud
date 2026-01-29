/*
 * /d/Gondor/mordor/ungol/tower/centre03.c
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

#define TOWERORC  "/d/Gondor/mordor/npc/towerorc.c"

/*
 * Prototypes
 */
void reset_room();

object orc1; /* An orc guarding the room */


/*
 * This function defines the room.
 */
void
create_room()
{
    make_the_room(); /* including several add_items :-) */

    set_name("Ungol tower, ground level");
    add_name( ({ "room", "passage" }) );

    set_short("The tower at Cirith ungol, ground level, gloomy passage");
    set_long(BSN("You are at ground level in the tower at Cirith Ungol. " +
        "You are in a gloomy passage. To the north is another passage. This " +
        "passage continues to the west."));

    add_item( ({ "passage", "gloomy passage" }),
        BSN("You are in a gloomy passage and there is another gloomy " +
        "passage to the north. You cannot see what is in them though. "));

    add_exit(CIRITH_DIR + "centre02", "north");
    add_exit(CIRITH_DIR + "west02",   "west");
}

void
reset_room()
{
    if (!objectp(orc1))
    {
        orc1 = clone_object(TOWERORC);
        orc1->make_the_orc(70);
        orc1->move(TO);
    }
}

