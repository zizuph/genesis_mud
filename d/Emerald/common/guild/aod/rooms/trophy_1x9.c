/*
 *  /d/Emerald/common/guild/aod/rooms/trophy_1x9.c
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

    add_spike("trophy_1x9");

    add_exit("trophy_1x10", "east");
    add_exit("trophy_2x10", "southeast");
    add_exit("trophy_2x9", "south");
    add_exit("trophy_2x8", "southwest");
    add_exit("trophy_1x8", "west");
} /* create_cave_room */
