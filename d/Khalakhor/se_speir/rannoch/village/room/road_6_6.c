/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_6_6.c
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
    add_exit(ROOM + "road_7_6.c","east",0,1,0);
    add_exit(ROOM + "road_6_7.c","south",0,1,0);

    set_short("Wall");
    set_long("Wall goes E.\n"
           + "Wall goes W, but blocked behind large building (add_item).\n"
           + "Smell from east.\n");
}

