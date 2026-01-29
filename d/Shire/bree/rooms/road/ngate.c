/*
 * North Gate of Bree
 * By Finwe, June  2002
 *
 * 2002/06/18 Last update
 * 2011/07/21 Lavellan - Updating to use fixed base rooms
 */

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit "/d/Shire/bree/stdgateroom.c";

create_gateroom()
{
    set_short("Western gate of Bree");
//    set_long("@@my_long");
    set_other_room(ROAD_DIR + "broad23");
    set_direction("southeast");

    set_add_dike();
    set_add_outside_hedge();

    add_exit(ROAD_DIR + "road03",   "west");
    add_exit(ROAD_DIR + "nhedge07", "east");
    add_exit(ROAD_DIR + "nhedge06", "south");
}

//my_long() {
long_desc() {
  string str;

    if (gatestate) str = "The gates are open. ";
    else str = "The gates are closed to keep villains out. ";
    return "You are standing in front of the northern gates of "+
        "the village of Bree. " + str + "The village lies south " +
        "with a lonely road running west to Deadman's Dike and " +
        "southeast into the village.\n";
}
