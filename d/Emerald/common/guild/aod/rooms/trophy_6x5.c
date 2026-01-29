/*
 *  /d/Emerald/common/guild/aod/rooms/trophy_6x5.c
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

    add_spike("trophy_6x5");

    add_exit("trophy_5x5", "north");
    add_exit("trophy_5x6", "northeast");
    add_exit("trophy_6x6", "east");
    add_exit("trophy_7x6", "southeast");
    add_exit("trophy_7x5", "south");
    add_exit("trophy_7x4", "southwest");
    add_exit("trophy_6x4", "west");
    add_exit("trophy_5x4", "northwest");
} /* create_cave_room */
