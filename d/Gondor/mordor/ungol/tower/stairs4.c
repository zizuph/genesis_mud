/*
 * /d/Gondor/mordor/ungol/tower/stairs4.c
 *
 * This is the fourth level of the tower of Cirith Ungol. It isn't very
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
    make_torch();    /* no add_item torch for we have a real one */
    make_the_room(); /* including several add_items :-)          */

    set_name("Ungol tower, first floor");
    add_name( ({ "room", "passage" }) );

    set_short("The tower at Cirith ungol at the fourth floor in the " +
        "staircase");
    set_long(BSN("You are at the fourth floor in the tower at Cirtih Ungol. " +
        "It is dimly lit with torches flaring in brackets on the walls, but " +
        "its distant end is lost in the gloom. To the west is a door " +
        "leading to another room and to the north, this hallway continues. " +
        "In the dimly lit hall, you see two dark openings to the east and " +
        "in it you vaguely recognize some stairs leading up and down in " +
        "this dreadful place. TO BE ADJUSTED"));

    add_item( ({ "stair", "stairs", "opening" }),
        BSN("Peering into the gloom you cannot see much of the stairs, " +
        "except for the fact that they are made of stone and that the " +
        "stairs northeast lead down the tower and the stairs northwest " +
        "will bring you higher in this dark the tower."));

    add_exit(CIRITH_DIR + "winding3", "northeast", "@@walk_northeast", 2);
    add_exit(CIRITH_DIR + "winding4", "northwest", "@@walk_northwest", 2);

    reset_room();
}

/*
 * When you leave northeast, you will descend the stairs and in fact go down
 */
int
walk_northeast()
{
    write(BSN("Walking northeast, you descend the stairs."));
    SAY(" descends the stairs as " + PRONOUN(TP) + " walks northeast.");
    return 0;
}

/*
 * When you leave northwest, you will climb the stairs and in fact go up ;-)
 */
int
walk_northwest()
{
    write(BSN("Walking northwest, you climb the stairs."));
    SAY(" climbs the stairs as " + PRONOUN(TP) + " walks northwest.");
    return 0;
}

/*
 * This procedure is called each time the room needs to be updated. Here also
 * is a check for the orc guards. They will re-appear if killed before.
 */
void
reset_room()
{
    if (!objectp(orc))
    {
        orc = make_orc(60);
    }
}
