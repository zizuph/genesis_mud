/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_17_8.c
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
    add_exit(ROOM + "road_16_8.c","west",0,1,0);
    add_exit(ROOM + "road_17_7.c","north",0,1,0);
    add_exit(ROOM + "road_18_7.c","northeast",0,1,0);
    add_exit(ROOM + "road_17_9.c","south",0,1,0);

    set_short("Walkway");
    set_long("Height: 8.\n"
           + "Starts here, direction: S.\n"
           + "Maybe tower.\n"
           + "Maybe cliffs.\n"
           + "Highest point in village.\n");
}

