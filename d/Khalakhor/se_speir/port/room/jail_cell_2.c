/*
 * jail_cell_2.c
 *
 * One of the prison cells of Port MacDunn.
 *
 * Khail - March 30/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

public int *
query_local_coords()
{
    return ({18,2});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public int
is_jail_cell()
{
    return 1;
}

/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
    set_short("prison cell in Port Macdunn");
    set_long("   You are in a small cell in the prison of " +
        "Port Macdunn. Pretty much square in shape, the " +
        "cell looks like it's been built quite solidly, " +
        "with walls made of thick slabs of stone, and " +
        "larger slabs of stone jointed together somehow " +
        "to form a ceiling. The only light trickles down " +
        "into the room through a window high up on the " +
        "wall, and the only thing on the floor here is " +
        "dirt and a variety of stains you don't even want " +
        "to consider identifying.\n");

    add_item(({"window"}),
        "The window is fairly small, just a bit larger " +
        "than a man's head. However, they've been covered " +
        "with bars, just in case they have a particularly " +
        "slippery prisoner.\n");
    add_item(({"floor", "ground"}),
        "The floor of the room is simply hard-packed " +
        "earth.\n");
    add_item(({"walls", "wall"}),
        "The walls of the room are made from various sized " +
        "pieces of hard grey stone, carefully placed together " +
        "and packed with clay.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling is made from heavy slabs of stone " +
        "carefully jointed together.\n");

    INSIDE;

    clone_object(OBJ + "inner_cell_2_door")->move(TO);

    reset_room();
}
