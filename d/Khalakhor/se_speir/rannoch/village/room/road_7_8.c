/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_7_8.c
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
    add_item(({"bridge","crossing"}),
               "The village has been built on both sides of "
             + "the river, and this bridge seems to be the "
             + "only way to cross into the other side. It is "
             + "made of wood and stone, allowing heavy traffic "
             + "across it.\n");
    add_item(({"river","water"}),
               "You stand at the river's western bank. The river "
             + "joins the lake south of here, and the only means "
             + "of crossing it is the bridge northeast of you.\n");
            
    add_exit(ROOM + "road_6_8.c","west",0,1,0);
    add_exit(ROOM + "road_7_7.c","north",0,1,0);
    add_exit(ROOM + "road_6_9.c","southwest",0,1,0);

    set_short("Walkway");
    set_long("Walkway goes N and SW.\n");
}

