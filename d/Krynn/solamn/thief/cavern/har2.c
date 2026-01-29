/* created by Aridor 03/09/94 */

#include "../guild/guild.h"

inherit DOOR_ROOM_BASE

#define OTHER    CAVERN + "har1"
/* additional IDs!!! of keys (except keyring) to the door here. */
#define KEYS     ({ })


void
create_door_room()
{
    other_room = OTHER;
    keys += KEYS;

    set_short("In a cavern.\nThere is a door leading south.\n" +
	      "There are two obvious exits: north, up");
    set_long("This is a cavern. There is a stone staircase leading up " +
	     "and the cavern continues north.\n" +
	     "There is a@@door_state@@ door leading south.\n" +
	     "There are two obvious exits: north, up.\n");
    
    set_noshow_obvious(1);
    add_exit(OTHER,"south","@@door_is_closed");
    add_exit(CAVERN + "har3","north");
    add_exit(CAVERN + "har8","up");

    add_item(({"stairs","staircase"}),
	     "A narrow staircase leads up into the rock from here. The " +
	     "stairs, like almost everything around here, are made from " +
	     "stone.\n");
}
