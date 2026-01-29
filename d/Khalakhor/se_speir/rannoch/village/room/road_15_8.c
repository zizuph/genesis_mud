/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_15_8.c
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
    add_item(({"adv_guild"}),
               "Blah.\n");

    add_exit(ROOM + "road_14_8.c","west",0,1,0);
    add_exit(ROOM + "road_15_7.c","north",0,1,0);
    add_exit(ROOM + "road_16_8.c","east",0,1,0);
    add_exit(ROOM + "road_15_9.c","south",0,1,0);
    add_exit(ROOM + "adv_guild.c","southwest",0,1,0);
}

