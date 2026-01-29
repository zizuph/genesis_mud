/* created by Aridor 03/09/94 */

#include "../guild/guild.h"

inherit DOOR_ROOM_BASE

#define OTHER    CAVERN + "pal1"
/* additional IDs!!! of keys (except keyring) to the door here. */
#define KEYS     ({ })


void
create_door_room()
{
    other_room = OTHER;
    keys += KEYS;

    set_short("In a cavern.\nThere is a door leading east.\n" +
	      "There are two obvious exits: southeast and west");
    set_long("This is a cavern, which continues to " +
	     "your southeast, where it leads downwards also, turning " +
	     "into a hallway, and to your west, leading outside into " +
	     "fresh air.\nThere is a@@door_state@@ door leading east.\n" +
	     "There are two obvious exits: southeast and west.\n");
    
    set_noshow_obvious(1);
    add_exit(CAVERN + "pal5","southeast");
    add_exit(CAVERN + "pal7","west");
    add_exit(OTHER,"east","@@door_is_closed");
    
}
