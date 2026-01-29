/*
 *  /d/Emerald/common/guild/aod/rooms/trophy_9x3.c
 *
 *  One of the 100 rooms that the Ogre guild has at its disposal for
 *  trophy storage.
 *
 *  Created June 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include <stdproperties.h>

inherit AOD_ROOM_DIR + "trophy_1x1";
inherit AOD_LIB_DIR + "add_spike";

/* prototypes */
public void        create_cave_room();


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("in a vast trophy chamber");
    set_em_long("Though thick and crusted, the walls here are"
      + " softened by smooth rounded curves and corners. This appears"
      + " to be some sort of large hollowed-out chamber within a"
      + " magma deposit. Many dozens of trophy spikes are visible"
      + " in the chamber. Apparently, this area is used to store the"
      + " spoils of various exploits that the Ogre Chieftains have"
      + " produced over the years.\n");

    add_trophy_items();
    add_cave_items();

    add_spike("trophy_9x3");

    add_exit("trophy_8x3", "north");
    add_exit("trophy_8x4", "northeast");
    add_exit("trophy_9x4", "east");
    add_exit("trophy_10x4", "southeast");
    add_exit("trophy_10x3", "south");
    add_exit("trophy_10x2", "southwest");
    add_exit("trophy_9x2", "west");
    add_exit("trophy_8x2", "northwest");
} /* create_cave_room */
