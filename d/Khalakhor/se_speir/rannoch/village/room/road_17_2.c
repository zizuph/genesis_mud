/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_17_2.c
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

    add_item(({"gate","village gate"}),
               "The exit from the village lies northwest of here.\n");

    add_exit(ROOM + "road_16_2.c","west",0,1,0);
    add_exit(ROOM + "road_16_1.c","northwest",0,1,0);
    add_exit(ROOM + "road_17_3.c","south",0,1,0);

    set_short("Wall");
    set_long("Wall goes NW and S.\n"
           + "Gate NW.\n");
}

