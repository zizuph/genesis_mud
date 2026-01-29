/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_12_9.c
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
    add_item(({"building"}),
               "It is small, but very clean and well maintained. The "
             + "door is open.\n");

    add_item(({"door","doorway"}),
               "The door, unlike the rest of the building, is badly "
             + "need of repair.\n");

   add_exit(ROOM + "road_12_8.c","north",0,1,0);
   add_exit(ROOM + "road_11_9.c","west",0,1,0);
   
}

