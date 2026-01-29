/*
 * /d/Gondor/mordor/ungol/stairs/sstair_t.c
 *
 * This is a part of the Straight Stair. I like these kind of rooms that have
 * all the fancy stuff in a default file.
 *
 * /Mercade, 22 November 1993
 *
 * Revision History:
 */

inherit "/d/Gondor/mordor/ungol/stairs/std_straight.c";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>

#define DOWN_ROOM (STAIRS_DIR + "straight10")

void
create_room()
{
    set_short("On top of the Straight Stair in the Mountains of Shadow");
    set_long(BSN("You are on top of the Straight Stair, deep into the " +
        "Mountains of Shadow, Ephel Duath. This is a dark small passage " +
        "that seems to go up, though at a gentle slope and without steps."));

    add_mountain();
    add_walls();
    add_stair();
    add_item( ({ "passage", "slope" }),
        BSN("This passage goes up slightly. It is much easier to walk here " +
        "than climbing on the stairs. However the Straight Stair is the " +
        "only way down. What to expect to the east you cannot tell from " +
        "place."));

    add_exit(STAIRS_DIR + "winding1", "east");

    add_prop(ROOM_I_NO_ME_SUN, 1);
    add_prop(OBJ_S_WIZINFO,
        BSN("This room is on top of the Straight Stair. The first stairs on " +
        "the journey to Torech Ungol, Shelobs lair. A player that tries to " +
        "climb this stair might just find himself lying hurt or even dead " +
        "at the foot and those that survive will have to climb the Winding " +
        "Stairs before they enter the lair and face Shelob... /Mercade"));
}

/*
 * Function name: do_up
 * Description  : This is a redefinition to make sure that you cannot climb
 *                up in this room.
 * Arguments    : string str - the command line argument.
 * Returns      : 0 - always
 */
int
do_up(string str)
{
    NFN0("You cannot climb the mountains any further.");
}

/*
 * Function name: query_room_down
 * Description  : This is an ugly function to allow me to define DOWN_ROOM
 *                in this file and access it from the inherited file.
 */
string
query_room_down()
{
    return DOWN_ROOM;
}
