/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_2_10.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-05      
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
    add_item(({"pier","landing"}),
               "South of you is the westernmost of three piers, "
             + "where the village fishermen dock. Only a couple "
             + "of boats can be seen at the moment, the rest are "
             + "out on the lake.\n");
    add_item(({"boat","boats","fishing boat","fishing boats"}),
               "Docked at the piers are a few simple wooden boats, "
             + "some with sails. The rest are out on the lake at the "
             + "moment.\n");
             
    add_exit(ROOM + "road_1_10.c","west",0,1,0);
    add_exit(ROOM + "road_2_9.c","north",0,1,0);
    add_exit(ROOM + "road_3_10.c","east",0,1,0);
    add_exit(ROOM + "road_2_11.c","south",0,1,0);

    set_short("Walkway");
    set_long("Walkway goes W and E.\n"
           + "Pier south.\n");
}

