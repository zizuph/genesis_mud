/*
 *    - clone npcs into a room
 *    - use VBFC in add_exit
 *    - block an exit of a room using npcs
 */
inherit "/std/room";

// for CAN_SEE, CAN_SEE_IN_ROOM
#include <macros.h>
// for LIVE_I_SEE_DARK
#include <stdproperties.h>

#include "examples.h"

// I want to add guards to the bridge.
static object *guards = allocate(3); 

void
add_guards()
{
    int     i = sizeof(guards);

    while(i--)
    {
        // clone a new guard only if it does not exist already
        if (!objectp(guards[i]))
        {
            guards[i] = clone_object(EX_NPC + "bridge_guard");
            guards[i]->arm_me();
            guards[i]->move_living("into the world", this_object());
        }
    }
}

public void
reset_room()
{
    add_guards();
}

void
create_room()
{
    set_short("in front of a bridge");

    set_long("The plains end here at the bank of a river, but the "
      + "road continues northward across a wooden bridge.\n");

    //  and put the details into the item descriptions
    add_item(({"road", "street", }),
        "South of the river, the south is running in a straight line "
      + "across a wide empty plain, while to the north it crosses the "
      + "river on a wooden bridge to disappear into a dense forest.\n");
    add_item(({"forest", "wood", }),
        "A dense forest is rising on the northern bank of the river.\n");
    add_item(({"plain", "plains", }),
        "A wide empty plain is stretching south of the river as far "
      + "as one can see. The road is running across the plain in a "
      + "straight line. Besides the road there is only one feature "
      + "standing out, a small group of bushes several hundred yards "
      + "south of the river.\n");
    add_item(({"bushes", "group", "group of bushes", }),
        "It is hard to make out any details from this far off. It "
      + "looks like a small group of bushes, conspicious only because "
      + "it is the only one visible on the plain.\n");
    add_item(({"river", "stream", "water", }),
        "The river is about fifty yards wide here. The water is flowing "
      + "slowly from east to west.\n");
    add_item(({"bridge", "wooden bridge", }),
        "The bridge spans the river in two wide arches which both rest "
      + "with one end on a stone pier in the middle of the river. "
      + "Except for the pier, the bridge has been built from wood. "
      + "At this end of the bridge there is a small wooden booth.\n");
    add_item(({"pier", "stone pier", "arch", "arches", }),
        "Both arches of the bridge rest with one end on a bank and "
      + "with the other on a stone pier in the middle of the river.\n");
    add_item(({"booth", "toll booth", }),
        "At the southern end of the bridge, there is a small booth. "
      + "It might be used by the guards in bad weather.\n");

    add_exit(STAND_DIR + "bridge",    "north", "@@check_guards", 1);
    add_exit(STAND_DIR + "plain_rd1", "south", 0, 1);

    reset_room();
}

public int
check_guards()
{
    object  guard = present("_bridge_guard", this_object());
    // this picks one guard. If there is more than one guard in the room,
    // the check is not done for all guards, but just for one.

    // this takes care of invisible or sneaking players.
    if (!CAN_SEE_IN_ROOM(guard) || !CAN_SEE(guard, this_player()))
        return 0;

    this_player()->catch_msg(QCTNAME(guard) + " stops you from going there!\n");
    say(QCTNAME(guard) + " stops " + QTNAME(this_player())
      + " from going north.\n", ({ this_player(), guard }));

    return 1;
}

