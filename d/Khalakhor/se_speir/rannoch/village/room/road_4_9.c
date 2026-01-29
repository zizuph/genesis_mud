/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_4_9.c
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
    add_exit(ROOM + "road_3_9.c","west",0,1,0);            
    add_exit(ROOM + "road_4_8.c","north",0,1,0);
    add_exit(ROOM + "road_5_9.c","east",0,1,0);
    add_exit(ROOM + "road_4_10.c","south",0,1,0);

    set_short("Walkway");
    set_long("Walkay goes E and S.\n"
           + "Marketplace N.\n"
           + "Large 2-storey building directly west (inn).\n");
}

