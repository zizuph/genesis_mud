/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_15_1.c
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
               "The exit from the village lies east of here.\n");

    add_exit(ROOM + "road_14_1.c","west",0,1,0);
    add_exit(ROOM + "road_16_1.c","east",0,1,0);
    add_exit(ROOM + "road_15_2.c","south",0,1,0);

    set_short("Wall");
    set_long("Wall goes W and E.\n"
           + "Gate E.\n");
}

