/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_6_9.c
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
    add_exit(ROOM + "road_5_9.c","west",0,1,0);
    add_exit(ROOM + "road_6_8.c","north",0,1,0);
    add_exit(ROOM + "road_7_8.c","northeast",0,1,0);

    set_short("Walkway");
    set_long("No specials.\n"
           + "Walkway W and NE.\n");
}

