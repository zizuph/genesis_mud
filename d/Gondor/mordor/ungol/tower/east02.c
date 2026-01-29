/*
 * /d/Gondor/mordor/ungol/tower/east02.c
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
object orc1; /* mean orcs guard the tower        */
object orc2; /* there are several orcs here      */
object orc3; /* among which you find string ones */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_torch();    /* add a torch and don't get an add_item for torch */
    make_the_room(); /* including several add_items :-)                 */

    set_name("Ungol tower, ground level");
    add_name( ({ "room", "quarters" }) );

    set_short("The tower at Cirith ungol, ground level, entrance");
    set_long(BSN("You are at ground level in the tower at Cirith Ungol. " +
        "Currently you are in a wide and echong passage, leading from the " +
        "entrance south of you to the mountain side. It is dimly lit with " +
        "torches flaring in brackets on on the walls, but its distant end " +
        "is lost in the gloom. This looks like a guarding place from which " +
        "orcs guard the prisons north of here and the entrance of the " +
        "tower. North is a hallway with several prisons for prisoners of " +
        "The quarters extend to the east. There are a few bunks here and " +
        "you can see a table and some chairs."));

    add_item( ({ "entrance", "door" }),
        BSN("To the south you see a great door, standing half open. It is " +
        "the entrance of the tower and you can see a small part of the " +
        "yard surrounding the tower through it. The door is made of solid " +
        "wood and secured with iron bands. The hinges are rusty and the " +
        "door probably hasn't moved in a long time."));
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
    add_item( ({ "chair", "chairs" }),
        BSN("Around the table are a few wooden chairs. The ocs that are on " +
        "must sit here, waiting till their shift is over."));
    add_item( ({ "table", "tables" }),
        BSN("It is a wooden table with several chairs around it. On the " +
        "table is nothing special interest to you."));
    add_item("something", BSN("Your guess is as good as mine. ;-)"));

    add_cmd_item( ({ "chair", "on chair", "in chair" }), ({ "sit" }),
        "@@sit_on_chair");
    add_cmd_item( ({ "down", "bunk", "straw", "mattress", "on bunk",
        "on straw", "on mattress" }), ({ "lie" }),
        BSN("For a moment you think about lying down on one of the straw " +
        "matresses, but then see something crawl away from under the bunk " +
        "you were looking at and your desire to lie down disappears " +
        "completely."));
    add_cmd_item( ({ "door" }), ({ "open", "close" }),
        BSN("The door is strong, but the hinges are rusty. It won't budge."));

    add_prop(ROOM_I_LIGHT, 1); /* the entrance isn't dark by default. */

    add_exit(CIRITH_DIR + "east01",   "north");
    add_exit(CIRITH_DIR + "east05",   "east");
    add_exit(UNGOL_DIR + "yard1",    "south");
    add_exit(CIRITH_DIR + "centre02", "west");

    reset_room();
}

void
reset_room()
{
    if (!objectp(orc1))
    {
        orc1 = make_orc(110);
    }
    if (!objectp(orc2))
    {
        orc2 = make_orc(45);
    }
    if (!objectp(orc3))
    {
        orc3 = make_orc(80);
    }
}

/*
 * Code for if you want to sit in a chair.
 */
string
sit_on_chair()
{
    SAY(" sits down on one of the chairs for a while and then " + PRONOUN(TP) +
        " stands up again.");

    return BSN("You sit down on one of the chairs for a while and then you " +
        "stand up again.");
}
