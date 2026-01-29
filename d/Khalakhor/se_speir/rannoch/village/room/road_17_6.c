/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_17_6.c
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
    add_item(({"cliff","cliffs","cliffside","cliffsides","rocks"}),
               "MAYBE special cliffs.\n");

    add_exit(ROOM + "road_16_6.c","west",0,1,0);
    add_exit(ROOM + "road_16_5.c","northwest",0,1,0);
    add_exit(ROOM + "road_18_7.c","southeast",0,1,0);

    set_long("MAYBE special cliffs.\n");
}

