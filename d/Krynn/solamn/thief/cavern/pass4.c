/* created by Aridor 08/30/94 */

#include "../guild/guild.h"

inherit DOOR_ROOM_BASE

#define OTHER   GUILDR + "shop"
/* additional IDs!!! of keys (except keyring) to the door here. */
#define KEYS     ({ })


void
create_door_room()
{
    other_room = OTHER;
    keys += KEYS;

    set_short("In a cavern.\nA door is leading southwest.\n" +
	      "There are two obvious exits: up, northeast");
    set_long("This is a cavern. The door leading southwest just doesn't " +
	     "fit into this rather natural cavern. You can see traces " +
	     "of manual work having been done here though to enlarge " +
	     "the cavern and to also carve the stairs from the rock " +
	     "which are leading upwards from here. The cavern itself " +
	     "extends further in a northeastern direction.\n" +
	     "A@@door_state@@ door is leading southwest.\n" +
	     "There are two obvious exits: up, northeast.\n");
    
    set_noshow_obvious(1);
    add_exit(CAVERN + "pass3","up");
    add_exit(CAVERN + "pass5","northeast");
    add_exit(OTHER,"southwest","@@door_is_closed");
    
    add_item("stairs","They're uneven stairs cut out from the rock leading " +
	     "upwards.\n");
}
