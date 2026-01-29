/*
*  /d/Sparkle/area/jade/yard.c
*  Created 2017-01-23 by Martin Berka on Genesis MUD
*
*/

#pragma strict_types

#include "../defs.h"
inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>

/* Prototypes */
object family4;

/*
 * Function name: create_room
 * Description  : Constructor for the room
 */
void
create_room()
{
    set_short("A path in the Jade Forest");
    set_long("The trees of the Jade Forest tower over a path in the Jade "
        + "Forest. To the west, the trees have been cleared well away from a "
        + "wooden fence, beyond which stand a two-storey "
        + "house and a large orchard. To the east, you can just make out a "
        + "white road cutting through the forest.\n");

    add_item( ({"road", "white road", "paved road", "white paved road",
        "bright road", "east"}), "To the east, a white road cuts through the "
        + "forest running north-south.\n");
    add_item( ({"road", "white road", "paved road", "white paved road",
        "bright road", "east"}), "To the east, a white paved road cuts "
        + "through the forest running north-south.\n");
    add_item( ({ "path", "trail", "ground" }), "The path appears to be wide "
        + "and freshly cut from the surrounding undergrowth.\n");
    add_item("tree", "You can't see the trees for the forest!\n");

    add_house();
    add_fence( ({"northeast"}) );
    add_forest( ({"north", "northwest", "southwest"}) );

    add_exit(ROOM_DIR + "s_road3", "west");
    add_exit(ROOM_DIR + "jade_yard", "east");
    add_exit(ROOM_DIR + "jade_forest_s", "south");
    add_exit(ROOM_DIR + "jade_forest_s", "southeast", 0, 1, 1);

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(PATH_HOME_PROP, "east");

    reset_room();
}

/*
 * Function name: reset_room
 * Description  : Populate room with potentially role-holding NPC
 */
void
reset_room()
{
    if (!objectp(family4))
    {
        family4 = clone_object(NPC_DIR + "family.c");
        family4->set_family_index(4);
        family4->move(TO);
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
