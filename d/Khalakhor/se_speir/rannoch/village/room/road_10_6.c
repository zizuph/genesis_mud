/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_10_6.c
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
   add_exit(ROOM + "road_9_6.c","west",0,1,0);
   add_exit(ROOM + "road_10_5.c","north",0,1,0);
   add_exit(ROOM + "road_11_5.c","northeast",0,1,0);
   add_exit(ROOM + "road_11_6.c","east",0,1,0);
   add_exit(ROOM + "road_10_7.c","south",0,1,0);
   add_exit(ROOM + "road_9_7.c","southwest",0,1,0);

    set_short("Main road");
    set_long("Direction SW and NE.\n");
}

