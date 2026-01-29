/*
 * jail_corridor_3.c
 *
 * Corridor leading to the prison cells of Port MacDunn.
 *
 * Khail - March 30/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";

object e_door,
       w_door;

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
  
public object
query_east_door()
{
    return e_door;
}

public object
query_west_door()
{
    return w_door;
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
    set_short("dimly lit prison corridor");
    set_long("   You are in a dimly lit corridor that connects " +
        "the handful of prison cells for Port Macdunn. No " +
        "torches or lamps are present, the only bit of light " +
        "filters in through the narrow windows high in the " +
        "prison cells. Cells stand to the east and west, " +
        "and the corridor leads back out of the cells " +
        "section to the north.\n");

    add_item(({"window", "windows"}),
        "The windows are fairly small, just a bit larger " +
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
        "The ceiling is constructed a bit more sturdily than " +
        "most buildings in the village, and seems to be " +
        "made from several layers of wooden planks atop " +
        "heavy rafters.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "thick wooden rafters.\n");

    INSIDE;

    add_exit(ROOM + "jail_corridor_2", "north");
    e_door = clone_object(OBJ + "outer_cell_2_door");
    e_door->move(TO);
    w_door = clone_object(OBJ + "outer_cell_3_door");
    w_door->move(TO);

    reset_room();
}
