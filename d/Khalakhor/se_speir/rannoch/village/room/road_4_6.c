/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_4_6.c
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
    add_item(({"wall","wooden wall","pole","poles","layer","layers"}),
               "The wall is made of two layers of wooden poles, driven "
             + "deep into the ground, and reinforced with mud and ropes. "
             + "It looks sturdy enough to keep unwanted people out. The "
             + "top of the poles have been sharpened, to prevent anyone "
             + "from climbing over it.\n");

    add_exit(ROOM + "road_3_6.c","west",0,1,0);
    add_exit(ROOM + "road_4_7.c","south",0,1,0);

    set_short("Wall");
    set_long("Wall goes west.\n"
           + "Wall goes east behind large building (add_item).\n");
}

