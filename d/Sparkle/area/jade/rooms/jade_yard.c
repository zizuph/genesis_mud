/*
*  /d/Sparkle/area/jade/rooms/yard.c
*  Created 2017-01-23 by Martin Berka on Genesis MUD
*
*/

#pragma strict_types

#include "../defs.h"
inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>

/* Prototypes */
static object   family,
                family0,
                family3;

/*
 * Function name: create_room
 * Description  : Adds Mar's settings to the default workroom setup.
 */
void
create_room()
{
    object door;

    set_short("A fenced yard");
    set_long("A small, barren yard lies before a two-storey house with a steep "
        + "roof to the east. To the north, at the other end of the yard is a "
        + "pile of fruit next to a stand. The yard is surrounded by a strong "
        + "wooden fence. Beyond the fence to the northeast and southeast "
        + "grow fruit trees. The far side of the fence in the remaining "
        + "directions consists of a strip of scorched earth followed by the "
        + "wilder trees of the Jade Forest, which can be reached through the "
        + "open gateway to the west.\n");

    add_item( ({"ground", "yard", "small yard", "small barren yard",
        "barren yard"}),
        "This part of the yard is barren, the dirt packed down by frequent "
        + "trampling.\n");
    add_item( ({"trampling", "dirt", "packed dirt"}),
        "Many feet have been here before.\n");
    add_item( ({"gateway", "open gateway", "west", "opening", "narrow opening"}),
        "A narrow opening in the fence allows passage to the forest to "
        + "the west.\n");

    add_item( ({"end", "other end", "pile", "fruits", "pile of fruit", "stand",
        "fruit stand", "north"}),
        "Various fruits are piled next to a fruit stand. You will have to go "
        + "north to get a closer look.\n");
    add_item(({"fruit trees", "fruit"}),
        "The fruit trees grow well east of fence and house - well-tended "
        + "and out of reach\n");

    add_orchard();
    add_deadzone();
    add_forest();
    add_house();
    add_fence( ({ "southwest", "northwest", "southeast", "south" }) );

    add_item( ({ "door", "front door", "east door",
        "doorway", "green doorway", "front doorway", "east doorway",
        "eastern door", "fortified door", "green fortified door",
        "door to the east", "green door to the east" }),
        "The door leading into the house is made of greyish-green wood and is "
        + "heavily fortified, though "
        + "open and readily passable at present.\n" );

    add_exit(ROOM_DIR + "jade_forest_w", "west");
    add_exit(ROOM_DIR + "jade_house", "east");
    add_exit(ROOM_DIR + "jade_stand", "north");
    add_exit(ROOM_DIR + "jade_stand", "northeast", 0, 1, 1);

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(PATH_HOME_PROP, "east");
    reset_room();
}

/*
 * Function name: reset_room
 * Description  : Populate room with NPC's
 */
void
reset_room()
{
    if (!objectp(family0))
    {
        family0 = clone_object(NPC_DIR + "family.c");
        family0->set_family_index(0);
        family0->move(TO);
    }
}

/*
 * Function name: init
 * Description:   set up the commands
 */
void
init()
{
    ::init();
} /* init */
