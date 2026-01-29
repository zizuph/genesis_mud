/*
 * /d/Gondor/mordor/ungol/tower/look20.c
 *
 * This is the a part of the lookout on top of the first tier of the tower at
 * Cirith Ungol. It isn't very exciting except for the fact that you will hear
 * it if people are walking in the tower withing hearing distance. This room
 * will allow you to see parts of Mordor.
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
    no_add_items();  /* to block the add_items in make_the_room */
    make_the_room(); /* make_the_room does more though ;-)      */

    set_name("Ungol tower, second floor");
    add_name( ({ "room", "lookout", "look-out" }) );

    set_short("The tower at Cirith ungol, second floor, lookout");
    set_long(BSN("You are standing on top of the first tier of the tower at " +
        "Cirith Ungol. As the next tier is smaller than the first one, " +
        "there is space for a terrace, which is used as a look-out. A long " +
        "time ago, when the man of Gondor ruled this tower, it was used to " +
        "see when the evil creatures of the dark one might try to make a " +
        "sally. Now it is used to see any intruders in the dark land. This " +
        "position gives a good view on the south and southwest. To the west " +
        "are the Mountains of Shadow, Ephel Duath. To get a good look at " +
        "Plateau of Gorgoroth and to look further into Mordor in general, " +
        "both east of you, you will have to go east first for the tower " +
        "blocks a part of the view. The darkness makes it hard to see very " +
        "much for massive clouds of darkness block most of the sunlight. " +
        "Going north and west will bring you back into the tower."));

    add_item_stone(); /* The default add_item for stone will do */
    add_item( ({ "wall", "walls" }),
        BSN(""));
    add_item( ({ "floor", "ground" }),
        BSN(""));

    add_item( ({ "ephel duath", "mountain", "mountains",
        "mountains of shadow" }),
        BSN(""));
    add_item( ({ "plateau", "gorgoroth", "plateau of gorgoroth" }),
        BSN(""));
    add_item( ({ "mordor", "view" }),
        BSN(""));

    add_prop(OBJ_S_WIZINFO,
        BSN("This tower has to nice features. If you walk here, other " +
        "people that are within hearing distance will hear you walking. " +
        "The stairs are developed like a so-called winding staircase. If " +
        "you go northeast, you descend the stairs, if you go southeast you " +
        "up. This particular room is a look-out where you might see parts " +
        "of Mordor."));

    add_exit(CIRITH_DIR + "west23",  "west");
    add_exit(CIRITH_DIR + "south20", "north");
    add_exit(CIRITH_DIR + "look21",  "east");

    reset_room();
}

void
init()
{
    add_action("do_look", "look");
}

void
reset_room()
{
    if (!objectp(orc1))
    {
        orc1 = make_orc(80);
    }
    if (!objectp(orc2))
    {
        orc2 = make_orc(60);
    }
}

/*
 * I will allow people to do "look" with a direction, i.e. "look south"
 */
int
do_look()
{
    return 0;
}
