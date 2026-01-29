/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_0_8.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-08      
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
               "South.\n");
    add_item(({"banner"}),
               "Same as by gate, road_0_9.\n");

    add_exit(ROOM + "road_1_7.c","northeast",0,1,0);
    add_exit(ROOM + "road_1_8.c","east",0,1,0);
    add_exit(ROOM + "road_0_9.c","south",0,1,0);

    set_short("Wall");
    set_long("Wall goes NE and S.\n"
           + "Gate south.\n");
}

