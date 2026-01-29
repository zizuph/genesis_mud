/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_3_12.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-09     
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
    add_item(({"planks","pier","ground","floor","dirt"}),
               "You are on a wooden pier, about five feet above the "
             + "water. The planks are old and worn, and some of them "
             + "have been replaced recently.\n");

    add_exit(ROOM + "road_3_11.c","north",0,1,0);

    set_short("Pier");
    set_long("Pier continues north.\n");
}

