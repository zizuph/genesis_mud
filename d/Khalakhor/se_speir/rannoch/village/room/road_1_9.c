/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_1_9.c
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
               "West.\n");

    add_exit(ROOM + "road_0_9.c","west",0,1,0);
    add_exit(ROOM + "road_1_8.c","north",0,1,0);
    add_exit(ROOM + "road_2_9.c","east",0,1,0);
    add_exit(ROOM + "road_1_10.c","south",0,1,0);

    set_long("No specials.\n"
           + "Among houses.\n"
           + "Gate west.\n"
           + "Large 2-storey building 2 E, inn.\n");
}

