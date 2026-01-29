/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_12_2.c
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
    add_item(({"river","water"}),
               "You stand the river's eastern bank. The river joins "
             + "the lake south of here, and it seems impossible to "
             + "cross it here due to its depth and temperature. On "
             + "the other side you see nothing but forest.\n");

    add_exit(ROOM + "road_13_1.c","northeast",0,1,0);
    add_exit(ROOM + "road_13_2.c","east",0,1,0);
    add_exit(ROOM + "road_12_3.c","south",0,1,0);
    add_exit(ROOM + "road_11_3.c","southwest",0,1,0);

    set_short("River");
    set_long("River.\n");
}

