/*
 * /d/Gondor/mordor/ungol/tower/winding0.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance. This room is there to create a
 * better effect on the winding stairs.
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/tower/winding";

#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Gondor/defs.h"

#define HIGHER_ROOM CIRITH_DIR + "stairs1"
#define LOWER_ROOM  CIRITH_DIR + "stairs0"

/*
 * This function defines the room.
 */
void
create_room()
{
    create_winding(); /* this will create the winding stairs */

    set_name("Ungol tower, winding staircase");
    add_name( ({ "room" }) );

    set_short("Tower at Cirith ungol on the stairs between ground level " +
        "and first floor");
    set_long(BSN("You are in the staircase between the ground floor and the " +
        "the first floor of the tower at Cirith Ungol. It is dimly lit by " +
        "torches that flare in on the floors. The stairs continue up to the " +
        "southwest and if you go south you go down."));

    add_exit(LOWER_ROOM,  "south",     "@@walk_south",     2);
    add_exit(HIGHER_ROOM, "southwest", "@@walk_southwest", 2);
}

/*
 * When you leave south, you will descend the stairs and in fact go down
 */
int
walk_south()
{
    write(BSN("Walking south, you descend the stairs to the ground floor."));
    SAY(" descends the stairs as " + PRONOUN(TP) + " walks south.");
    return 0;
}

/*
 * When you leave southeast, you will climb the stairs and in fact go up ;-)
 */
int
walk_southwest()
{
    write(BSN("Walking southwest, you climb the stairs to the first floor."));
    SAY(" climbs the stairs as " + PRONOUN(TP) + " walks southwest.");
    return 0;
}

/*
 * This is a rather ugly construct to allow people to define LOWER_ROOM in
 * this file and access it in the inherited master.
 */
string
lower_room()
{
    return LOWER_ROOM;
}
