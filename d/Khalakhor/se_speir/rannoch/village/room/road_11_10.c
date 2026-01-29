/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_11_10.c
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
    add_exit(ROOM + "road_10_9.c","northwest",0,1,0);
    add_exit(ROOM + "road_12_10.c","east",0,1,0);

    set_short("Walkway blah");
    set_long("Height: 1.\n");
           /*+ "Direction: E, stair NW.\n");*/
}

