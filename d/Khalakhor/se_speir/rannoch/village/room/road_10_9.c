/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_10_9.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-19      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Changed structure to coord system (Darragh 2003-07-25) 
 */

#pragma strict_types

#include "room.h"

inherit VILLAGE_BASEFILE;

public void
create_road()
{
    add_item(({"stair","stairs","stairway","stone","stones"}),
               "The stair has been carved out of the cliff itself, and "
             + "the steps are rough and of different heights.\n");
    add_item(({"steps"}),
               "Whatever.\n");

    add_exit(ROOM + "road_9_8.c","northwest",0,1,0);
    add_exit(ROOM + "road_10_8.c","north",0,1,0);
    add_exit(ROOM + "road_11_10.c","southeast",0,1,0);

    set_short("On a stair");
    set_long("Stair.\n"
           + "Walkway starts SE.\n"
           + "Water, no railing?\n");
}

