/*
 * /d/Gondor/mordor/ungol/tower/east06.c
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

#define SLEEPING_ORC   "/d/Gondor/mordor/npc/sleeping_orc.c"


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
    make_the_room(); /* including several add_items :-) */

    set_name("Ungol tower, ground level");
    add_name( ({ "room", "quarters" }) );

    set_short("The tower at Cirith ungol, ground level, orc quarters");
    set_long(BSN("You are at ground level in the tower at Cirith Ungol. " +
        "The room you are in is a part of the quarters of the orcs that " +
        "guard the prisons north of here. North is a hallway with several " +
        "prisons for prisoners of the orcs. Some torches shed a little " +
        "light. The quarters extend to the west. There are a few bunks here " +
        "and you can see a table and some chairs. Against the walls you see " +
        "some closets."));

    add_item( ({ "floor", "ground" }),
        BSN("The stone floor is rather dusty. Against one of the walls are " +
        "some straw mattresses for the orcs that are on duty."));
    add_item( ({ "hall", "hallway", "passage", "prison", "prisons",
        "prison cell", "prison cells" }),
        BSN("To the north you see a broad passage, leading to several " + 
        "prison cells. In those cells, prisoners of the orcs can be locked " +
        "up."));
    add_item( ({ "bunk", "bunks", "straw", "mattress", "straw mattress",
        "mattresses", "straw mattresses", "straw bunk", "straw bunks" }),
        BSN("There are a number of straw mattresses laying against one of " +
        "the walls in this room. The bunks are use by orcs that are on " +
        "duty. Apparently they aren't guard the prisons in shifts."));
    add_item( ({ "closet", "closets" }),
        BSN("The closets are made of wood. They must contain some stuff " +
        "the orcs use in their dayly life."));
    add_item( ({ "chair", "chairs" }),
        BSN("Around the table are a few wooden chairs. The ocs that are on " +
        "must sit here, waiting till their shift is over."));
    add_item( ({ "table", "tables" }),
        BSN("It is a wooden table with several chairs around it. On the " +
        "table is nothing special interest to you."));
    add_item("something", BSN("Your guess is as good as mine. ;-)"));

    add_cmd_item( ({ "closet", "closets" }), ({ "open" }),
        BSN("You try to open one of the closets, but it won't give in."));
    add_cmd_item( ({ "chair", "on chair", "in chair" }), ({ "sit" }),
        "@@sit_on_chair");
    add_cmd_item( ({ "down", "bunk", "straw", "mattress", "on bunk",
        "on straw", "on mattress" }), ({ "lie", "sleep" }),
        BSN("For a moment you think about lying down on one of the straw " +
        "matresses, but then see something crawl away from under the bunk " +
        "you were looking at and your desire to lie down disappears " +
        "completely."));

    add_exit(CIRITH_DIR + "east04", "north");
    add_exit(CIRITH_DIR + "east02", "west");

    reset_room();
}

void
reset_room()
{
    if (!objectp(orc1))
    {    
        orc1 = clone_object(SLEEPING_ORC);
        orc1->make_the_orc(70);
        orc1->move(TO);
    }
    if (!objectp(orc2))
    {
        orc2 = clone_object(SLEEPING_ORC);
        orc2->make_the_orc(60);
        orc2->move(TO);
    }
}

/*
 * If you want to sit on the stairs.
 */
string
sit_on_chair()
{
    SAY(" sits down on one of the chairs for a while and then " + PRONOUN(TP) +
        " stands up again.");

    return BSN("You sit down on one of the chairs for a while and then you " +
        "stand up again.");
}

/*
 * This function is to let a sleeping orc know there is a bunk here.
 */
int
query_bunk()
{
    return 1;
}
