/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_5_6.c
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
   set_short("Inside a large house");
   set_long("This house is not finished.\n");

   add_exit(ROOM + "road_5_7.c","south",0,1,0);
}

